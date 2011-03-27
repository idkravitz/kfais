#include "../headers/card.h"

using namespace Setting;

inline void AddWidToLt(QGridLayout *aLt, QLabel *aLbl, QWidget *aW, int aRow, int aCol)
{
    aLt->addWidget(aLbl, aRow, aCol);
    aLt->addWidget(aW, aRow, aCol + 1);
    aLbl->setBuddy(aW);
}

/******************************* Card (basic) *******************************/

Card::Card(QWidget *aParent, Setting::TblType aType, int aId):
        QDialog(aParent),
        type(aType),
        id(aId)
{
    setAttribute(Qt::WA_DeleteOnClose);

    model = new QSqlRelationalTableModel(this);
}

int Card::GetId() const
{
    return id;
}

void Card::CreateBasicWidgets(QLayout *aLt)
{
    QHBoxLayout *lt1 = new QHBoxLayout;
    QLabel *lblNote = new QLabel(tr("Заметка"));
    edtNote = new QLineEdit;
    lt1->addWidget(lblNote);
    lt1->addWidget(edtNote);

    QHBoxLayout *lt2 = new QHBoxLayout;
    btnOk = new QPushButton(tr("Ok"));
    btnCancel = new QPushButton(tr("Закрыть"));
    connect(btnOk, SIGNAL(clicked()), this, SLOT(Ok()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    lt2->addWidget(btnOk);
    lt2->addWidget(btnCancel);

    QVBoxLayout *lt = new QVBoxLayout;
    lt->addLayout(aLt);
    lt->addLayout(lt1);
    lt->addLayout(lt2);
    setLayout(lt);
}

void Card::Ok()
{

}

void Card::closeEvent(QCloseEvent *aE)
{
    model->revert();
    mdiArea->closeActiveSubWindow();
    aE->accept();
}

/******************************* Sportsmen *******************************/

CardSport::CardSport(QWidget *aParent, int aId):
        Card(aParent, ttSport, aId)
{
    CreateWidgets();

    model->setTable(table_settings[ttSport].tblName);
    model->setFilter("id = " + QString::number(aId));
    model->select();

//    QTableView *tbl = new QTableView(this);
//    tbl->setModel(model);
//    QHBoxLayout *lt = new QHBoxLayout;
//    lt->addWidget(tbl);
//    setLayout(lt);
}

void CardSport::CreateWidgets()
{
    QGridLayout *lt1 = new QGridLayout;
    edtName = new QLineEdit;
    AddWidToLt(lt1, new QLabel(tr("ФИО")), edtName, 0, 0);
    edtDateBirth = new QDateEdit;
    edtDateBirth->setCalendarPopup(true);
    AddWidToLt(lt1, new QLabel(tr("Дата рождения")), edtDateBirth, 0, 2);
    edtAddr = new QLineEdit;
    AddWidToLt(lt1, new QLabel(tr("Адрес")), edtAddr, 1, 0);
    edtPhone = new QLineEdit;
    AddWidToLt(lt1, new QLabel(tr("Телефон")), edtPhone, 1, 2);
    edtWorkplace = new QLineEdit;
    AddWidToLt(lt1, new QLabel(tr("Место работы")), edtWorkplace, 2, 0);
    edtJob = new QLineEdit;
    AddWidToLt(lt1, new QLabel(tr("Должность")), edtJob, 2, 2);
//    cbCoach = new QComboBox;
//    AddWidToLt(lt1, new QLabel(tr("Тренер")), cbb, 2, 2);
//    = new Q;
//    AddWidToLt(lt1, new QLabel(tr("Должность")), edtJob, 2, 2);
//    edtJob = new QLineEdit;
//    A*ddWidToLt(lt1, new QLabel(tr("Должность")), edtJob, 2, 2);

    CreateBasicWidgets(lt1);
}

/******************************* Coaches *******************************/

CardCoach::CardCoach(QWidget *aParent, int aId):
        Card(aParent, ttCoach, aId)
{

}

/******************************* Clubs *******************************/

CardClub::CardClub(QWidget *aParent, int aId):
        Card(aParent, ttClub, aId)
{

}

/******************************* Sertifications *******************************/

CardSert::CardSert(QWidget *aParent, int aId):
        Card(aParent, ttSert, aId)
{

}

/******************************* Fee *******************************/

CardFee::CardFee(QWidget *aParent, int aId):
        Card(aParent, ttFee, aId)
{

}

/******************************* Sportsmen-Competiotions *******************************/

CardSportComp::CardSportComp(QWidget *aParent, int aId):
        Card(aParent, ttSportComp, aId)
{

}

/******************************* Competiotions *******************************/

CardComp::CardComp(QWidget *aParent, int aId):
        Card(aParent, ttComp, aId)
{

}

/******************************* Categories *******************************/

CardCateg::CardCateg(QWidget *aParent, int aId):
        Card(aParent, ttCateg, aId)
{

}
