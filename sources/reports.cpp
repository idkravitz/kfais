#include "reports.h"

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

QAxObject *BaseReport::openDocument()
{
    QAxObject *excel = new QAxObject("Excel.Application", 0);
    excel->dynamicCall("SetVisible(bool)", true);
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add()");
    QAxObject *sheet = workbook->querySubObject("ActiveSheet");
    sheet->dynamicCall( "Select()" );
    return sheet;
}


void SportsmenReport::makeReport()
{
    const char *headers[] = {
        "РегНомер",
        "ФИО",
        "Дата рождения",
        "Адрес",
        "Телефон",
        "Место р/уч",
        "Должность",
        "Тренер",
        "Разряд",
    };
    writeBody(headers);
}

void SportsmenReport::writeBody(const char *headers[])
{
    QAxObject *sheet = openDocument();
    for(uint i = 0; i < sizeof(headers) / sizeof(*headers); ++i)
    {
        QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                 QString('A'+i) + QString::number(1));
        range->dynamicCall("SetValue(const QVariant&)", QString(headers[i]));
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

void CertificationReport::makeReport()
{
    const char* headers[] = {
        "ФИО",
        "Дата рождения",
        "Разряд",
        "Тренер",
        "Рег. №",
        "Аттестуется на"
    };
    writeBody(headers);
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
        Report(aParent, new SportsmenReport)
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
    InitComboBox(cbCoach, GetLstRec("SELECT * FROM coaches", vecId));
    CreateBasicWidgets(lt);
}

QString RepSport::GetQuery()
{
    return "SELECT s.reg_number, s.name, s.birthday, s.address, s.phone, "
           "s.workplace, s.job, c.name, r.name FROM sportsmen s LEFT OUTER JOIN coaches c, "
           "ranks r ON s.coach_id = c.id AND s.rank_id = r.id WHERE s.id <> 0 and c.id = " +
           QString::number(vecId[cbCoach->currentIndex()]) + ";";
}

/******************************* Sertifications *******************************/

RepSert::RepSert(QWidget *aParent):
        Report(aParent, new SportsmenReport) //Must be modified for sertifications
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
    return "";
//    return "SELECT s.id, s.reg_number, s.name, s.birthday, s.address, s.phone, "
//           "s.workplace, s.job, c.name, r.name FROM sportsmen s LEFT OUTER JOIN coaches c, "
//           "ranks r ON s.coach_id = c.id AND s.rank_id = r.id WHERE c.id = " +
//           QString::number(vecId[cb->currentIndex()]) + ";";
}

