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

inline bool IsCBValid(QComboBox *aCB, bool aCanBeEmpty = true)
{
    return  (aCanBeEmpty && aCB->currentText().isEmpty()) ||
            (aCB->count() && aCB->currentText() == aCB->itemText(aCB->currentIndex()));
}

/******************************* Card (basic) *******************************/

Card::Card(QWidget *aParent, TableModel *aModel, TblType aType, int aId):
        QDialog(aParent),
        tblModel(aModel),
        type(aType),
        id(aId)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("Карточка - ") + Sett::GetTblTitle(type));
}

int Card::GetId() const
{
    return id;
}

TblType Card::GetType() const
{
    return type;
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
    if (tblModel) tblModel->Select();
    close();
}

void Card::closeEvent(QCloseEvent *aE)
{
    Sett::GetMA()->closeActiveSubWindow();
    aE->accept();
}

void Card::keyPressEvent(QKeyEvent *aE)
{
    if (aE->key() == Qt::Key_Escape)
    {
        close();
    }
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

inline QGroupBox *CardSport::_AddTable(TableView *aView, TableModel *aModel, const QString &aTitle)
{
    QGroupBox *gb = new QGroupBox(aTitle);
    QHBoxLayout *lt = new QHBoxLayout;
    lt->addWidget(aView);
    aView->setModel(aModel);
    gb->setLayout(lt);
    return gb;
}

CardSport::CardSport(QWidget *aParent, TableModel *aTblModel, int aId):
        Card(aParent, aTblModel, ttSport, aId)
{
    CreateWidgets();
    InitWidgets();
}

void CardSport::CreateWidgets()
{
    QHBoxLayout *ltName = new QHBoxLayout;
    QLabel *lblName = new QLabel(Sett::GetColName(ttSport, Sport::taName));
    edtName = new QLineEdit;
    lblName->setBuddy(edtName);
    ltName->addWidget(lblName);
    ltName->addWidget(edtName);

    QGridLayout *lt1 = new QGridLayout;

    AddWid(lt1, Sport::taBirth, edtDateBirth = new QDateEdit, 0, 0);
    edtDateBirth->setCalendarPopup(true);
    AddWid(lt1, Sport::taRegNum, edtRegNum = new QLineEdit, 0, 3);
    SetRegExprInt(edtRegNum);

    AddWid(lt1, Sport::taRank, cbRank = new QComboBox, 1, 0);
    QPushButton *btnRank = new QPushButton();
    lt1->addWidget(btnRank, 1, 2);
    connect(btnRank, SIGNAL(clicked()), this, SLOT(OpenCardRank()));
    AddWid(lt1, Sport::taCoach, cbCoach = new QComboBox, 1, 3);
    QPushButton *btnCoach = new QPushButton();
    lt1->addWidget(btnCoach, 1, 5);
    connect(btnCoach, SIGNAL(clicked()), this, SLOT(OpenCardCoach()));

    AddWid(lt1, Sport::taAddr, edtAddr = new QLineEdit, 2, 0);
    AddWid(lt1, Sport::taPhone, edtPhone = new QLineEdit, 2, 3);

    AddWid(lt1, Sport::taWork, edtWorkplace = new QLineEdit, 3, 0);
    AddWid(lt1, Sport::taJob, edtJob = new QLineEdit, 3, 3);

    QVBoxLayout *lt = new QVBoxLayout;
    lt->addLayout(ltName);
    lt->addLayout(lt1);
    lt->addLayout(CreateInnerTbls());

    CreateBasicWidgets(lt);
}

QVBoxLayout *CardSport::CreateInnerTbls()
{
    QVBoxLayout *lt2 = new QVBoxLayout;

    lt2->addWidget(_AddTable(viewSert = new TableView,
                             modelSert = new TableModel(this), Sett::GetTblTitle(ttSert)));
    lt2->addWidget(_AddTable(viewPrzWin = new TableView,
                             modelPrzWin = new TableModel(this), tr("Спортивные достижения")));
    lt2->addWidget(_AddTable(viewFee = new TableView,
                             modelFee = new TableModel(this), Sett::GetTblTitle(ttFee)));

    modelSert->SetQuery("SELECT se.id, se.sportsman_id, se.date, r1.name, r2.name, se.note FROM sertifications se "
                        "JOIN ranks r2 ON se.rank_to_id = r2.id "
                        "LEFT OUTER JOIN ranks r1 ON se.rank_from_id = r1.id "
                        "WHERE se.sportsman_id = " + QString::number(GetId()));
    modelSert->Select();

    modelPrzWin->SetQuery("SELECT pw.id, c.name, c.date, sc.sportsman_id, pw.fights_count, pw.fights_won, pw.place, pw.region, "
                          "pw.city, pw.note FROM prize_winners pw "
                          "JOIN sportsmen_competitions sc ON pw.sportsman_competition_id = sc.id "
                          "JOIN competitions c ON sc.competition_id = c.id "
                          "WHERE sc.sportsman_id = " + QString::number(GetId()));
    modelPrzWin->Select();

    modelFee->SetQuery("SELECT id, sportsman_id, date, note FROM fee "
                       "WHERE sportsman_id = " + QString::number(GetId()));
    modelFee->Select();

    viewSert->setColumnHidden(Sert::taId, true);
    viewSert->setColumnHidden(Sert::taSport, true);
    viewPrzWin->setColumnHidden(PrzWin::taId, true);
    viewPrzWin->setColumnHidden(PrzWin::taSport, true);
    viewFee->setColumnHidden(Fee::taId, true);
    viewFee->setColumnHidden(Fee::taSport, true);

    return lt2;
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
    edtNote->setText(r.value(9).toString());
}

bool CardSport::IsValid() const
{
    return  !CheckCond(edtName->text().isEmpty(), tr("Введите Ф.И.О. спортсмена")) &&
            !CheckCond(!IsCBValid(cbRank), tr("Выбранный разряд отсутствует в базе")) &&
            !CheckCond(!IsCBValid(cbCoach), tr("Выбранный тренет отсутствует в базе"));
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

void CardSport::OpenCardRank()
{
    if (!IsCBValid(cbRank, false)) return;
    int id = vecRankId[cbRank->currentIndex()];
    if (mapperCard.SetCard(ttRank, id)) return;
    mapperCard.InsertCard(ttRank, id, new CardRank(Sett::GetMA(), 0, id), this);
}

void CardSport::OpenCardCoach()
{
    if (!IsCBValid(cbCoach, false)) return;
    int id = vecCoachId[cbCoach->currentIndex()];
    if (mapperCard.SetCard(ttCoach, id)) return;
    mapperCard.InsertCard(ttCoach, id, new CardCoach(Sett::GetMA(), 0, id), this);
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
    QPushButton *btnClub = new QPushButton();
    lt->addWidget(btnClub, 2, 2);
    connect(btnClub, SIGNAL(clicked()), this, SLOT(OpenCardClub()));

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
    return !CheckCond(edtName->text().isEmpty(), tr("Введите Ф.И.О. тренера")) &&
           !CheckCond(!IsCBValid(cbClub), tr("Выбранный клуб отсутствует в базе"));
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

void CardCoach::OpenCardClub()
{
    if (!IsCBValid(cbClub, false)) return;
    int id = vecClubId[cbClub->currentIndex()];
    if (mapperCard.SetCard(ttClub, id)) return;
    mapperCard.InsertCard(ttClub, id, new CardClub(Sett::GetMA(), 0, id), this);
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
    QPushButton *btnSport = new QPushButton();
    lt->addWidget(btnSport, 1, 2);
    connect(btnSport, SIGNAL(clicked()), this, SLOT(OpenCardSport()));

    AddWid(lt, Sert::taDate, edtDate = new QDateEdit, 2);
    edtDate->setCalendarPopup(true);

    AddWid(lt, Sert::taRankFrom, cbRankFrom = new QComboBox, 3);
    QPushButton *btnRankFrom = new QPushButton();
    lt->addWidget(btnRankFrom, 3, 2);
    connect(btnRankFrom, SIGNAL(clicked()), this, SLOT(OpenCardRankFrom()));

    AddWid(lt, Sert::taRankTo, cbRankTo = new QComboBox, 4);
    QPushButton *btnRankTo = new QPushButton();
    lt->addWidget(btnRankTo, 4, 2);
    connect(btnRankTo, SIGNAL(clicked()), this, SLOT(OpenCardRankTo()));

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
    return  !CheckCond(!IsCBValid(cbSport, false), tr("Спортсмен либо не выбран, либо отстутствует в базе")) &&
            !CheckCond(!IsCBValid(cbRankFrom), tr("Выбранный текущий разряд спортсмена отстутствует в базе")) &&
            !CheckCond(!IsCBValid(cbRankTo, false), tr("Разряд, на который спортмен аттестуется, "
                                                       "либо не выбран, либо отстутствует в базе"));
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

void CardSert::OpenCardSport()
{
    if (!IsCBValid(cbSport, false)) return;
    int id = vecSportId[cbSport->currentIndex()];
    if (mapperCard.SetCard(ttSport, id)) return;
    mapperCard.InsertCard(ttSport, id, new CardSport(Sett::GetMA(), 0, id), this);
}

void CardSert::OpenCardRankFrom()
{
    if (!IsCBValid(cbRankFrom, false)) return;
    int id = vecRankFromId[cbRankFrom->currentIndex()];
    if (mapperCard.SetCard(ttRank, id)) return;
    mapperCard.InsertCard(ttRank, id, new CardRank(Sett::GetMA(), 0, id), this);
}

void CardSert::OpenCardRankTo()
{
    if (!IsCBValid(cbRankTo, false)) return;
    int id = vecRankToId[cbRankTo->currentIndex()];
    if (mapperCard.SetCard(ttRank, id)) return;
    mapperCard.InsertCard(ttRank, id, new CardRank(Sett::GetMA(), 0, id), this);
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
    QPushButton *btnSport = new QPushButton();
    lt->addWidget(btnSport, 0, 2);
    connect(btnSport, SIGNAL(clicked()), this, SLOT(OpenCardSport()));

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
    return !CheckCond(!IsCBValid(cbSport, false), tr("Спортсмен либо не выбран, либо отстутствует в базе"));
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

void CardFee::OpenCardSport()
{
    if (!IsCBValid(cbSport, false)) return;
    int id = vecSportId[cbSport->currentIndex()];
    if (mapperCard.SetCard(ttSport, id)) return;
    mapperCard.InsertCard(ttSport, id, new CardSport(Sett::GetMA(), 0, id), this);
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
    QPushButton *btnSport = new QPushButton();
    lt->addWidget(btnSport, 0, 2);
    connect(btnSport, SIGNAL(clicked()), this, SLOT(OpenCardSport()));

    AddWid(lt, SportComp::taComp, cbComp = new QComboBox, 1);
    QPushButton *btnComp = new QPushButton();
    lt->addWidget(btnComp, 1, 2);
    connect(btnComp, SIGNAL(clicked()), this, SLOT(OpenCardComp()));

    AddWid(lt, SportComp::taCateg, cbCateg = new QComboBox, 2);
    QPushButton *btnCateg = new QPushButton();
    lt->addWidget(btnCateg, 2, 2);
    connect(btnCateg, SIGNAL(clicked()), this, SLOT(OpenCardCateg()));

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
    if (CheckCond(!IsCBValid(cbSport, false), tr("Спортсмен либо не выбран, либо отстутствует в базе")) ||
        CheckCond(!IsCBValid(cbComp, false), tr("Соревнование либо не выбрано, либо отстутствует в базе")) ||
        CheckCond(!IsCBValid(cbCateg), tr("Категория отстутствует в базе")))
    {
        return false;
    }
    QSqlQuery q("SELECT * FROM sportsmen_competitions WHERE "
                "id <> " + QString::number(GetId()) + " AND "
                "sportsman_id = " + QString::number(vecSportId[cbSport->currentIndex()]) + " AND "
                "competition_id = " + QString::number(vecCompId[cbComp->currentIndex()]));

    return !CheckCond(q.next(),
                      tr("В базе уже есть запись, отражающае участие выбранного спортсмена в выбранном соревновании"));
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

void CardSportComp::OpenCardSport()
{
    if (!IsCBValid(cbSport, false)) return;
    int id = vecSportId[cbSport->currentIndex()];
    if (mapperCard.SetCard(ttSport, id)) return;
    mapperCard.InsertCard(ttSport, id, new CardSport(Sett::GetMA(), 0, id), this);
}

void CardSportComp::OpenCardComp()
{
    if (!IsCBValid(cbComp, false)) return;
    int id = vecCompId[cbComp->currentIndex()];
    if (mapperCard.SetCard(ttComp, id)) return;
    mapperCard.InsertCard(ttComp, id, new CardComp(Sett::GetMA(), 0, id), this);
}

void CardSportComp::OpenCardCateg()
{
    if (!IsCBValid(cbCateg, false)) return;
    int id = vecCategId[cbCateg->currentIndex()];
    if (mapperCard.SetCard(ttCateg, id)) return;
    mapperCard.InsertCard(ttCateg, id, new CardCateg(Sett::GetMA(), 0, id), this);
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
    connect(edtName, SIGNAL(returnPressed()), this, SLOT(UpdateNameProt()));
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
    return  !CheckCond(edtName->text().isEmpty(), tr("Введите название соревнования")) &&
            !CheckCond(edtNameProt->text().isEmpty(),
                       tr("Введите название соревнования, как оно будет отображаться в протоколах"));
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

void CardComp::UpdateNameProt()
{
    if (edtName->text().isEmpty()) return;
    int button = QMessageBox::question(this,
        tr("Подтверждение копирования"),
        tr("Вы хотите скопировать введенное название в название для протоколов?"),
            QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes)
    {
        edtNameProt->setText(edtName->text());
    }
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
    QPushButton *btnComp = new QPushButton();
    lt->addWidget(btnComp, 0, 2);
    connect(btnComp, SIGNAL(clicked()), this, SLOT(OpenCardComp()));

    AddWid(lt, PrzWin::taSport, cbSport = new QComboBox, 1, 0);
    QPushButton *btnSport = new QPushButton();
    lt->addWidget(btnSport, 1, 2);
    connect(btnSport, SIGNAL(clicked()), this, SLOT(OpenCardSport()));

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
                "FROM prize_winners pw "
                "JOIN sportsmen_competitions sc ON pw.sportsman_competition_id = sc.id "
                "WHERE pw.id = " + QString::number(id));
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
    if (CheckCond(!IsCBValid(cbSport, false), tr("Спортсмен либо не выбран, либо отстутствует в базе")) ||
        CheckCond(!IsCBValid(cbComp, false), tr("Соревнование либо не выбрано, либо отстутствует в базе")))
    {
        return false;
    }
    QSqlQuery q("SELECT sc.id FROM sportsmen_competitions sc "
                "LEFT OUTER JOIN prize_winners pw ON pw.sportsman_competition_id = sc.id "
                "JOIN competitions c ON sc.competition_id = c.id "
                "JOIN sportsmen s ON sc.sportsman_id = s.id "
                "WHERE pw.id <> " + QString::number(GetId()) + " AND "
                "c.id = " + QString::number(vecCompId[cbComp->currentIndex()]) + " AND "
                "s.id = " + QString::number(vecSportId[cbSport->currentIndex()]));
    return !CheckCond(q.next(),
                      tr("В базе уже есть запись, отражающае призовое место выбранного спортсмена в выбранном соревновании"));
}

bool CardPrzWin::Submit()
{
    QSqlQuery q("SELECT sc.id FROM sportsmen_competitions sc "
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
                "SELECT s.id, s.name FROM sportsmen_competitions sc "
                "JOIN sportsmen s ON sc.sportsman_id = s.id "
                "WHERE sc.competition_id = " + QString::number(vecCompId[aIndex]),
                0);
}

void CardPrzWin::OpenCardComp()
{
    if (!IsCBValid(cbComp, false)) return;
    int id = vecCompId[cbComp->currentIndex()];
    if (mapperCard.SetCard(ttComp, id)) return;
    mapperCard.InsertCard(ttComp, id, new CardComp(Sett::GetMA(), 0, id), this);
}

void CardPrzWin::OpenCardSport()
{
    if (!IsCBValid(cbSport, false)) return;
    int id = vecSportId[cbSport->currentIndex()];
    if (mapperCard.SetCard(ttSport, id)) return;
    mapperCard.InsertCard(ttSport, id, new CardSport(Sett::GetMA(), 0, id), this);
}

/******************************* Mapper card *******************************/

MapperCard mapperCard;

MapperCard::MapperCard()
{
    //emty
}

void MapperCard::InsertCard(TblType aType, int aId, Card *aCard, QWidget *aParent)
{
    mapCard.insert(KeyMapCard_(aType, aId), ValMapCard_(aCard, aParent));
    connect(aCard, SIGNAL(destroyed(QObject *)), this, SLOT(CloseCard(QObject *)));
    QMdiSubWindow *sw = Sett::GetMA()->addSubWindow(aCard);
    sw->show();
}

bool MapperCard::SetCard(TblType aType, int aId)
{
    MapCard_::const_iterator it = mapCard.find(KeyMapCard_(aType, aId));
    if (it != mapCard.end())       //if card already opened
    {
        it.value().first->setFocus();
        return true;
    }
    return false;
}

void MapperCard::CloseCard(QObject *aObj)
{
    Card *c = static_cast<Card *>(aObj);
    MapCard_::iterator it = mapCard.find(KeyMapCard_(c->GetType(), c->GetId()));
    if (it != mapCard.end())
    {
        QWidget *w = it.value().second;
        mapCard.erase(it);
        if (qobject_cast<QWidget *>(w)) w->setFocus();
    }
}
