#include "table.h"

/******************************* Table (basic) *******************************/

Table::Table(QWidget *aParent, TblType aType):
        QMainWindow(aParent),
        type(aType)
{
    setAttribute(Qt::WA_DeleteOnClose);
    model = new TableModel(this);
    connect(model, SIGNAL(Refresh()), this, SLOT(UpdateTable()));
    CreateWidgets();
    view->setModel(model);
}

Table::~Table()
{
    SaveTableSettings();
}

void Table::CreateWidgets()
{
    QToolBar *tb = new QToolBar;
    tb->setFloatable(false);    //Disable floatable

    tb->addAction(QIcon(":/resource/First.ico"), tr("Начало"), this, SLOT(SetFirst()));
    tb->addAction(QIcon(":/resource/Next.ico"), tr("Следующий"), this, SLOT(SetNext()));
    tb->addAction(QIcon(":/resource/Prev.ico"), tr("Предудыщий"), this, SLOT(SetPrev()));
    tb->addAction(QIcon(":/resource/Last.ico"), tr("Конец"), this, SLOT(SetLast()));
    tb->addAction(QIcon(":/resource/Add.ico"), tr("Добавить"), this, SLOT(Add()));
    tb->addAction(QIcon(":/resource/Delete.ico"), tr("Удалить"), this, SLOT(Delete()));
    tb->addAction(QIcon(":/resource/Edit.png"), tr("Редактировать"), this, SLOT(Edit()));

    addToolBar(tb);

    view = new TableView;
    view->setSortingEnabled(true);
    view->setShowGrid(true);
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OpenCard(QModelIndex)));
    connect(view->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(SetSort(int)));

    ApplyTableSettings();

    setWindowTitle(Sett::GetTblTitle(type));
    setCentralWidget(view);
}

void Table::UpdateTable()
{
    ApplyTableSettings();
}

void Table::SetTableHeaders()
{
    QVector<char*> *n = &Sett::GetVecColName(type);
    for (int i = 0; i < n->size(); ++i)
        model->setHeaderData(i, Qt::Horizontal, tr(n->at(i)));
}

void Table::ApplyTableSettings()
{
    QVector<int> *w = &Sett::GetVecColWidth(type);
    for (int i = 0; i < w->size(); ++i)
        view->setColumnWidth(i, w->at(i));
    SetTableHeaders();
    view->setColumnHidden(0, true);
}

void Table::SaveTableSettings()
{
    QVector<int> *w = &Sett::GetVecColWidth(type);
    w->resize(model->columnCount());
    for (int i = 0; i < model->columnCount(); ++i)
        (*w)[i] = view->columnWidth(i);
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
    _CreateCard(-1);
}

void Table::Delete()
{
    int button = QMessageBox::question(this,
        tr("Подтверждение удаления"),
        tr("Вы действительно хотите удалить текущую запись?"),
            QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes)
    {
        int curRow = view->currentIndex().row();
        QString delId = model->GetVal(view->currentIndex().row(), 0).toString();
        model->DelRecord(Sett::GetTblName(type), "id = " + delId);
        view->selectRow(curRow);
    }
}

void Table::Edit()
{
    OpenCard(view->currentIndex());
}

void Table::OpenCard(QModelIndex aMIndex)
{
    int id = model->GetVal(aMIndex.row(), 0).toInt();
    MapCard::const_iterator it = mapCard.find(id);
    if (it != mapCard.end())       //if card already opened
    {
        it.value()->setFocus();
        return;
    }
    mapCard.insert(id, _CreateCard(id));
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

inline Card *Table::_CreateCard(int aId) const
{
    Card *c = CreateCard(aId);
    QMdiSubWindow *sw = Sett::GetMA()->addSubWindow(c);
    sw->show();
    connect(c, SIGNAL(destroyed(QObject *)), this, SLOT(CloseCard(QObject *)));
    return c;
}

void Table::SetSort(int aI)
{
//    QVector<QString> v;
//    v << "[^]" << "[v]";
//    prevSortVal = Qt::SortOrder(prevSortCol == aI ? !prevSortVal : Qt::AscendingOrder);
//    SetTableHeaders();
//    model->setSort(aI, prevSortVal);
//    model->setHeaderData(aI, Qt::Horizontal, model->headerData(aI, Qt::Horizontal).toString() + " " + v[prevSortVal]);
//    model->select();
//    prevSortCol = aI;
}

/******************************* Sportsmen *******************************/

TblSport::TblSport(QWidget *aParent):
        Table(aParent, ttSport)
{
    model->SetQuery(
            "SELECT s.id, s.name, s.birthday, r.name, s.reg_number, c.name, s.address, s.phone, s.workplace, s.job, s.note "
            "FROM sportsmen s LEFT OUTER JOIN coaches c ON s.coach_id = c.id LEFT OUTER JOIN ranks r ON s.rank_id = r.id");
    model->Select();
}

Card *TblSport::CreateCard(int aId) const
{
    return new CardSport(Sett::GetMA(), model, aId);
}

/******************************* Coaches *******************************/

TblCoach::TblCoach(QWidget *aParent):
        Table(aParent, ttCoach)
{
    model->SetQuery("SELECT c.id, c.name, c.phone, cl.name, c.note "
                     "FROM coaches c LEFT OUTER JOIN clubs cl ON c.club_id = cl.id");
    model->Select();
}

Card *TblCoach::CreateCard(int aId) const
{
    return new CardCoach(Sett::GetMA(), model, aId);
}

/******************************* Clubs *******************************/

TblClub::TblClub(QWidget *aParent):
        Table(aParent, ttClub)
{
    model->SetQuery("SELECT id, name, address, note FROM clubs");
    model->Select();
}

Card *TblClub::CreateCard(int aId) const
{
    return new CardClub(Sett::GetMA(), model, aId);
}

/******************************* Sertifications *******************************/

TblSert::TblSert(QWidget *aParent):
        Table(aParent, ttSert)
{
    model->SetQuery("SELECT se.id, s.name, se.date, r1.name, r2.name, se.note FROM sertifications se "
                     "JOIN sportsmen s, ranks r2 ON se.sportsman_id = s.id AND se.rank_to_id = r2.id "
                     "LEFT OUTER JOIN ranks r1 ON se.rank_from_id = r1.id");
    model->Select();
}

Card *TblSert::CreateCard(int aId) const
{
    return new CardSert(Sett::GetMA(), model, aId);
}

///******************************* Fee *******************************/

TblFee::TblFee(QWidget *aParent):
        Table(aParent, ttFee)
{
    model->SetQuery("SELECT f.id, s.name, f.date, f.note FROM fee f "
                     "JOIN sportsmen s ON f.sportsman_id = s.id");
    model->Select();
}

Card *TblFee::CreateCard(int aId) const
{
    return new CardFee(Sett::GetMA(), model, aId);
}

/******************************* Sportsmen-Competiotions *******************************/

TblSportComp::TblSportComp(QWidget *aParent):
        Table(aParent, ttSportComp)
{
    model->SetQuery("SELECT sc.id, sp.name, co.name, co.date, ca.name, sc.draw_number, sc.units, sc.note "
                     "FROM sportsmen_competitions sc JOIN sportsmen sp, competitions co "
                     "ON sc.sportsman_id = sp.id AND sc.competition_id = co.id "
                     "LEFT OUTER JOIN categories ca ON sc.category_id = ca.id");
    model->Select();
}

Card *TblSportComp::CreateCard(int aId) const
{
    return new CardSportComp(Sett::GetMA(), model, aId);
}

/******************************* Competiotions *******************************/

TblComp::TblComp(QWidget *aParent):
        Table(aParent, ttComp)
{
    model->SetQuery("SELECT id, name, name_prot, date, location, note FROM competitions");
    model->Select();
}

Card *TblComp::CreateCard(int aId) const
{
    return new CardComp(Sett::GetMA(), model, aId);
}

/******************************* Categories *******************************/

TblCateg::TblCateg(QWidget *aParent):
        Table(aParent, ttCateg)
{
    model->SetQuery("SELECT id, name, note FROM categories");
    model->Select();
}

Card *TblCateg::CreateCard(int aId) const
{
    return new CardCateg(Sett::GetMA(), model, aId);
}

/******************************* Ranks *******************************/

TblRank::TblRank(QWidget *aParent):
        Table(aParent, ttRank)
{
    model->SetQuery("SELECT id, name, note FROM ranks");
    model->Select();
}

Card *TblRank::CreateCard(int aId) const
{
    return new CardRank(Sett::GetMA(), model, aId);
}

/******************************* Prize winners *******************************/

TblPrzWin::TblPrzWin(QWidget *aParent):
        Table(aParent, ttPrzWin)
{
    model->SetQuery("SELECT pw.id, c.name, c.date, s.name, pw.fights_count, pw.fights_won, pw.place, pw.region, "
                     "pw.city, pw.note FROM prize_winners pw "
                     "JOIN sportsmen_competitions sc ON pw.sportsman_competition_id = sc.id "
                     "JOIN sportsmen s, competitions c ON sc.sportsman_id = s.id AND sc.competition_id = c.id");
    model->Select();
}

Card *TblPrzWin::CreateCard(int aId) const
{
    return new CardPrzWin(Sett::GetMA(), model, aId);
}
