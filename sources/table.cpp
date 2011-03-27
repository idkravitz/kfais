#include "../headers/table.h"

using namespace Setting;

/******************************* Card (basic) *******************************/

Table::Table(QWidget *aParent, TblType aType):
        QMainWindow(aParent),
        type(aType)
{
    setAttribute(Qt::WA_DeleteOnClose);
    CreateWidgets();
}

Table::~Table()
{
    SaveTableSettings();
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
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OpenCard(QModelIndex)));

    ApplyTableSettings();

    setWindowTitle(tr(table_settings[type].title));
    setCentralWidget(view);
}

void Table::ApplyTableSettings()
{
    QVector<int> *w = &table_settings[type].colWidth;
    QVector<char*> *n = &table_settings[type].colName;
    for (int i = 0; i < w->size(); ++i)
        view->setColumnWidth(i, w->at(i));
    for (int i = 0; i < n->size(); ++i)
        model->setHeaderData(i, Qt::Horizontal, tr(n->at(i)));
}

void Table::SaveTableSettings()
{
    QVector<int> *w = &table_settings[type].colWidth;
    w->resize(model->columnCount());
    for (int i = 0; i < model->columnCount(); ++i)
        (*w)[i] = view->columnWidth(i);
}

void Table::TableSpecificConfig()
{
    model->select();
    ApplyTableSettings();
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

void Table::OpenCard(QModelIndex aMIndex)
{
    int id = model->record(aMIndex.row()).value(0).toInt();
    MapCard::const_iterator it = mapCard.find(id);
    if (it != mapCard.end())    //if card already opened
    {
        it.value()->setFocus();
        return;
    }
    Card *c = CreateCard(id);
    QMdiSubWindow *sw = mdiArea->addSubWindow(c);
    sw->show();
    mapCard.insert(id, c);
    connect(c, SIGNAL(destroyed(QObject *)), this, SLOT(CloseCard(QObject *)));
}

void Table::CloseCard(QObject *aObj)
{
    MapCard::iterator it = mapCard.find(static_cast<Card *>(aObj)->GetId());
    if (it != mapCard.end())
    {
        mapCard.erase(it);
    }
}

/******************************* Sportsmen *******************************/

TblSport::TblSport(QWidget *aParent):
        Table(aParent, ttSport)
{ 
    TableSpecificConfig();
}

Card *TblSport::CreateCard(int aId) const
{
    return new CardSport(mdiArea, aId);
}

/******************************* Coaches *******************************/

TblCoach::TblCoach(QWidget *aParent):
        Table(aParent, ttCoach)
{
    TableSpecificConfig();
}

Card *TblCoach::CreateCard(int aId) const
{
return 0;
}

/******************************* Clubs *******************************/

TblClub::TblClub(QWidget *aParent):
        Table(aParent, ttClub)
{
    TableSpecificConfig();
}

Card *TblClub::CreateCard(int aId) const
{
return 0;
}

/******************************* Sertifications *******************************/

TblSert::TblSert(QWidget *aParent):
        Table(aParent, ttSert)
{
    TableSpecificConfig();
}

Card *TblSert::CreateCard(int aId) const
{
return 0;
}

/******************************* Fee *******************************/

TblFee::TblFee(QWidget *aParent):
        Table(aParent, ttFee)
{
    TableSpecificConfig();
}

Card *TblFee::CreateCard(int aId) const
{
return 0;
}

/******************************* Sportsmen-Competiotions *******************************/

TblSportComp::TblSportComp(QWidget *aParent):
        Table(aParent, ttSportComp)
{
    TableSpecificConfig();
}

Card *TblSportComp::CreateCard(int aId) const
{
return 0;
}

/******************************* Competiotions *******************************/

TblComp::TblComp(QWidget *aParent):
        Table(aParent, ttComp)
{
    TableSpecificConfig();
}

Card *TblComp::CreateCard(int aId) const
{
    return 0;
}

/******************************* Categories *******************************/

TblCateg::TblCateg(QWidget *aParent):
        Table(aParent, ttCateg)
{
    TableSpecificConfig();
}

Card *TblCateg::CreateCard(int aId) const
{
    return 0;
}

/******************************* Ranks *******************************/

TblRank::TblRank(QWidget *aParent):
        Table(aParent, ttRank)
{
    TableSpecificConfig();
}

Card *TblRank::CreateCard(int aId) const
{
    return 0;
}
