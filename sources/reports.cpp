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
    aCB->addItems(aLst);
    aCB->setInsertPolicy(QComboBox::NoInsert);
    aCB->setEditable(true);
    QCompleter *comp = new QCompleter(aLst);
    aCB->setCompleter(comp);
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

    QSqlQuery q;
    q.exec("SELECT * FROM coaches");
    QStringList lst;
    while (q.next())
    {
        vecId.push_back(q.record().value(0).toInt());
        lst.push_back(q.record().value(1).toString());
    }
    InitComboBox(cbCoach, lst);
}

void RepSport::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Sett::GetColName(ttSport, Sport::taCoach) + ":", cbCoach = new QComboBox, 0, 0);
    CreateBasicWidgets(lt);
}

QString RepSport::GetQuery()
{
    return "SELECT s.id, s.reg_number, s.name, s.birthday, s.address, s.phone, "
           "s.workplace, s.job, c.name, r.name FROM sportsmen s LEFT OUTER JOIN coaches c, "
           "ranks r ON s.coach_id = c.id AND s.rank_id = r.id WHERE c.id = " +
           QString::number(vecId[cbCoach->currentIndex()]) + ";";
}
