#include "../headers/table.h"

using namespace Setting;

Table::Table(QWidget *aParent, TblType aType):
        QMainWindow(aParent),
        type(aType)
{
    setAttribute(Qt::WA_DeleteOnClose);
    CreateWidgets();
}

void Table::CreateWidgets()
{
    QToolBar *tb = new QToolBar;
    tb->setFloatable(false);    //Disable floatable

    tb->addAction(tr("Начало"), this, SLOT(SetFirst()));
    tb->addAction(tr("Следующий"), this, SLOT(SetNext()));
    tb->addAction(tr("Предудыщий"), this, SLOT(SetPrev()));
    tb->addAction(tr("Конец"), this, SLOT(SetLast()));
    tb->addAction(tr("Добавить"), this, SLOT(Add()));
    tb->addAction(tr("Удалить"), this, SLOT(Delete()));
    tb->addAction(tr("Редактировать"), this, SLOT(Edit()));

    addToolBar(tb);

    model = new QSqlRelationalTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnRowChange);  
    model->setTable(table_settings[type].tblName);

    view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection); //Selection mode - single
    view->setSelectionBehavior(QAbstractItemView::SelectRows);  //Selection mode - full row
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);   //Disable editing

    setWindowTitle(tr(table_settings[type].title));
    setCentralWidget(view);
}

void Table::TableSpecificConfig()
{
    model->select();
}

TblType Table::Type() const
{
    return type;
}

void Table::SetFirst()
{

}

void Table::SetNext()
{

}

void Table::SetPrev()
{

}

void Table::SetLast()
{

}

void Table::Add()
{

}

void Table::Delete()
{

}

void Table::Edit()
{

}

/******************************* Sportsmen *******************************/

TblSport::TblSport(QWidget *aParent):
        Table(aParent, ttSport)
{ 
    TableSpecificConfig();
}

/******************************* Trainers *******************************/

TblCoach::TblCoach(QWidget *aParent):
        Table(aParent, ttCoach)
{
    TableSpecificConfig();
}

/******************************* Clubs *******************************/

TblClub::TblClub(QWidget *aParent):
        Table(aParent, ttClub)
{
    TableSpecificConfig();
}

/******************************* Sertifications *******************************/

TblSert::TblSert(QWidget *aParent):
        Table(aParent, ttSert)
{
    TableSpecificConfig();
}

/******************************* Fee *******************************/

TblFee::TblFee(QWidget *aParent):
        Table(aParent, ttFee)
{
    TableSpecificConfig();
}

/******************************* Sportsmen-Competiotions *******************************/

TblSportComp::TblSportComp(QWidget *aParent):
        Table(aParent, ttSportComp)
{
    TableSpecificConfig();
}

/******************************* Competiotions *******************************/

TblComp::TblComp(QWidget *aParent):
        Table(aParent, ttComp)
{
    TableSpecificConfig();
}

/******************************* Categories *******************************/

TblCateg::TblCateg(QWidget *aParent):
        Table(aParent, ttCateg)
{
    TableSpecificConfig();
}
