#include "reports.h"

extern void InitComboBox(QComboBox *aCB, QVector<int> &aVecId, const QString &aStrQ, int aCurId);

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

QAxObject *BaseReport::openDocument()
{
    excel = new QAxObject("Excel.Application", 0);
    excel->dynamicCall("SetVisible(bool)", true);
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add()");
    QAxObject *sheet = workbook->querySubObject("ActiveSheet");
    sheet->dynamicCall( "Select()" );
    return sheet;
}

QAxObject *BaseReport::getRange(const QString &range)
{
    return sheet->querySubObject("Range(const QString&)", range);
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
    writeBody(headers, sizeof(headers)/sizeof(*headers));
}

void SportsmenReport::writeBody(const char *headers[], uint length)
{
    sheet = openDocument();
    qDebug() << sizeof(headers);
    for(uint i = 0; i < length; ++i)
    {
        QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                 QString('A'+i) + QString::number(1));
        range->dynamicCall("SetValue(const QVariant&)", QObject::tr(headers[i]));
        range->querySubObject("Font")->setProperty("Bold", true);
        range->querySubObject("Borders")->setProperty("LineStyle", xlSingle);
    }
    int rowid = 2, fieldsCount = length;
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
        "Аттестуется на",
        "Примечание",
    };
    writeBody(headers, sizeof(headers)/sizeof(*headers));
}

void DrawingReport::writeHeader(const QString& category, const QDate &date)
{
    QAxObject *feder = getRange(QString("A%1:E%1").arg(QString::number(currentRow)));
    feder->dynamicCall("Merge()");
    feder->dynamicCall("SetValue(const QVariant&)",
        QObject::tr("Федерация КУДО Приморского края"));
    feder->setProperty("HorizontalAlignment", xlCenter);

    QAxObject *pageNumber = getRange(QString("F%1").arg(QString::number(currentRow)));
    pageNumber->dynamicCall("SetValue(const QVariant&)", QString::number(currentPage));
    pageNumber->setProperty("HorizontalAlignment", xlRight);
    currentRow++;

    QAxObject *protocol = getRange(QString("A%1:E%1").arg(QString::number(currentRow)));
    protocol->dynamicCall("Merge()");
    protocol->dynamicCall("SetValue(const QVariant&)", QObject::tr("ПРОТОКОЛ"));
    protocol->setProperty("HorizontalAlignment", xlCenter);
    currentRow++;

    QAxObject *protocolName = getRange(QString("A%1:E%1").arg(QString::number(currentRow)));
    protocolName->dynamicCall("Merge()");
    protocolName->dynamicCall("SetValue(const QVariant&)", QObject::tr("Взвешивания, мандатной комиссии и жеребьёвки"));
    protocolName->setProperty("HorizontalAlignment", xlCenter);
    currentRow++;

    QString curRow = QString::number(currentRow);
    QAxObject *daten = getRange(QString("A%1").arg(curRow));
    daten->dynamicCall("SetValue(const QVariant&)", QObject::tr("Дата"));

    QAxObject *dateval = getRange(QString("B%1").arg(curRow));
    dateval->dynamicCall("SetValue(const QVariant&)", date.toString("dd MMMM yyyy") + QObject::tr("г."));
    dateval->querySubObject("Borders(int)", xlEdgeBottom)->setProperty("LineStyle", xlSingle);

    QAxObject *categn = getRange(QString("C%1").arg(curRow));
    categn->dynamicCall("SetValue(const QVariant&)", QObject::tr("Категория"));

    QAxObject *categval = getRange(QString("D%1:F%1").arg(curRow));
    categval->dynamicCall("Merge()");
    categval->dynamicCall("SetValue(const QVariant&)", category);
    categval->setProperty("HorizontalAlignment", xlRight);
    categval->querySubObject("Borders(int)", xlEdgeBottom)->setProperty("LineStyle", xlSingle);

    QAxObject *style1[] = {feder, protocol, protocolName};
    for(int i = 0; i < sizeof(style1)/sizeof(*style1); ++i)
    {
        QAxObject *font = style1[i]->querySubObject("Font");
        font->setProperty("Name", QString("Arial Cyr"));
        font->setProperty("Size", 12);
        font->setProperty("Bold", true);
    }

    pageNumber->querySubObject("Font")->setProperty("Name", "Calibri");
    pageNumber->querySubObject("Font")->setProperty("Size", 11);

    QAxObject *font2 = getRange(QString("A%1:F%1").arg(curRow))->querySubObject("Font");
    font2->setProperty("Name", QString("Arial Cyr"));
    font2->setProperty("Size", 10);
    font2->setProperty("Bold", true);

    currentRow += 2;

    const char *headers[] = {
        "№ п/п",
        "ФИО",
        "Дата рожд.",
        "Команда/город",
        "Разряд\n(кю, дан)",
        "№ Жеребьёвки"
    };
    for(uint i = 0; i < sizeof(headers)/sizeof(*headers); ++i)
    {
        QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                 QString('A'+i) + QString::number(currentRow));
        range->dynamicCall("SetValue(const QVariant&)", QObject::tr(headers[i]));
        range->querySubObject("Borders")->setProperty("LineStyle", xlSingle);
    }
    QAxObject *font3 = getRange(QString("A%1:F%1").arg(QString::number(currentRow)))->querySubObject("Font");
    font3->setProperty("Name", QString("Arial Cyr"));
    font3->setProperty("Size", 10);
    font3->setProperty("Bold", true);
    currentRow++;
}

void DrawingReport::writeFooter(uint written)
{
    for(int i = written; i < 16; ++i, ++currentRow)
    {
        sheet->querySubObject("Range(const QString&)", QString('A') + QString::number(currentRow))
             ->dynamicCall("SetValue(const QVariant&)", QString("\n\n")+QString::number(i+1));
    }
    sheet->querySubObject("Range(const QString&)",
        QString('A') + QString::number(currentRow-16) + QString(":") + QString('A' + 5) + QString::number(currentRow-1))
        ->querySubObject("Borders")->setProperty("LineStyle", xlSingle);
    QAxObject *range1 = getRange(QString("A%1:A%2").arg(currentRow - 16).arg(currentRow - 1)),
              *range2 = getRange(QString("B%1:F%2").arg(currentRow - 16).arg(currentRow - 1));
    range1->setProperty("HorizontalAlignment", xlRight);
    QAxObject *font1 = range1->querySubObject("Font");
    font1->setProperty("Name", QString("Arial Cyr"));
    font1->setProperty("Size", 12);
    font1->setProperty("Bold", true);
    range2->setProperty("VerticalAlignment", xlTop);
    QAxObject *font2 = range2->querySubObject("Font");
    font2->setProperty("Name", QString("Calibri"));
    font2->setProperty("Size", 10);
    currentRow++;
    QAxObject *judge = getRange(QString("B%1").arg(currentRow));
    judge->dynamicCall("SetValue(const QVarialnt&)", QObject::tr("Гл. судья"));
    QAxObject *secr = getRange(QString("D%1:E%1").arg(currentRow));
    secr->dynamicCall("Merge()");
    secr->dynamicCall("SetValue(const QVarialnt&)", QObject::tr("Гл. секретарь"));
    QAxObject *js[] = {judge, secr};
    for(int i = 0; i < sizeof(js)/sizeof(*js); ++i)
    {
        js[i]->querySubObject("Borders(int)", xlEdgeBottom)->setProperty("LineStyle", xlSingle);
        QAxObject *font = js[i]->querySubObject("Font");
        font->setProperty("Name", "Arial Cyr");
        font->setProperty("Size", 10);
        font->setProperty("Bold", true);
    }
    currentRow += 7;
    currentPage++;
}

void DrawingReport::writeLine(uint written)
{
    sheet->querySubObject("Range(const QString&)", QString('A') + QString::number(currentRow))
         ->dynamicCall("SetValue(const QVariant&)", QString("\n\n")+QString::number(written+1));
    for(int i = 2, fieldsCount = query->record().count(); i < fieldsCount; ++i)
    {
        QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                 QString('A'+i-1) + QString::number(currentRow));
        range->dynamicCall("SetValue(const QVariant&)", QVariant(query->value(i).value<QString>()));
    }
    currentRow++;
}

void DrawingReport::makeReport()
{
    uint written = 0;
    QString category = "", vcat;
    currentRow = pageStartRow = currentPage = 1;
    sheet = openDocument();
    excel->querySubObject("ActiveWindow")->setProperty("Zoom", 85);
    while(query->next())
    {
        vcat = query->value(0).toString();
        if(currentRow == 1 || category != vcat || written == 16)
        {
            if(currentRow > 1)
                writeFooter(written);
            category = vcat;
            writeHeader(category, query->value(1).toDate());
            written = 0;
        }
        writeLine(written++);
    }
    writeFooter(written);
    sheet->querySubObject("Columns")->dynamicCall("AutoFit()");
}

/********************************************************************/
/******************************* View *******************************/
/********************************************************************/

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
    InitComboBox(cbCoach, vecId, "SELECT * FROM coaches", 0);

//    QSqlQuery q;
//    q.exec("SELECT * FROM coaches");
//    QStringList lst;
//    int id;
//    while (q.next())
//    {
//        id = q.record().value(0).toInt();
//        if(id)
//        {
//            vecId.push_back(id);
//            lst.push_back(q.record().value(1).toString());
//        }
//    }
//    InitComboBox(cbCoach, lst);
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

/******************************* Sertifications *******************************/

RepSert::RepSert(QWidget *aParent):
        Report(aParent, new CertificationReport)
{
    CreateWidgets();
    InitComboBox(cb, vecId, "SELECT * FROM coaches", 0);
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

    CreateBasicWidgets(lt);
}

void RepSert::ChangeTbl(int aIndex)
{
    if (!aIndex)
    {
        InitComboBox(cb, vecId, "SELECT * FROM coaches", 0);
    }
    else
    {
        InitComboBox(cb, vecId, "SELECT * FROM clubs", 0);
    }
    lbl->setText(cbTbl->currentText() + ":");
}

QString RepSert::GetQuery()
{
    if (!cbTbl->currentIndex())
    {
        return  "select sp.name, sp.birthday, r1.name, c.name, sp.reg_number, r2.name, se.note from sertifications se "
                "left outer join sportsmen sp, coaches c, ranks r1, ranks r2 on se.sportsman_id = sp.id and sp.coach_id = c.id "
                "and se.rank_from_id = r1.id and se.rank_to_id = r2.id where c.id = "
                + QString::number(vecId[cb->currentIndex()]) + ";";
    }
    return  "select sp.name, sp.birthday, r1.name, c.name, sp.reg_number, r2.name, se.note from sertifications se "
            "left outer join sportsmen sp, coaches c, ranks r1, ranks r2, clubs cl on se.sportsman_id = sp.id and "
            "sp.coach_id = c.id and se.rank_from_id = r1.id and se.rank_to_id = r2.id and c.club_id = cl.id where cl.id = "
            + QString::number(vecId[cb->currentIndex()]) + ";";
}

/******************************* Drawing *******************************/


RepDraw::RepDraw(QWidget *aParent):
        Report(aParent, new DrawingReport)
{
    CreateWidgets();
}

void RepDraw::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;

//    AddWidToLt(lt, tr("Выборка по:"), cbTbl = new QComboBox, 0, 0);
//    QStringList lst;
//    lst << Sett::GetColName(ttSport, Sport::taCoach) << Sett::GetColName(ttCoach, Coach::taClub);
//    cbTbl->addItems(lst);
//    connect(cbTbl, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeTbl(int)));

//    lbl = new QLabel(cbTbl->currentText() + ":");
//    AddWidToLt(lt, lbl, cb = new QComboBox, 1, 0);
//    InitComboBox(cb, GetLstRec("SELECT * FROM coaches", vecId));

    CreateBasicWidgets(lt);
}

QString RepDraw::GetQuery()
{
    return "select ca.name, co.date, s.name, s.birthday, cl.name, r.name "
           "from sportsmen_competitions sc inner join sportsmen s, coaches c, clubs cl, "
           "categories ca, competitions co, ranks r on "
           "sc.sportsman_id = s.id and s.coach_id = c.id and c.club_id = cl.id and sc.category_id = ca.id "
           "and sc.competition_id = co.id and s.rank_id = r.id "
           "order by ca.name";
}
