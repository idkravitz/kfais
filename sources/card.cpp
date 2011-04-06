#include "card.h"
#include <limits.h>

extern void InitComboBox(QComboBox *aCB, QVector<int> &aVecId, const QString &aStrQ, int aCurId);

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

Card::Card(QWidget *aParent, TableModel *aModel, TblType aType, int aId):
        QDialog(aParent),
        tblModel(aModel),
        type(aType),
        id(aId)
{
    setAttribute(Qt::WA_DeleteOnClose);
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
    gbNote->setLayout(lt1);

    QGroupBox *gb = new QGroupBox;
    gb->setLayout(aLt);

    QHBoxLayout *lt2 = new QHBoxLayout;
    btnOk = new QPushButton(tr("Ok"));
    btnCancel = new QPushButton(tr("Закрыть"));
    lt2->addStretch(1);
    lt2->addWidget(btnOk);
    lt2->addWidget(btnCancel);
    lt2->addStretch(0);
    connect(btnOk, SIGNAL(clicked()), this, SLOT(Ok()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *lt = new QVBoxLayout;
    lt->addWidget(gb);
    lt->addWidget(gbNote);
    lt->addLayout(lt2);
    setLayout(lt);
}

void Card::Ok()
{
    if (!IsValid())
    {
        return;
    }
    if (!Submit())
    {
        QMessageBox::critical(0, Sett::GetErrMsgTitle(), Sett::GetErrMsgDef());
        return;
    }
    tblModel->Select();
    close();
}

void Card::closeEvent(QCloseEvent *aE)
{
    Sett::GetMA()->closeActiveSubWindow();
    aE->accept();
}

inline void Card::AddWid(QGridLayout *aLt, int aTAIndex, QWidget *aW, int aRow, int aCol)
{
    AddWidToLt(aLt, Sett::GetColName(type, aTAIndex) + ":", aW, aRow, aCol);
}

bool Card::IsValid() const
{
    return true;
}

bool Card::Submit()
{
    return true;
}

bool Card::IsNew() const
{
    return id == -1;
}

inline void Card::SetRegExprInt(QLineEdit* aEdt, bool aCanBeZero)
{
    QRegExp rx(aCanBeZero ? "^[0-9]*$" : "^[1-9]{1}[0-9]*$");
    aEdt->setValidator(new QRegExpValidator(rx, this));
}

inline QString PackToQM(const QString &aStr, bool aIsQM)
{
    return aIsQM ? "'" + aStr + "'" : aStr;
}

QString Card::CreateQuary(const MapQuery &aMap)
{
    QString str;
    if (IsNew())
    {
        str = "INSERT INTO " + Sett::GetTblName(type) + " (";
        QString strVal = " VALUES (";
        MapQuery::const_iterator it = aMap.begin();
        str += it.key().first;
        strVal += PackToQM(it.key().second, it.value());
        while (++it != aMap.end())
        {
            str += ", " + it.key().first;
            strVal += ", " + PackToQM(it.key().second, it.value());
        }
        strVal += ")";
        str += ")" + strVal;
    }
    else
    {
        str = "UPDATE " + Sett::GetTblName(type) + " SET ";
        MapQuery::const_iterator it = aMap.begin();
        str += it.key().first + " = " + PackToQM(it.key().second, it.value());
        while (++it != aMap.end())
        {
            str += ", " + it.key().first + " = " + PackToQM(it.key().second, it.value());
        }
        str += " WHERE id = " + QString::number(id);
    }
    return str;
}

/******************************* Sportsmen *******************************/

//inline QTableView *CardSport::_InitViewModel(QTableView *aView, QSqlRelationalTableModel *aModel, TblType aType)
//{
//    aModel->setTable(Sett::GetTblName(aType));
//    aModel->setFilter("sportsman_id = " + QString::number(GetId()));
//    aModel->setEditStrategy(QSqlTableModel::OnRowChange);

//    aView->setModel(aModel);

//    return aView;
//}

//inline QGroupBox *CardSport::_AddTable(TblType aType, QTableView *aView, QSqlRelationalTableModel *aModel, const QString &aTitle)
//{
//    QGroupBox *gb = new QGroupBox(aTitle);
//    QHBoxLayout *lt = new QHBoxLayout;
//    lt->addWidget(_InitViewModel(aView, aModel, aType));
//    gb->setLayout(lt);
//    return gb;
//}

//inline QGroupBox *CardSport::_AddTable(TblType aType, QTableView *aView, QSqlRelationalTableModel *aModel)
//{
//    return _AddTable(aType, aView, aModel, Sett::GetTblTitle(aType));
//}

//QVBoxLayout *CardSport::CreateInnerTbls()
//{
//    QVBoxLayout *lt2 = new QVBoxLayout;

//    lt2->addWidget(_AddTable(ttSert, viewSert = new QTableView, modelSert = new QSqlRelationalTableModel(this)));
//    lt2->addWidget(_AddTable(ttSportComp, viewSC = new QTableView, modelSC = new QSqlRelationalTableModel(this),
//                             tr("Спортивные достижения")));
//    lt2->addWidget(_AddTable(ttFee, viewFee = new QTableView, modelFee = new QSqlRelationalTableModel(this)));

//    viewSert->setColumnHidden(Sert::taId, true);
//    viewSert->setColumnHidden(Sert::taSport, true);
//    viewSC->setColumnHidden(SportComp::taId, true);
//    viewSC->setColumnHidden(SportComp::taSport, true);
//    viewFee->setColumnHidden(Fee::taId, true);
//    viewFee->setColumnHidden(Fee::taSport, true);

//    modelSert->setRelation(3, QSqlRelation("ranks", "id", "name"));
//    modelSert->setRelation(4, QSqlRelation("ranks", "id", "name"));
//    modelSert->select();

//    modelSC->setRelation(4, QSqlRelation("categories", "id", "name"));
//    modelSC->select();

//    modelFee->select();

//    return lt2;
//}

CardSport::CardSport(QWidget *aParent, TableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSport, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardSport::CreateWidgets()
{
    QGridLayout *lt1 = new QGridLayout;
    AddWid(lt1, Sport::taName, edtName = new QLineEdit, 0, 0);
    AddWid(lt1, Sport::taBirth, edtDateBirth = new QDateEdit, 0, 2);
    edtDateBirth->setCalendarPopup(true);
    AddWid(lt1, Sport::taRank, cbRank = new QComboBox, 1, 0);

    AddWid(lt1, Sport::taCoach, cbCoach = new QComboBox, 1, 2);
    AddWid(lt1, Sport::taRegNum, edtRegNum = new QLineEdit, 2, 0);
    SetRegExprInt(edtRegNum);

    AddWid(lt1, Sport::taAddr, edtAddr = new QLineEdit, 2, 2);
    AddWid(lt1, Sport::taPhone, edtPhone = new QLineEdit, 3, 0);

    AddWid(lt1, Sport::taWork, edtWorkplace = new QLineEdit, 3, 2);
    AddWid(lt1, Sport::taJob, edtJob = new QLineEdit, 4, 0);

    QVBoxLayout *lt = new QVBoxLayout;
    lt->addLayout(lt1);
    //lt->addLayout(CreateInnerTbls());
    CreateBasicWidgets(lt);
}

void CardSport::InitWidgets()
{
    QSqlQuery q("SELECT name, birthday, rank_id, reg_number, coach_id, address, phone, workplace, job, note "
                "FROM sportsmen WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    edtName->setText(r.value(0).toString());
    edtDateBirth->setDate(r.value(1).toDate());
    InitComboBox(cbRank, vecRankId, "SELECT id, name FROM ranks", r.value(2).toInt());
    edtRegNum->setText(r.value(3).toString());
    InitComboBox(cbCoach, vecCoachId, "SELECT id, name FROM coaches", r.value(4).toInt());
    edtAddr->setText(r.value(5).toString());
    edtPhone->setText(r.value(6).toString());
    edtWorkplace->setText(r.value(7).toString());
    edtJob->setText(r.value(8).toString());
    edtNote->setText(r.value(8).toString());
}

bool CardSport::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Введите Ф.И.О. спортсмена"));
}

bool CardSport::Submit()
{
    QString rank = cbRank->currentText().isEmpty() ? "NULL" : QString::number(vecRankId[cbRank->currentIndex()]);
    QString coach = cbCoach->currentText().isEmpty() ? "NULL" : QString::number(vecCoachId[cbCoach->currentIndex()]);
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("name", edtName->text()), true);
    mapQuery.insert(PairQuery("birthday", edtDateBirth->date().toString("yyyy-MM-dd")), true);
    mapQuery.insert(PairQuery("rank_id", rank), false);
    mapQuery.insert(PairQuery("reg_number", edtRegNum->text()), true);
    mapQuery.insert(PairQuery("coach_id", coach), false);
    mapQuery.insert(PairQuery("address", edtAddr->text()), true);
    mapQuery.insert(PairQuery("phone", edtPhone->text()), true);
    mapQuery.insert(PairQuery("workplace", edtWorkplace->text()), true);
    mapQuery.insert(PairQuery("job", edtJob->text()), true);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Coaches *******************************/

CardCoach::CardCoach(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttCoach, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardCoach::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Coach::taName, edtName = new QLineEdit, 0);
    AddWid(lt, Coach::taPhone, edtPhone = new QLineEdit, 1);
    AddWid(lt, Coach::taClub, cbClub = new QComboBox, 2);
    CreateBasicWidgets(lt);
}

void CardCoach::InitWidgets()
{
    QSqlQuery q("SELECT name, phone, club_id, note "
                "FROM coaches WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    edtName->setText(r.value(0).toString());
    edtPhone->setText(r.value(1).toString());
    InitComboBox(cbClub, vecClubId, "SELECT id, name FROM clubs", r.value(2).toInt());
    edtNote->setText(r.value(3).toString());
}

bool CardCoach::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Введите Ф.И.О. тренера"));
}

bool CardCoach::Submit()
{
    QString club = cbClub->currentText().isEmpty() ? "NULL" : QString::number(vecClubId[cbClub->currentIndex()]);
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("name", edtName->text()), true);
    mapQuery.insert(PairQuery("phone", edtPhone->text()), true);
    mapQuery.insert(PairQuery("club_id", club), false);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Clubs *******************************/

CardClub::CardClub(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttClub, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardClub::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Club::taName, edtName = new QLineEdit, 0);
    AddWid(lt, Club::taAddr, edtAddr = new QLineEdit, 1);
    CreateBasicWidgets(lt);
}

void CardClub::InitWidgets()
{
    QSqlQuery q("SELECT name, address, note FROM clubs WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    edtName->setText(r.value(0).toString());
    edtAddr->setText(r.value(1).toString());
    edtNote->setText(r.value(2).toString());
}

bool CardClub::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Введите название клуба"));
}

bool CardClub::Submit()
{
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("name", edtName->text()), true);
    mapQuery.insert(PairQuery("address", edtAddr->text()), true);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Sertifications *******************************/

CardSert::CardSert(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttSert, aId)
{
    CreateWidgets();
    InitWidgets();
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

void CardSert::InitWidgets()
{
    QSqlQuery q("SELECT sportsman_id, date, rank_from_id, rank_to_id, note "
                "FROM sertifications WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    InitComboBox(cbSport, vecSportId, "SELECT id, name FROM sportsmen", r.value(0).toInt());
    edtDate->setDate(r.value(1).toDate());
    InitComboBox(cbRankFrom, vecRankFromId, "SELECT id, name FROM ranks", r.value(2).toInt());
    InitComboBox(cbRankTo, vecRankToId, "SELECT id, name FROM ranks", r.value(3).toInt());
    edtNote->setText(r.value(4).toString());
}

bool CardSert::IsValid() const
{
    //проверить на null
    return !CheckCond(cbSport->currentText().isEmpty(), tr("Выберите спортсмена"));
}

bool CardSert::Submit()
{
    QString rankFrom = cbRankFrom->currentText().isEmpty() ?
                       "NULL" : QString::number(vecRankFromId[cbRankFrom->currentIndex()]);
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("sportsman_id", QString::number(vecSportId[cbSport->currentIndex()])), false);
    mapQuery.insert(PairQuery("date", edtDate->date().toString("yyyy-MM-dd")), true);
    mapQuery.insert(PairQuery("rank_from_id", rankFrom), false);
    mapQuery.insert(PairQuery("rank_to_id", QString::number(vecRankToId[cbRankTo->currentIndex()])), false);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Fee *******************************/

CardFee::CardFee(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttFee, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardFee::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Fee::taSport, cbSport = new QComboBox, 0);
    AddWid(lt, Fee::taDate, edtDate = new QDateEdit, 1);
    edtDate->setCalendarPopup(true);
    CreateBasicWidgets(lt);
}

void CardFee::InitWidgets()
{
    QSqlQuery q("SELECT sportsman_id, date, note "
                "FROM fee WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    InitComboBox(cbSport, vecSportId, "SELECT id, name FROM sportsmen", r.value(0).toInt());
    edtDate->setDate(r.value(1).toDate());
    edtNote->setText(r.value(2).toString());
}

bool CardFee::IsValid() const
{
    return !CheckCond(cbSport->currentText().isEmpty(), tr("Выберите спортсмена"));
}

bool CardFee::Submit()
{
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("sportsman_id", QString::number(vecSportId[cbSport->currentIndex()])), false);
    mapQuery.insert(PairQuery("date", edtDate->date().toString("yyyy-MM-dd")), true);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Sportsmen-Competiotions *******************************/

CardSportComp::CardSportComp(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttSportComp, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardSportComp::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, SportComp::taSport, cbSport = new QComboBox, 0);
    AddWid(lt, SportComp::taComp, cbComp = new QComboBox, 1);
    AddWid(lt, SportComp::taCateg, cbCateg = new QComboBox, 2);
    AddWid(lt, SportComp::taDrawNum, edtDrawNum = new QLineEdit, 3);
    SetRegExprInt(edtDrawNum, false);
    AddWid(lt, SportComp::taUnit, edtUnit = new QLineEdit, 4);
    SetRegExprInt(edtUnit, false);
    CreateBasicWidgets(lt);
}

void CardSportComp::InitWidgets()
{
    QSqlQuery q("SELECT sportsman_id, competition_id, category_id, draw_number, units, note "
                "FROM sportsmen_competitions WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    InitComboBox(cbSport, vecSportId, "SELECT id, name FROM sportsmen", r.value(0).toInt());
    InitComboBox(cbComp, vecCompId, "SELECT id, name || ' ' || date FROM competitions", r.value(1).toInt());
    InitComboBox(cbCateg, vecCategId, "SELECT id, name FROM categories", r.value(2).toInt());
    edtDrawNum->setText(r.value(3).toString());
    edtUnit->setText(r.value(4).toString());
    edtNote->setText(r.value(5).toString());
}

bool CardSportComp::IsValid() const
{
//    return !CheckCond(cbSport->currentText().isEmpty(), tr("Выберите спортсмена"));
//    return !CheckCond(cbSport->currentText().isEmpty(), tr("Выберите соревнование"));
    //проверка уникальности
    return true;
}

bool CardSportComp::Submit()
{
    QString categ = cbCateg->currentText().isEmpty() ?
                       "NULL" : QString::number(vecCategId[cbCateg->currentIndex()]);
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("sportsman_id", QString::number(vecSportId[cbSport->currentIndex()])), false);
    mapQuery.insert(PairQuery("competition_id", QString::number(vecCompId[cbComp->currentIndex()])), false);
    mapQuery.insert(PairQuery("category_id", categ), false);
    mapQuery.insert(PairQuery("draw_number", edtDrawNum->text()), true);
    mapQuery.insert(PairQuery("units", edtUnit->text()), true);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Competiotions *******************************/

CardComp::CardComp(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttComp, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardComp::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Comp::taName, edtName = new QLineEdit, 0);
    AddWid(lt, Comp::taNameProt, edtNameProt = new QLineEdit, 1);
    AddWid(lt, Comp::taDate, edtDate = new QDateEdit, 2);
    edtDate->setCalendarPopup(true);
    AddWid(lt, Comp::taLoc, edtLoc = new QLineEdit, 3);
    CreateBasicWidgets(lt);
}

void CardComp::InitWidgets()
{
    QSqlQuery q("SELECT name, name_prot, date, location, note "
                "FROM competitions WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    edtName->setText(r.value(0).toString());
    edtNameProt->setText(r.value(1).toString());
    edtDate->setDate(r.value(2).toDate());
    edtLoc->setText(r.value(3).toString());
    edtNote->setText(r.value(4).toString());
}

bool CardComp::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Выберите название соревнования"));
}

bool CardComp::Submit()
{
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("name", edtName->text()), true);
    mapQuery.insert(PairQuery("name_prot", edtNameProt->text()), true);
    mapQuery.insert(PairQuery("date", edtDate->date().toString("yyyy-MM-dd")), true);
    mapQuery.insert(PairQuery("location", edtLoc->text()), true);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Categories *******************************/

CardCateg::CardCateg(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttCateg, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardCateg::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Categ::taName, edtName = new QLineEdit, 0);
    CreateBasicWidgets(lt);
}

void CardCateg::InitWidgets()
{
    QSqlQuery q("SELECT name, note FROM categories WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    edtName->setText(r.value(0).toString());
    edtNote->setText(r.value(1).toString());
}

bool CardCateg::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Выберите название категории"));
}

bool CardCateg::Submit()
{
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("name", edtName->text()), true);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Ranks *******************************/

CardRank::CardRank(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttRank, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardRank::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWid(lt, Rank::taName, edtName = new QLineEdit, 0);
    CreateBasicWidgets(lt);
}

void CardRank::InitWidgets()
{
    QSqlQuery q("SELECT name, note FROM ranks WHERE id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    edtName->setText(r.value(0).toString());
    edtNote->setText(r.value(1).toString());
}

bool CardRank::IsValid() const
{
    return !CheckCond(edtName->text().isEmpty(), tr("Выберите название разряда"));
}

bool CardRank::Submit()
{
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("name", edtName->text()), true);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    QSqlQuery q(CreateQuary(mapQuery));
    return true;
}

/******************************* Prize winners *******************************/

int FindIndexById(const QVector<int> &aVecId, int aId)
{
    for (int  i = 0; i < aVecId.size(); ++i)
    {
        if (aId == aVecId[i])
        {
            return i;
        }
    }
}

CardPrzWin::CardPrzWin(QWidget *aParent, TableModel *aModel, int aId):
        Card(aParent, aModel, ttPrzWin, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardPrzWin::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;

    AddWid(lt, PrzWin::taCompName, cbComp = new QComboBox, 0, 0);
    AddWid(lt, PrzWin::taSport, cbSport = new QComboBox, 1, 0);
    AddWid(lt, PrzWin::taFightsCount, edtFightsCount = new QLineEdit, 2);
    SetRegExprInt(edtFightsCount);
    AddWid(lt, PrzWin::taFightsWon, edtFightsWon = new QLineEdit, 3);
    SetRegExprInt(edtFightsWon);
    AddWid(lt, PrzWin::taPlace, edtPlace = new QLineEdit, 4);
    SetRegExprInt(edtPlace, false);
    AddWid(lt, PrzWin::taRegion, edtRegion = new QLineEdit, 5);
    AddWid(lt, PrzWin::taCity, edtCity = new QLineEdit, 6);

    CreateBasicWidgets(lt);
}

void CardPrzWin::InitWidgets()
{
    QSqlQuery q("SELECT sc.competition_id, sc.sportsman_id, pw.fights_count, pw.fights_won, "
                "pw.place, pw.region, pw.city, pw.note "
                "FROM prize_winners pw JOIN sportsmen_competitions sc "
                "ON pw.sportsman_competition_id = sc.id WHERE pw.id = " + QString::number(id));
    q.next();
    QSqlRecord r = q.record();
    InitComboBox(cbComp, vecCompId, "SELECT id, name || ' ' || date FROM competitions", r.value(0).toInt());

    UpdateCBSport(cbComp->currentIndex());
    cbSport->setCurrentIndex(FindIndexById(vecSportId, r.value(1).toInt()));
    connect(cbComp, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateCBSport(int)));

    edtFightsCount->setText(r.value(2).toString());
    edtFightsWon->setText(r.value(3).toString());
    edtPlace->setText(r.value(4).toString());
    edtRegion->setText(r.value(5).toString());
    edtCity->setText(r.value(6).toString());
    edtNote->setText(r.value(7).toString());
}

bool CardPrzWin::IsValid() const
{
    return true;
}

bool CardPrzWin::Submit()
{
    QSqlQuery q("SELECT sc.id FROM sportsmen_competitions sc "
                "LEFT OUTER JOIN prize_winners pw ON pw.sportsman_competition_id = sc.id "
                "JOIN competitions c ON sc.competition_id = c.id "
                "JOIN sportsmen s ON sc.sportsman_id = s.id "
                "WHERE c.id = " + QString::number(vecCompId[cbComp->currentIndex()]) + " AND "
                "s.id = " + QString::number(vecSportId[cbSport->currentIndex()]));
    q.next();
    MapQuery mapQuery;
    mapQuery.insert(PairQuery("sportsman_competition_id", q.record().value(0).toString()), false);
    mapQuery.insert(PairQuery("fights_count", edtFightsCount->text()), false);
    mapQuery.insert(PairQuery("fights_won", edtFightsWon->text()), false);
    mapQuery.insert(PairQuery("place", edtPlace->text()), false);
    mapQuery.insert(PairQuery("region", edtRegion->text()), true);
    mapQuery.insert(PairQuery("city", edtCity->text()), true);
    mapQuery.insert(PairQuery("note", edtNote->text()), true);
    q.exec(CreateQuary(mapQuery));
    return true;
}

void CardPrzWin::UpdateCBSport(int aIndex)
{
    InitComboBox(cbSport, vecSportId,
                "SELECT s.id, s.name FROM sportsmen_competitions sc JOIN sportsmen s ON "
                "sc.sportsman_id = s.id WHERE sc.competition_id = " + QString::number(vecCompId[aIndex]),
                0);
}
