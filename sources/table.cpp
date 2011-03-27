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

    view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection); //Selection mode - single
    view->setSelectionBehavior(QAbstractItemView::SelectRows);  //Selection mode - full row
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);   //Disable editing
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OpenCard(QModelIndex)));

    setCentralWidget(view);
}

void Table::Init(const QString &aTitle, const QString &aTblName)
{
    setWindowTitle(aTitle);
    model->setTable(aTblName);
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
    using namespace Sport;

    Init(tr(title), Sport::tblName);
}

Card *TblSport::CreateCard(int aId) const
{
    return new CardSport(mdiArea, aId);
}

/******************************* Coaches *******************************/

TblCoach::TblCoach(QWidget *aParent):
        Table(aParent, ttCoach)
{
    using namespace Coach;

    Init(tr(title), tblName);
}

Card *TblCoach::CreateCard(int aId) const
{
return 0;
}

/******************************* Clubs *******************************/

TblClub::TblClub(QWidget *aParent):
        Table(aParent, ttClub)
{
    using namespace Club;

    Init(tr(title), tblName);
}

Card *TblClub::CreateCard(int aId) const
{
return 0;
}

/******************************* Sertifications *******************************/

TblSert::TblSert(QWidget *aParent):
        Table(aParent, ttSert)
{
    using namespace Sert;

    Init(tr(title), tblName);
}

Card *TblSert::CreateCard(int aId) const
{
return 0;
}

/******************************* Fee *******************************/

TblFee::TblFee(QWidget *aParent):
        Table(aParent, ttFee)
{
    using namespace Fee;

    Init(tr(title), tblName);
}

Card *TblFee::CreateCard(int aId) const
{
return 0;
}

/******************************* Sportsmen-Competiotions *******************************/

TblSportComp::TblSportComp(QWidget *aParent):
        Table(aParent, ttSportComp)
{
    using namespace SportComp;

    Init(tr(title), tblName);
}

Card *TblSportComp::CreateCard(int aId) const
{
return 0;
}

/******************************* Competiotions *******************************/

TblComp::TblComp(QWidget *aParent):
        Table(aParent, ttComp)
{
    using namespace Comp;

    Init(tr(title), tblName);
}

Card *TblComp::CreateCard(int aId) const
{
    return 0;
}

/******************************* Categories *******************************/

TblCateg::TblCateg(QWidget *aParent):
        Table(aParent, ttCateg)
{
    using namespace Categ;

    Init(tr(title), tblName);
}

Card *TblCateg::CreateCard(int aId) const
{
    return 0;
}
