#include "reports.h"
#include <QAxObject>

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

void SportsMen::makeReport()
{
    QAxObject *excel = new QAxObject("Excel.Application", 0);
    excel->dynamicCall("SetVisible(bool)", true);
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add()");
    QAxObject *sheet = workbook->querySubObject("ActiveSheet");
    sheet->dynamicCall( "Select()" );
// Adjust columns
    QString headers[] = {
                         QObject::tr("№"),
                         QObject::tr("РегНомер"),
                         QObject::tr("ФИО"),
                         QObject::tr("Дата рождения"),
                         QObject::tr("Адрес"),
                         QObject::tr("Телефон"),
                         QObject::tr("Место р/уч"),
                         QObject::tr("Должность"),
                         QObject::tr("Тренер"),
                         QObject::tr("Разряд"),
                        };
    for(int i = 0; i < sizeof(headers) / sizeof(QString); ++i)
    {
        QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                 QString('A'+i) + QString::number(1));
        range->dynamicCall("SetValue(const QVariant&)", QVariant(headers[i]));
        range->querySubObject("Font")->setProperty("Bold", true);
    }
    int rowid = 2;
    qDebug() << "Vasay";
    while(query->next())
    {
        qDebug() << "Vasay";
        for(int i = 0; i < query->record().count(); ++i)
        {
            QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                     QString('A'+i) + QString::number(rowid));
            range->dynamicCall("SetValue(const QVariant&)", QVariant(query->value(i).value<QString>()));
        }
        rowid++;
    }
    sheet->querySubObject("Columns")->dynamicCall("AutoFit()");
}

/********************************************************************/
/******************************* View *******************************/
/********************************************************************/

inline void InitComboBox(QComboBox *aCB, const QStringList &aLst)
{
    aCB->clear();
    aCB->addItems(aLst);
    aCB->setInsertPolicy(QComboBox::NoInsert);
    aCB->setEditable(true);
    QCompleter *comp = new QCompleter(aLst);
    aCB->setCompleter(comp);
}

QStringList GetLstRec(const QString &aStrQ, QVector<int> &aVecId)
{
    aVecId.clear();
    QSqlQuery q(aStrQ);
    QStringList lst;
    while (q.next())
    {
        aVecId.push_back(q.record().value(0).toInt());
        lst.push_back(q.record().value(1).toString());
    }
    return lst;
}

Report::Report(QWidget *aParent, BaseReport *aLogRep):
        QDialog(aParent),
        logRep(aLogRep),
        query(new QSqlQuery)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

Report::~Report()
{
    delete query;
}

void Report::CreateBasicWidgets(QGridLayout *aLt)
{
    QVBoxLayout *lt = new QVBoxLayout;
    lt->addLayout(aLt);

    QHBoxLayout *lt1 = new QHBoxLayout;
    btnExport = new QPushButton(tr("Выгрузить"));
    lt1->addStretch(1);
    lt1->addWidget(btnExport);
    lt1->addStretch(0);
    connect(btnExport, SIGNAL(clicked()), this, SLOT(Export()));

    lt->addLayout(aLt);
    lt->addLayout(lt1);

    setLayout(lt);
}

void Report::closeEvent(QCloseEvent *aE)
{
    Sett::GetMA()->closeActiveSubWindow();
    aE->accept();
}

void Report::Export()
{
    query->exec(GetQuery());
    logRep->setQuery(query);
    logRep->makeReport();
}

QString Report::GetQuery()
{
    return "";
}

/******************************* Sportsmen *******************************/

RepSport::RepSport(QWidget *aParent):
        Report(aParent, new SportsMen)
{
    CreateWidgets();
}

void RepSport::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Sett::GetColName(ttSport, Sport::taCoach) + ":", cbCoach = new QComboBox, 0, 0);
    InitComboBox(cbCoach, GetLstRec("SELECT * FROM coaches", vecId));
    CreateBasicWidgets(lt);
}

QString RepSport::GetQuery()
{
    return "SELECT s.id, s.reg_number, s.name, s.birthday, s.address, s.phone, "
           "s.workplace, s.job, c.name, r.name FROM sportsmen s LEFT OUTER JOIN coaches c, "
           "ranks r ON s.coach_id = c.id AND s.rank_id = r.id WHERE c.id = " +
           QString::number(vecId[cbCoach->currentIndex()]) + ";";
}

/******************************* Sertifications *******************************/

RepSert::RepSert(QWidget *aParent):
        Report(aParent, new SportsMen) //Must be modified for sertifications
{
    CreateWidgets();
}

void RepSert::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;

    AddWidToLt(lt, tr("Выборка по:"), cbTbl = new QComboBox, 0, 0);
    QStringList lst;
    lst << Sett::GetColName(ttSport, Sport::taCoach) << Sett::GetColName(ttCoach, Coach::taClub);
    cbTbl->addItems(lst);
    connect(cbTbl, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeTbl(int)));

    lbl = new QLabel(cbTbl->currentText() + ":");
    AddWidToLt(lt, lbl, cb = new QComboBox, 1, 0);
    InitComboBox(cb, GetLstRec("SELECT * FROM coaches", vecId));

    CreateBasicWidgets(lt);
}

void RepSert::ChangeTbl(int aIndex)
{
    if (!aIndex)
    {
        InitComboBox(cb, GetLstRec("SELECT * FROM coaches", vecId));
    }
    else
    {
        InitComboBox(cb, GetLstRec("SELECT * FROM clubs", vecId));
    }
    lbl->setText(cbTbl->currentText() + ":");
}

QString RepSert::GetQuery()
{
    if (!cbTbl->currentIndex())
    {
        return  "select sp.name, sp.birthday, c.name, sp.reg_number, r1.name, r2.name, se.note from sertifications se "
                "left outer join sportsmen sp, coaches c, ranks r1, ranks r2 on se.sportsman_id = sp.id and sp.coach_id = c.id "
                "and se.rank_from_id = r1.id and se.rank_to_id = r2.id where c.id = " +
                + QString::number(vecId[cb->currentIndex()]) + ";";
    }
    return "";
}

