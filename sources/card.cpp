#include "card.h"

inline bool CheckCond(bool aCond, const QString &aMsg)
{
    if (aCond)
    {
        QMessageBox::critical(0, Sett::GetErrMsgTitle(), aMsg);
        return true;
    }
    return false;
}

/******************************* Card (basic) *******************************/

Card::Card(QWidget *aParent, QSqlRelationalTableModel *aTblModel, TblType aType, int aId):
        QDialog(aParent),
        tblModel(aTblModel),
        type(aType),
        id(aId)
{
    setAttribute(Qt::WA_DeleteOnClose);

    model = new QSqlRelationalTableModel(this);
    InitModel(aId);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);   //The model is not updated until submit() is called.
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
}

int Card::GetId() const
{
    return id;
}

void Card::CreateBasicWidgets(QLayout *aLt)
{
    QGroupBox *gbNote = new QGroupBox(Sett::GetNoteName());
    QHBoxLayout *lt1 = new QHBoxLayout;
    edtNote = new QLineEdit;
    lt1->addWidget(edtNote);
    mapper->addMapping(edtNote, Sett::GetVecColName(type).size() - 1);
    gbNote->setLayout(lt1);

    QGroupBox *gb = new QGroupBox;
    gb->setLayout(aLt);

    QHBoxLayout *lt2 = new QHBoxLayout;
    btnOk = new QPushButton(tr("Ok"));
    btnCancel = new QPushButton(tr("Закрыть"));
    connect(btnOk, SIGNAL(clicked()), this, SLOT(Ok()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(Cancel()));
    lt2->addStretch(1);
    lt2->addWidget(btnOk);
    lt2->addWidget(btnCancel);
    lt2->addStretch(0);

    QVBoxLayout *lt = new QVBoxLayout;
    lt->addWidget(gb);
    lt->addWidget(gbNote);
    lt->addLayout(lt2);
    setLayout(lt);
}

void Card::InitModel(int aId)
{
    model->setTable(Sett::GetTblName(type));
    model->setFilter(Sett::GetTblName(type) + ".id = " + QString::number(aId));
    for (int i = 0; i < tblModel->columnCount(); ++i)
    {
        QSqlRelation tmpRelation = tblModel->relation(i);
        if (tmpRelation.isValid())
        {
            model->setRelation(i, tmpRelation);
        }
    }
    model->select();
    if (id == -1)   //If is new
    {
        model->insertRow(0);
    }
}

void Card::Ok()
{
    if (!IsValid())
    {
        return;
    }
    if (!mapper->submit())
    {
        QMessageBox::critical(0, Sett::GetErrMsgTitle(), Sett::GetErrMsgDef());
        return;
    }
    tblModel->select(); //Update table model
    close();
}

void Card::Cancel()
{
    model->revert();
    close();
}

void Card::closeEvent(QCloseEvent *aE)
{
    Sett::GetMA()->closeActiveSubWindow();
    aE->accept();
}

void Card::AddWid(QGridLayout *aLt, int aTAIndex, QWidget *aW, int aRow, int aCol)
{
    AddWidToLt(aLt, Sett::GetColName(type, aTAIndex) + ":", aW, aRow, aCol);
    mapper->addMapping(aW, aTAIndex);
}

bool Card::IsValid() const
{
    return true;
}

inline void Card::_SetCBModel(QComboBox *aCB, int aIn, int aOut)
{
    aCB->setModel(model->relationModel(aIn));
    aCB->setModelColumn(aOut);
    aCB->setInsertPolicy(QComboBox::NoInsert);
    aCB->setEditable(true);
    QCompleter *comp = new QCompleter(model->relationModel(aIn));
    comp->setCompletionColumn(aOut);
    aCB->setCompleter(comp);
}

/******************************* Sportsmen *******************************/

inline QTableView *CardSport::_InitViewModel(QTableView *aView, QSqlRelationalTableModel *aModel, TblType aType)
{
    aModel->setTable(Sett::GetTblName(aType));
    aModel->setFilter("sportsman_id = " + QString::number(GetId()));
    aModel->setEditStrategy(QSqlTableModel::OnRowChange);

    aView->setModel(aModel);
    Sett::SetParam(aView);

    return aView;
}

inline QGroupBox *CardSport::_AddTable(TblType aType, QTableView *aView, QSqlRelationalTableModel *aModel, const QString &aTitle)
{
    QGroupBox *gb = new QGroupBox(aTitle);
    QHBoxLayout *lt = new QHBoxLayout;
    lt->addWidget(_InitViewModel(aView, aModel, aType));
    gb->setLayout(lt);
    return gb;
}

inline QGroupBox *CardSport::_AddTable(TblType aType, QTableView *aView, QSqlRelationalTableModel *aModel)
{
    return _AddTable(aType, aView, aModel, Sett::GetTblTitle(aType));
}

CardSport::CardSport(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSport, aId)
{
    CreateWidgets();
    _SetCBModel(cbRank, Sport::taRank, Rank::taName);
    _SetCBModel(cbCoach, Sport::taCoach, Coach::taName);
    mapper->toFirst();
}

void CardSport::CreateWidgets()
{
    QGridLayout *lt1 = new QGridLayout;
    AddWid(lt1, Sport::taName, edtName = new QLineEdit, 0, 0);
    AddWid(lt1, Sport::taBirth, edtDateBirth = new QDateEdit, 0, 2);
    edtDateBirth->setCalendarPopup(true);
    AddWid(lt1, Sport::taRank, cbRank = new QComboBox, 0, 4);

    AddWid(lt1, Sport::taCoach, cbCoach = new QComboBox, 1, 2);
    AddWid(lt1, Sport::taRegNum, edtRegNum = new QLineEdit, 1, 4);
    QRegExp rx( "^[1-9]{1}[0-9]*$" );
    edtRegNum->setValidator(new QRegExpValidator(rx, this));

    AddWid(lt1, Sport::taAddr, edtAddr = new QLineEdit, 2, 2);
    AddWid(lt1, Sport::taPhone, edtPhone = new QLineEdit, 2, 4);

    AddWid(lt1, Sport::taWork, edtWorkplace = new QLineEdit, 3, 2);
    AddWid(lt1, Sport::taJob, edtJob = new QLineEdit, 3, 4);

    QVBoxLayout *lt = new QVBoxLayout;
    lt->addLayout(lt1);
    lt->addLayout(CreateInnerTbls());
    CreateBasicWidgets(lt);
}

QVBoxLayout *CardSport::CreateInnerTbls()
{
    QVBoxLayout *lt2 = new QVBoxLayout;

    lt2->addWidget(_AddTable(ttSert, viewSert = new QTableView, modelSert = new QSqlRelationalTableModel(this)));
    lt2->addWidget(_AddTable(ttSportComp, viewSC = new QTableView, modelSC = new QSqlRelationalTableModel(this),
                             tr("Спортивные достижения")));
    lt2->addWidget(_AddTable(ttFee, viewFee = new QTableView, modelFee = new QSqlRelationalTableModel(this)));

    viewSert->setColumnHidden(Sert::taId, true);
    viewSert->setColumnHidden(Sert::taSport, true);
    viewSC->setColumnHidden(SportComp::taId, true);
    viewSC->setColumnHidden(SportComp::taSport, true);
    viewFee->setColumnHidden(Fee::taId, true);
    viewFee->setColumnHidden(Fee::taSport, true);

    modelSert->setRelation(3, QSqlRelation("ranks", "id", "name"));
    modelSert->setRelation(4, QSqlRelation("ranks", "id", "name"));
    modelSert->select();

    modelSC->setRelation(4, QSqlRelation("categories", "id", "name"));
    modelSC->select();

    modelFee->select();

    return lt2;
}


bool CardSport::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Введите Ф.И.О. спортсмена"));
}

/******************************* Coaches *******************************/

CardCoach::CardCoach(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttCoach, aId)
{
    CreateWidgets();
    _SetCBModel(cbClub, Coach::taClub, Club::taName);
    mapper->toFirst();
}

void CardCoach::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Coach::taName, edtName = new QLineEdit, 0);
    AddWid(lt, Coach::taPhone, edtPhone = new QLineEdit, 1);
    AddWid(lt, Coach::taClub, cbClub = new QComboBox, 2);
    CreateBasicWidgets(lt);
}

bool CardCoach::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Введите Ф.И.О. тренера"));
}

/******************************* Clubs *******************************/

CardClub::CardClub(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttClub, aId)
{
    CreateWidgets();
    mapper->toFirst();
}

void CardClub::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Club::taName, edtName = new QLineEdit, 0);
    AddWid(lt, Club::taAddr, edtAddr = new QLineEdit, 1);
    CreateBasicWidgets(lt);
}

bool CardClub::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Введите название клуба"));
}

/******************************* Sertifications *******************************/

CardSert::CardSert(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSert, aId)
{
    CreateWidgets();

    _SetCBModel(cbSport, Sert::taSport, Sport::taName);
    _SetCBModel(cbRankFrom, Sert::taRankFrom, Rank::taName);
    _SetCBModel(cbRankTo, Sert::taRankTo, Rank::taName);

    mapper->toFirst();
}

void CardSert::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;

    AddWid(lt, Sert::taSport, cbSport = new QComboBox, 1);
    AddWid(lt, Sert::taDate, edtDate = new QDateEdit, 2);
    edtDate->setCalendarPopup(true);
    AddWid(lt, Sert::taRankFrom, cbRankFrom = new QComboBox, 3);
    AddWid(lt, Sert::taRankTo, cbRankTo = new QComboBox, 4);
    CreateBasicWidgets(lt);
}

bool CardSert::IsValid() const
{
    return !CheckCond(cbSport->currentText().isEmpty(), tr("Выберите спортсмена"));
}

/******************************* Fee *******************************/

CardFee::CardFee(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttFee, aId)
{
    CreateWidgets();
    _SetCBModel(cbSport, Fee::taSport, Sport::taName);
    mapper->toFirst();
}

void CardFee::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Fee::taSport, cbSport = new QComboBox, 0);
    AddWid(lt, Fee::taDate, edtDate = new QDateEdit, 1);
    edtDate->setCalendarPopup(true);
    CreateBasicWidgets(lt);
}

bool CardFee::IsValid() const
{
    return !CheckCond(cbSport->currentText().isEmpty(), tr("Выберите спортсмена"));
}

/******************************* Sportsmen-Competiotions *******************************/

CardSportComp::CardSportComp(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSportComp, aId)
{
    CreateWidgets();
}

void CardSportComp::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
//    AddWid(lt, Fee::taSport, cbSport = new QComboBox, 0);
//    AddWid(lt, Fee::taDate, edtDate = new QDateEdit, 1);
//    edtDate->setCalendarPopup(true);
    CreateBasicWidgets(lt);
}

bool CardSportComp::IsValid() const
{
//    return !CheckCond(cbSport->currentText().isEmpty(), tr("Выберите спортсмена"));
    return true;
}

/******************************* Competiotions *******************************/

CardComp::CardComp(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttComp, aId)
{
    CreateWidgets();
    mapper->toFirst();
}

void CardComp::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Comp::taName, edtName = new QLineEdit, 0);
    AddWid(lt, Comp::taDate, edtDate = new QDateEdit, 1);
    edtDate->setCalendarPopup(true);
    AddWid(lt, Comp::taLoc, edtLoc = new QLineEdit, 2);
    CreateBasicWidgets(lt);
}

bool CardComp::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Выберите название соревнования"));
}

/******************************* Categories *******************************/

CardCateg::CardCateg(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttCateg, aId)
{
    CreateWidgets();
    mapper->toFirst();
}

void CardCateg::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Categ::taName, edtName = new QLineEdit, 0);
    CreateBasicWidgets(lt);
}

bool CardCateg::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Выберите название категории"));
}

/******************************* Ranks *******************************/

CardRank::CardRank(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttRank, aId)
{
    CreateWidgets();
    mapper->toFirst();
}

void CardRank::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Rank::taName, edtName = new QLineEdit, 0);
    CreateBasicWidgets(lt);
}

bool CardRank::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Выберите название разряда"));
}
