#include "../headers/card.h"

/******************************* Card (basic) *******************************/

Card::Card(QWidget *aParent, QSqlRelationalTableModel *aTblModel, TblType aType, int aId):
        QDialog(aParent),
        tblModel(aTblModel),
        type(aType),
        id(aId)
{
    setAttribute(Qt::WA_DeleteOnClose);

    model = new QSqlRelationalTableModel(this);

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
    QHBoxLayout *lt1 = new QHBoxLayout;
    QLabel *lblNote = new QLabel(tr(Sett::GetNoteName()));
    edtNote = new QLineEdit;
    lblNote->setBuddy(edtNote);
    lt1->addWidget(lblNote);
    lt1->addWidget(edtNote);

    QHBoxLayout *lt2 = new QHBoxLayout;
    btnOk = new QPushButton(tr("Ok"));
    btnCancel = new QPushButton(tr("Закрыть"));
    connect(btnOk, SIGNAL(clicked()), this, SLOT(Ok()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(Cancel()));
    lt2->addWidget(btnOk);
    lt2->addWidget(btnCancel);

    QVBoxLayout *lt = new QVBoxLayout;
    lt->addLayout(aLt);
    lt->addLayout(lt1);
    lt->addLayout(lt2);
    setLayout(lt);
}

void Card::InitModel(const QString &aFilter)
{
    model->setTable(Sett::GetTblName(type));
    model->setFilter(Sett::GetTblName(type) + "." + aFilter);
    for (int i = 0; i < tblModel->columnCount(); ++i)
    {
        QSqlRelation tmpRelation = tblModel->relation(i);
        if (tmpRelation.isValid())
        {
            model->setRelation(i, tmpRelation);
        }
    }
    model->select();
}

void Card::Ok()
{
    if (!IsValid())
    {
        return;
    }
    mapper->submit();
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

void Card::AddWidToLt(QGridLayout *aLt, int aTAIndex, QWidget *aW, int aRow, int aCol)
{
    QLabel *lbl = new QLabel(tr(Sett::GetColName(type, aTAIndex)) + ":");
    aLt->addWidget(lbl, aRow, aCol);
    aLt->addWidget(aW, aRow, aCol + 1);
    lbl->setBuddy(aW);
    mapper->addMapping(aW, aTAIndex);
}

bool Card::IsValid() const
{
    //Hack
    return true;
}

inline void Card::_SetCBModel(QComboBox *aCB, int aIn, int aOut)
{
    aCB->setModel(model->relationModel(aIn));
    aCB->setModelColumn(aOut);
}

/******************************* Sportsmen *******************************/

CardSport::CardSport(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSport, aId)
{
    CreateWidgets();
    InitModel("id = " + QString::number(aId));

//    QTableView *tbl = new QTableView(this);
//    tbl->setModel(model);
//    QHBoxLayout *lt = new QHBoxLayout;
//    lt->addWidget(tbl);
//    setLayout(lt);
}

void CardSport::CreateWidgets()
{
    QGridLayout *lt1 = new QGridLayout;
//    edtName = new QLineEdit;
//    AddWidToLt(lt1, tr("ФИО"), edtName, 0, 0);
//    edtDateBirth = new QDateEdit;
//    edtDateBirth->setCalendarPopup(true);
//    AddWidToLt(lt1, tr("Дата рождения"), edtDateBirth, 0, 2);
//    edtAddr = new QLineEdit;
//    AddWidToLt(lt1, tr("Адрес"), edtAddr, 1, 0);
//    edtPhone = new QLineEdit;
//    AddWidToLt(lt1, tr("Телефон"), edtPhone, 1, 2);
//    edtWorkplace = new QLineEdit;
//    AddWidToLt(lt1, tr("Место работы"), edtWorkplace, 2, 0);
//    edtJob = new QLineEdit;
//    AddWidToLt(lt1, tr("Должность"), edtJob, 2, 2);
//    cbCoach = new QComboBox;
//    AddWidToLt(lt1, new QLabel(tr("Тренер")), cbb, 2, 2);
//    = new Q;
//    AddWidToLt(lt1, new QLabel(tr("Должность")), edtJob, 2, 2);
//    edtJob = new QLineEdit;
//    A*ddWidToLt(lt1, new QLabel(tr("Должность")), edtJob, 2, 2);

    CreateBasicWidgets(lt1);
}

/******************************* Coaches *******************************/

CardCoach::CardCoach(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttCoach, aId)
{
    InitModel("id = " + QString::number(aId));
    CreateWidgets();
    _SetCBModel(cbClub, Coach::taClub, Club::taName);
    mapper->toFirst();
}

void CardCoach::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Coach::taName, edtName = new QLineEdit, 0);
    AddWidToLt(lt, Coach::taPhone, edtPhone = new QLineEdit, 1);
    AddWidToLt(lt, Coach::taClub, cbClub = new QComboBox, 2);
    CreateBasicWidgets(lt);
}

/******************************* Clubs *******************************/

CardClub::CardClub(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttClub, aId)
{
    InitModel("id = " + QString::number(aId));
    CreateWidgets();
    mapper->toFirst();
}

void CardClub::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Club::taName, edtName = new QLineEdit, 0);
    AddWidToLt(lt, Club::taAddr, edtAddr = new QLineEdit, 1);
    CreateBasicWidgets(lt);
}

/******************************* Sertifications *******************************/

CardSert::CardSert(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSert, aId)
{
    InitModel("num_rec_sert = " + QString::number(aId));
    CreateWidgets();

    _SetCBModel(cbSport, Sert::taSport, Sport::taName);
    _SetCBModel(cbRankFrom, Sert::taRankFrom, Rank::taName);
    _SetCBModel(cbRankTo, Sert::taRankTo, Rank::taName);

    mapper->toFirst();
}

void CardSert::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;

    AddWidToLt(lt, Sert::taNumRecSert, edtNum = new QLineEdit, 0);
    QRegExp rx( "^[1-9]{1}[0-9]*$" );
    edtNum->setValidator(new QRegExpValidator(rx, this));

    AddWidToLt(lt, Sert::taSport, cbSport = new QComboBox, 1);
    AddWidToLt(lt, Sert::taDate, edtDate = new QDateEdit, 2);
    edtDate->setCalendarPopup(true);
    AddWidToLt(lt, Sert::taRankFrom, cbRankFrom = new QComboBox, 3);
    AddWidToLt(lt, Sert::taRankTo, cbRankTo = new QComboBox, 4);
    AddWidToLt(lt, Sert::taRes, edtRes = new QLineEdit, 5);
    CreateBasicWidgets(lt);
}

/******************************* Fee *******************************/

CardFee::CardFee(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttFee, aId)
{
    InitModel("id = " + QString::number(aId));
    CreateWidgets();
    _SetCBModel(cbSport, Fee::taSport, Sport::taName);
    mapper->toFirst();
}

void CardFee::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Fee::taSport, cbSport = new QComboBox, 0);
    AddWidToLt(lt, Fee::taDate, edtDate = new QDateEdit, 1);
    edtDate->setCalendarPopup(true);
    CreateBasicWidgets(lt);
}

/******************************* Sportsmen-Competiotions *******************************/

CardSportComp::CardSportComp(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSportComp, aId)
{

}

/******************************* Competiotions *******************************/

CardComp::CardComp(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttComp, aId)
{
    InitModel("id = " + QString::number(aId));
    CreateWidgets();
    mapper->toFirst();
}

void CardComp::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Comp::taName, edtName = new QLineEdit, 0);
    AddWidToLt(lt, Comp::taDate, edtDate = new QDateEdit, 1);
    edtDate->setCalendarPopup(true);
    AddWidToLt(lt, Comp::taLoc, edtLoc = new QLineEdit, 2);
    CreateBasicWidgets(lt);
}

/******************************* Categories *******************************/

CardCateg::CardCateg(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttCateg, aId)
{
    InitModel("id = " + QString::number(aId));
    CreateWidgets();
    mapper->toFirst();
}

void CardCateg::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Categ::taName, edtName = new QLineEdit, 0);
    CreateBasicWidgets(lt);
}

/******************************* Ranks *******************************/

CardRank::CardRank(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttRank, aId)
{
    InitModel("id = " + QString::number(aId));
    CreateWidgets();
    mapper->toFirst();
}

void CardRank::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Rank::taName, edtName = new QLineEdit, 0);
    CreateBasicWidgets(lt);
}
