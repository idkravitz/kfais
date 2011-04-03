#include "reports.h"
#include <QAxObject>

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

void SportsMen::makeReport()
{
    //const int xlDouble = -4119;
    const int xlSingle = 1;
    QAxObject *excel = new QAxObject("Excel.Application", 0);
    excel->dynamicCall("SetVisible(bool)", true);
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add()");
    QAxObject *sheet = workbook->querySubObject("ActiveSheet");
    sheet->dynamicCall( "Select()" );
// Adjust columns
    QString headers[] = {
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
    for(uint i = 0; i < sizeof(headers) / sizeof(QString); ++i)
    {
        QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                 QString('A'+i) + QString::number(1));
        range->dynamicCall("SetValue(const QVariant&)", QVariant(headers[i]));
        range->querySubObject("Font")->setProperty("Bold", true);
        range->querySubObject("Borders")->setProperty("LineStyle", xlSingle);
    }
    int rowid = 2, fieldsCount;
    while(query->next())
    {
        fieldsCount = query->record().count();
        for(int i = 0; i < fieldsCount; ++i)
        {
            QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                     QString('A'+i) + QString::number(rowid));
            range->dynamicCall("SetValue(const QVariant&)", QVariant(query->value(i).value<QString>()));
        }
        rowid++;
    }
    QAxObject *exported = sheet->querySubObject("Range(const QString&)",
                            (QString("A2:") + (QString('A'+(fieldsCount-1)) + QString::number(rowid-1))));
    exported->querySubObject("Borders")->setProperty("LineStyle", xlSingle);

    QAxObject *font = exported->querySubObject("Font");
    font->setProperty("Name", QObject::tr("Arial"));
    font->setProperty("Size", 10);

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
    int id;
    while (q.next())
    {
        id = q.record().value(0).toInt();
        if(id)
        {
            vecId.push_back(id);
            lst.push_back(q.record().value(1).toString());
        }
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
    return "SELECT s.reg_number, s.name, s.birthday, s.address, s.phone, "
           "s.workplace, s.job, c.name, r.name FROM sportsmen s LEFT OUTER JOIN coaches c, "
           "ranks r ON s.coach_id = c.id AND s.rank_id = r.id WHERE s.id <> 0 and c.id = " +
           QString::number(vecId[cbCoach->currentIndex()]) + ";";
}
