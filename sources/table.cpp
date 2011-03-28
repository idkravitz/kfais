#include "../headers/table.h"

/******************************* Table (basic) *******************************/

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
    model->setTable(Sett::GetTblName(type));
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    view = new QTableView;
    view->setModel(model);
    Sett::SetParam(view);
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OpenCard(QModelIndex)));

    ApplyTableSettings();

    setWindowTitle(Sett::GetTblTitle(type));
    setCentralWidget(view);
}

void Table::ApplyTableSettings()
{
    QVector<int> *w = &Sett::GetVecColWidth(type);
    QVector<char*> *n = &Sett::GetVecColName(type);
    for (int i = 0; i < w->size(); ++i)
        view->setColumnWidth(i, w->at(i));
    for (int i = 0; i < n->size(); ++i)
        model->setHeaderData(i, Qt::Horizontal, tr(n->at(i)));
}

void Table::SaveTableSettings()
{
    QVector<int> *w = &Sett::GetVecColWidth(type);
    w->resize(model->columnCount());
    for (int i = 0; i < model->columnCount(); ++i)
        (*w)[i] = view->columnWidth(i);
}

void Table::TableSpecificConfig()
{
    model->select();
    view->setColumnHidden(0, true);
}

TblType Table::Type() const
{
    return type;
}

void Table::SetFirst()
{
    view->selectRow(0);
}

void Table::SetNext()
{
    view->selectRow(view->currentIndex().row() + 1);
}

void Table::SetPrev()
{
    view->selectRow(view->currentIndex().row() - 1);
}

void Table::SetLast()
{
    view->selectRow(model->rowCount() - 1);
}

void Table::Add()
{

}

void Table::Delete()
{
    int button = QMessageBox::question(this,
        tr("Подтверждение удаления"),
        tr("Вы действительно хотите удалить текущую запись?"),
            QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes)
    {
        model->removeRow(view->currentIndex().row());
    }
}

void Table::Edit()
{

}

void Table::OpenCard(QModelIndex aMIndex)
{
    int id = model->record(aMIndex.row()).value(0).toInt();
    MapCard::const_iterator it = mapCard.find(id);
    if (it != mapCard.end())       //if card already opened
    {
        it.value()->setFocus();
        return;
    }
    Card *c = CreateCard(id);
    QMdiSubWindow *sw = Sett::GetMA()->addSubWindow(c);
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
    setFocus();
}

/******************************* Sportsmen *******************************/

void TblSport::TableSpecificConfig()
{
    model->setRelation(4, QSqlRelation("ranks", "id", "name"));
    model->setRelation(6, QSqlRelation("coaches", "id", "name"));
    model->select();
    view->setColumnHidden(0, true);
    view->setColumnHidden(Sport::taPhoto, true);
}

TblSport::TblSport(QWidget *aParent):
        Table(aParent, ttSport)
{ 
    TableSpecificConfig();
}

Card *TblSport::CreateCard(int aId) const
{
    return new CardSport(Sett::GetMA(), model, aId);
}

/******************************* Coaches *******************************/

void TblCoach::TableSpecificConfig()
{
    model->setRelation(3, QSqlRelation(Sett::GetTblName(ttClub), "id", "name"));
    model->select();
    view->setColumnHidden(0, true);
}

TblCoach::TblCoach(QWidget *aParent):
        Table(aParent, ttCoach)
{
    TableSpecificConfig();
}

Card *TblCoach::CreateCard(int aId) const
{
    return new CardCoach(Sett::GetMA(), model, aId);
}

/******************************* Clubs *******************************/

TblClub::TblClub(QWidget *aParent):
        Table(aParent, ttClub)
{
    TableSpecificConfig();
}

Card *TblClub::CreateCard(int aId) const
{
    return new CardClub(Sett::GetMA(), model, aId);
}

/******************************* Sertifications *******************************/

void TblSert::TableSpecificConfig()
{ 
    model->setRelation(1, QSqlRelation("sportsmen", "id", "name"));    
    model->setRelation(3, QSqlRelation("ranks", "id", "name"));
    model->setRelation(4, QSqlRelation("ranks", "id", "name"));
    model->select();
}

TblSert::TblSert(QWidget *aParent):
        Table(aParent, ttSert)
{
    TableSpecificConfig();
}

Card *TblSert::CreateCard(int aId) const
{
    return new CardSert(Sett::GetMA(), model, aId);
}

/******************************* Fee *******************************/

void TblFee::TableSpecificConfig()
{
    model->setRelation(1, QSqlRelation("sportsmen", "id", "name"));    
    model->select();
    view->setColumnHidden(0, true);
}

TblFee::TblFee(QWidget *aParent):
        Table(aParent, ttFee)
{
    TableSpecificConfig();
}

Card *TblFee::CreateCard(int aId) const
{
    return new CardFee(Sett::GetMA(), model, aId);
}

/******************************* Sportsmen-Competiotions *******************************/

void TblSportComp::TableSpecificConfig()
{
    model->setRelation(1, QSqlRelation("sportsmen", "id", "name"));    
    model->setRelation(4, QSqlRelation("categories", "id", "name"));    
    model->select();
    view->setColumnHidden(0, true);
}

TblSportComp::TblSportComp(QWidget *aParent):
        Table(aParent, ttSportComp)
{
    TableSpecificConfig();
}

Card *TblSportComp::CreateCard(int aId) const
{
    return new CardComp(Sett::GetMA(), model, aId);
}

/******************************* Competiotions *******************************/

TblComp::TblComp(QWidget *aParent):
        Table(aParent, ttComp)
{
    TableSpecificConfig();
}

Card *TblComp::CreateCard(int aId) const
{
    return new CardComp(Sett::GetMA(), model, aId);
}

/******************************* Categories *******************************/

TblCateg::TblCateg(QWidget *aParent):
        Table(aParent, ttCateg)
{
    TableSpecificConfig();
}

Card *TblCateg::CreateCard(int aId) const
{
    return new CardCateg(Sett::GetMA(), model, aId);
}

/******************************* Ranks *******************************/

TblRank::TblRank(QWidget *aParent):
        Table(aParent, ttRank)
{
    TableSpecificConfig();
}

Card *TblRank::CreateCard(int aId) const
{
    return new CardRank(Sett::GetMA(), model, aId);
}
