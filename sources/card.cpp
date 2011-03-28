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

void Card::InitModel(TblType aType, const QString &aFilter)
{
    model->setTable(Sett::GetTblName(aType));
    model->setFilter(aFilter);
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
    QLabel *lbl = new QLabel(tr(Sett::GetColName(type, aTAIndex)));
    aLt->addWidget(lbl, aRow, aCol);
    aLt->addWidget(aW, aRow, aCol + 1);
    lbl->setBuddy(aW);
}

bool Card::IsValid() const
{
    //Hack
    return true;
}

/******************************* Sportsmen *******************************/

CardSport::CardSport(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSport, aId)
{
    CreateWidgets();
    InitModel(ttSport, "id = " + QString::number(aId));

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
    InitModel(ttCoach, "id = " + QString::number(aId));
    CreateWidgets();

    cbClub->setModel(model->relationModel(Coach::taClub));
    cbClub->setModelColumn(Club::taName);

    mapper->addMapping(edtName, Coach::taName);
    mapper->addMapping(edtPhone, Coach::taPhone);
    mapper->addMapping(cbClub, Coach::taClub);
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
    InitModel(ttClub, "id = " + QString::number(aId));
    CreateWidgets();
    mapper->addMapping(edtName, Club::taName);
    mapper->addMapping(edtAddr, Club::taAddr);
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

}

/******************************* Fee *******************************/

CardFee::CardFee(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttFee, aId)
{

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

}

/******************************* Categories *******************************/

CardCateg::CardCateg(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttCateg, aId)
{

}

/******************************* Ranks *******************************/

CardRank::CardRank(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttRank, aId)
{

}
