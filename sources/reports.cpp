#include "reports.h"
#include "card.h"

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

QString genitiveDate(const QDate &date)
{
    const char *months[12] = {
        "января",
        "февраля",
        "марта",
        "апреля",
        "мая",
        "июня",
        "июля",
        "августа",
        "сентября",
        "октября",
        "ноября",
        "декабря"
    };
    return date.isValid() ?
        QString("%1 %2 %3").arg(date.day()).arg(QObject::tr(months[date.month() - 1])).arg(date.year()) + QObject::tr("г."):
        QString();
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
    dateval->dynamicCall("SetValue(const QVariant&)", genitiveDate(date));
    dateval->querySubObject("Borders(int)", xlEdgeBottom)->setProperty("LineStyle", xlSingle);

    QAxObject *categn = getRange(QString("C%1").arg(curRow));
    categn->dynamicCall("SetValue(const QVariant&)", QObject::tr("Категория"));

    QAxObject *categval = getRange(QString("D%1:F%1").arg(curRow));
    categval->dynamicCall("Merge()");
    categval->dynamicCall("SetValue(const QVariant&)", category);
    categval->setProperty("HorizontalAlignment", xlRight);
    categval->querySubObject("Borders(int)", xlEdgeBottom)->setProperty("LineStyle", xlSingle);

    QAxObject *style1[] = {feder, protocol, protocolName};
    for(uint i = 0; i < sizeof(style1)/sizeof(*style1); ++i)
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
    QAxObject *range3 = getRange(QString("A%1:F%1").arg(QString::number(currentRow))),
              *range4 = getRange(QString("A%1:F%1").arg(QString::number(currentRow)));
    range3->setProperty("RowHeight", 26.25);
    range4->setProperty("WrapText", true);
    QAxObject *font3 = range3->querySubObject("Font");
    font3->setProperty("Name", QString("Arial Cyr"));
    font3->setProperty("Size", 10);
    font3->setProperty("Bold", true);
    getRange(QString("F%1").arg(currentRow))->setProperty("WrapText", false);
    currentRow++;
}

void DrawingReport::writeFooter(uint written)
{
    for(int i = written; i < 16; ++i, ++currentRow)
    {
        QAxObject *range = sheet->querySubObject("Range(const QString&)", QString('A') + QString::number(currentRow));
        range->dynamicCall("SetValue(const QVariant&)", QString::number(i+1));
    }
    QAxObject *range0 = sheet->querySubObject("Range(const QString&)",
        QString('A') + QString::number(currentRow-16) + QString(":") + QString('A' + 5) + QString::number(currentRow-1));
    range0->querySubObject("Borders")->setProperty("LineStyle", xlSingle);
    range0->setProperty("RowHeight", 39);
    range0->setProperty("WrapText", true);
    QAxObject *range1 = getRange(QString("A%1:A%2").arg(currentRow - 16).arg(currentRow - 1)),
              *range2 = getRange(QString("B%1:F%2").arg(currentRow - 16).arg(currentRow - 1)),
              *range3 = getRange(QString("A%1:F%2").arg(currentRow - 16).arg(currentRow - 1));
    range3->setProperty("WrapText", true);
    range1->setProperty("HorizontalAlignment", xlRight);
    range1->setProperty("VerticalAlignment", xlBottom);
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
    for(uint i = 0; i < sizeof(js)/sizeof(*js); ++i)
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
         ->dynamicCall("SetValue(const QVariant&)", QString::number(written+1));
    for(int i = 2, fieldsCount = query->record().count(); i < fieldsCount; ++i)
    {
        QAxObject *range = sheet->querySubObject("Range(const QString&)",
                                                 QString('A'+i-1) + QString::number(currentRow));
        range->dynamicCall("SetValue(const QVariant&)",
            (i != 3 ? query->value(i).value<QString>() : query->value(i).value<QDate>().toString("dd.MM.yyyy")));
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
    const double widths[] = {
        6.29,
        30.29,
        11.14,
        18.71,
        12.29,
        14.71
    };
    for(uint i = 0; i < sizeof(widths)/sizeof(*widths); ++i)
    {
        sheet->querySubObject("Columns(const QString&)", QString("%1:%1").arg(QString('A' + i)))
             ->setProperty("ColumnWidth", widths[i]);
    }
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

    sheet->querySubObject("PageSetup")->setProperty("Zoom", 89);
    sheet->querySubObject("PageSetup")->setProperty("PrintQuality", 600);
}

void PulkaReport::writeHeader(const QString &category, const QString &competition, const QDate &date)
{
    uint offset = (currentPage - 1) * pageHeight + 1;
    QAxObject *range = getRange(QString("A%1:M%1").arg(offset));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("Протокол хода ") + competition);
    offset++;

    range = getRange(QString("D%1:E%1").arg(offset));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("Категория"));

    range = getRange(QString("F%1:K%1").arg(offset));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)", category);

    range = getRange(QString("L%1").arg(offset));
    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("г. Владивосток"));

    range = getRange(QString("M%1").arg(offset));
    range->dynamicCall("SetValue(const QVariant&)", date.toString("dd.MM.yyyy") + QObject::tr("г."));
    offset++;

    range = getRange(QString("A%1").arg(offset));
    range->dynamicCall("SetValue(const QVariant&)", QString::number(currentPage));
    range = getRange(QString("A%1:M%2").arg(offset-2).arg(offset));
    range->querySubObject("Font")->setProperty("Name", "Calibri");
    range->querySubObject("Font")->setProperty("Size", 11);
    offset++;
    for(int i = 0; i < 8; ++i, offset += 4)
    {
        QAxObject *range = getRange(QString("A%1:B%2").arg(offset).arg(offset + 1));
        range->dynamicCall("Merge()");
        range->querySubObject("Borders")->setProperty("LineStyle", xlSingle);
        range->setProperty("WrapText", true);

        range = getRange(QString("L%1:M%2").arg(offset).arg(offset + 1));
        range->dynamicCall("Merge()");
        range->querySubObject("Borders")->setProperty("LineStyle", xlSingle);
        range->setProperty("WrapText", true);
    }
}

void PulkaReport::writeRec(uint draw_number)
{
    bool right = draw_number > 8;
    draw_number = (draw_number - 1) % 8;
    uint offset = (currentPage - 1) * pageHeight + firstRecOffset + draw_number * 4;
    QAxObject *range = getRange((right ? QString("L%1:M%2") : QString("A%1:B%2")).arg(offset).arg(offset + 1));
    range->dynamicCall("SetValue(const QVariant&)",
        query->value(3).toString() + " " + query->value(4).toString() + " " + query->value(5).toString());
}

void PulkaReport::writeFooter()
{
    uint offset = currentPage * pageHeight;
    QAxObject *l1 = getRange(QString("A%1").arg(offset));
    QAxObject *l2 = getRange(QString("H%1:J%1").arg(offset));

    l1->dynamicCall("SetValue(const QVariant&)", QObject::tr("Гл. судья"));
    l2->dynamicCall("Merge()");
    l2->dynamicCall("SetValue(const QVariant&)", QObject::tr("Секретарь"));
    l1->querySubObject("Borders(int)", xlEdgeBottom)->setProperty("LineStyle", xlSingle);
    l2->querySubObject("Borders(int)", xlEdgeBottom)->setProperty("LineStyle", xlSingle);
    l1->querySubObject("Font")->setProperty("Name", "Arial Cyr");
    l2->querySubObject("Font")->setProperty("Name", "Arial Cyr");
    l1->querySubObject("Font")->setProperty("Size", 11);
    l2->querySubObject("Font")->setProperty("Size", 11);

    uint fstMainRow = (currentPage - 1) * pageHeight + firstRecOffset,
         lstMainRow = offset - 3;

    QAxObject *grid = getRange(QString("C%1:K%2").arg(fstMainRow).arg(lstMainRow));
    grid->querySubObject("Borders")->setProperty("LineStyle", xlContinious);
    grid->querySubObject("Borders")->setProperty("Weight", xlHairline);

    QAxObject *lCol = getRange(QString("A%1:B%2").arg(fstMainRow).arg(lstMainRow)),
              *rCol = getRange(QString("L%1:M%2").arg(fstMainRow).arg(lstMainRow));
    lCol->querySubObject("Font")->setProperty("Name", "Arial Cyr");
    rCol->querySubObject("Font")->setProperty("Name", "Arial Cyr");
    lCol->querySubObject("Font")->setProperty("Size", 12);
    rCol->querySubObject("Font")->setProperty("Size", 12);

    currentPage++;
}


void PulkaReport::makeReport()
{
    QString category = "", vcat;
    sheet = openDocument();
    currentPage = 1;
    bool start = true;
    uint draw_number;
    excel->querySubObject("ActiveWindow")->setProperty("Zoom", 75);
    const double widths[] = {
        21.29,
        13.29,
        7,
        7,
        7,
        7,
        7,
        7,
        7,
        7,
        7,
        21.29,
        13.29,
    };
    for(uint i = 0; i < sizeof(widths)/sizeof(*widths); ++i)
    {
        sheet->querySubObject("Columns(const QString&)", QString("%1:%1").arg(QString('A' + i)))
             ->setProperty("ColumnWidth", widths[i]);
    }
    while(query->next())
    {
        vcat = query->value(2).toString();
        draw_number = query->value(6).toUInt();
        if(start || category != vcat || draw_number > 16)
        {
            if(!start)
            {
                writeFooter();
            }
            else
            {
                start = false;
            }
            if(draw_number > 16)
                draw_number -= 16;
            category = vcat;
            writeHeader(category, query->value(0).toString(), query->value(1).toDate());
        }
        writeRec(draw_number);
    }
    writeFooter();
    sheet->querySubObject("PageSetup")->setProperty("Zoom", 90);
    sheet->querySubObject("PageSetup")->setProperty("Orientation", xlLandscape);
    sheet->querySubObject("PageSetup")->setProperty("PrintQuality", 600);
}

void ResultsReport::writeHeader(const QString &category, const QString &competition, const QDate &date)
{
    uint offset = (currentPage - 1) * pageHeight + 1;
    QAxObject *range = getRange(QString("A%1:K%1").arg(offset));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("Протокол результатов соревнований"));
    range->setProperty("HorizontalAlignment", xlCenter);
    range->querySubObject("Font")->setProperty("Name", "Times New Roman");
    range->querySubObject("Font")->setProperty("Size", 14);
    range->querySubObject("Font")->setProperty("Bold", true);
    offset++;

    range = getRange(QString("A%1:K%1").arg(offset));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)", competition);
    range->setProperty("HorizontalAlignment", xlCenter);
    range->querySubObject("Font")->setProperty("Name", "Times New Roman");
    range->querySubObject("Font")->setProperty("Size", 14);
    range->querySubObject("Font")->setProperty("Bold", true);
    offset++;

    range = getRange(QString("A%1:K%1").arg(offset));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("СК «Бастион», ") + genitiveDate(date));
    range->setProperty("HorizontalAlignment", xlCenter);
    range->querySubObject("Font")->setProperty("Name", "Times New Roman");
    range->querySubObject("Font")->setProperty("Size", 14);
    range->querySubObject("Font")->setProperty("Bold", true);
    offset+=2;

    range = getRange(QString("A%1:K%1").arg(offset));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("категория ") + category);
    range->setProperty("HorizontalAlignment", xlCenter);
    range->querySubObject("Font")->setProperty("Name", "Times New Roman");
    range->querySubObject("Font")->setProperty("Size", 12);
    range->querySubObject("Font")->setProperty("Bold", true);
    offset++;

    const char *headers[] = {
        "№ п/п",
        "ФИО",
        "Год рожд.",
        "Техн. квалиф. разряд",
        "Область, край, республика",
        "Город, населенный пункт",
        "Д.С.О. Ведомство",
        "СК, ДЮСШ, СДЮСШОР",
        "Ф.И.О. Тренера",
        "Кол-во боев/ побед",
        "Занятое место",
    };
    for(uint i = 0; i < sizeof(headers)/sizeof(*headers); ++i)
    {
        QAxObject *range = getRange(QString('A' + i) + QString::number(offset));
        range->dynamicCall("SetValue(const QVariant&)", QObject::tr(headers[i]));
    }
}

void ResultsReport::writeRec()
{
    uint place = query->value(11).toUInt();
    uint offset = (currentPage - 1) * pageHeight + 6 + place;

    for(int i = 3; i < 8 ; ++i)
    {
        QAxObject *range = getRange(QString('A' + i - 2) + QString::number(offset));
        range->dynamicCall("SetValue(const QVariant&)", query->value(i).value<QString>());
    }

    QAxObject *range = getRange(QString("J%1").arg(offset));
    range->dynamicCall("SetValue(const QString&)",
        "'" + query->value(9).value<QString>() + "/" + query->value(10).value<QString>());


    range = getRange(QString("C%1").arg(offset));
    QDate date = query->value(4).value<QDate>();

    range->dynamicCall("SetValue(const QVariant&)", (date.isValid() ? (QString::number(date.year())) : QString()));

    range = getRange(QString("G%1").arg(offset));
    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("КУДО"));

    range = getRange(QString("H%1").arg(offset));
    range->dynamicCall("SetValue(const QVariant&)", query->value(8).value<QString>());

    range = getRange(QString("I%1").arg(offset));
    range->dynamicCall("SetValue(const QVariant&)", query->value(12).value<QString>());

    range = getRange(QString("K%1").arg(offset));
    range->dynamicCall("SetValue(const QVariant&)", query->value(11).value<QString>());

    range = getRange(QString("A%1").arg(offset));
    range->dynamicCall("SetValue(const QVariant&)", query->value(11).value<QString>() + ".");
}

void ResultsReport::writeFooter()
{
    uint offset = currentPage * pageHeight - 15;
    QAxObject *range = getRange(QString("A%1:B%1").arg(offset - 1)),
            *range2 = getRange(QString("A%1:B%1").arg(offset));
    range->dynamicCall("Merge()");
    range2->dynamicCall("Merge()");

    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("Гл. судья"));
    range2->dynamicCall("SetValue(const QVariant&)", QObject::tr("Гл. секретарь"));

    range = getRange(QString("C%1:E%1").arg(offset - 1)),
    range2 = getRange(QString("C%1:E%1").arg(offset));

    range->dynamicCall("Merge()");
    range2->dynamicCall("Merge()");

    range->dynamicCall("SetValue(const QVariant&)", QObject::tr("Григорьев Д.А."));
    range2->dynamicCall("SetValue(const QVariant&)", QObject::tr("Штаненкова Ж.Л."));
    range->querySubObject("Font")->setProperty("Name", "Times New Roman");
    range2->querySubObject("Font")->setProperty("Name", "Times New Roman");
    range->querySubObject("Font")->setProperty("Size", 12);
    range2->querySubObject("Font")->setProperty("Size", 12);

    range = getRange(QString("A%1:K%2").arg(offset - 12).arg(offset - 4));
    range->querySubObject("Borders")->setProperty("LineStyle", xlSingle);
    range->querySubObject("Font")->setProperty("Name", "Times New Roman");
    range->setProperty("WrapText", true);

    range = getRange(QString("A%1:K%2").arg(offset - 11).arg(offset - 4));
    range->querySubObject("Font")->setProperty("Size", 11);

    range = getRange(QString("A%1:K%1").arg(offset - 12));
    range->querySubObject("Font")->setProperty("Size", 10);
    range->querySubObject("Font")->setProperty("Bold", true);
    range->setProperty("HorizontalAlignment", xlCenter);

    range = getRange(QString("B%1:K%2").arg(offset - 12).arg(offset - 4));
    range->setProperty("HorizontalAlignment", xlCenter);

    currentPage++;
}

void ResultsReport::makeReport()
{
    QString category = "", vcat;
    sheet = openDocument();
    currentPage = 1;
    bool start = true;
    excel->querySubObject("ActiveWindow")->setProperty("Zoom", 75);
    const double widths[] = {
        3.29,
        30,
        5.71,
        8.43,
        18.29,
        13.43,
        9.57,
        13.29,
        20.43,
        6.43,
        7,
    };
    for(uint i = 0; i < sizeof(widths)/sizeof(*widths); ++i)
    {
        sheet->querySubObject("Columns(const QString&)", QString("%1:%1").arg(QString('A' + i)))
             ->setProperty("ColumnWidth", widths[i]);
    }
    while(query->next())
    {
        vcat = query->value(0).toString();
        if(start || category != vcat)
        {
            if(!start)
            {
                writeFooter();
            }
            else
            {
                start = false;
            }
            category = vcat;
            writeHeader(category, query->value(1).toString(), query->value(2).toDate());
        }
        writeRec();
    }
    writeFooter();

    sheet->querySubObject("PageSetup")->setProperty("Zoom", 90);
    sheet->querySubObject("PageSetup")->setProperty("Orientation", xlLandscape);
    sheet->querySubObject("PageSetup")->setProperty("PrintQuality", 600);

}

void TechnicalReport::writeSuperHeader()
{
    QAxObject *range = getRange(QString("A%1:B%1").arg(currentRow));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)",
        QObject::tr("Технические результаты ") + query->value(0).value<QString>() + " " +
        query->value(2).value<QDate>().toString("dd.MM.yyyy"));
    currentRow++;
}

void TechnicalReport::writeHeader()
{
    QAxObject *range = getRange(QString("A%1:B%1").arg(currentRow));
    range->dynamicCall("Merge()");
    range->dynamicCall("SetValue(const QVariant&)",
        QObject::tr("Категория ") + query->value(1).value<QString>());
    currentRow++;
}

void TechnicalReport::writeLine()
{
    QAxObject *range = getRange(QString("A%1").arg(currentRow)),
            *range2 = getRange(QString("B%1").arg(currentRow));
    range->dynamicCall("SetValue(const QVariant&)",
        QString("%1.").arg(query->value(6).value<uint>()));
    range2->dynamicCall("SetValue(const QVariant&)",
        QString("%1 (%2 %3)").arg(query->value(3).toString(), query->value(5).toString(),
                                  query->value(4).toString()));
    currentRow++;
}

void TechnicalReport::makeReport()
{
    QString category = "", vcat;
    sheet = openDocument();
    currentRow = 1;
    const double widths[] = {
        2,
        82,
    };
    for(uint i = 0; i < sizeof(widths)/sizeof(*widths); ++i)
    {
        sheet->querySubObject("Columns(const QString&)", QString("%1:%1").arg(QString('A' + i)))
             ->setProperty("ColumnWidth", widths[i]);
    }
    while(query->next())
    {
        vcat = query->value(1).toString();
        if(currentRow == 1)
        {
            writeSuperHeader();
        }
        if(category != vcat)
        {
            category = vcat;
            writeHeader();
        }
        writeLine();
    }
    sheet->querySubObject("Columns")->setProperty("WrapText", true);
}

/********************************************************************/
/******************************* View *******************************/
/********************************************************************/

Report::Report(QWidget *aParent, BaseReport *aLogRep, const QString &title):
        QDialog(aParent),
        logRep(aLogRep),
        query(new QSqlQuery)
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle(tr("Отчёт - ") + title);
}

void Report::keyPressEvent(QKeyEvent *aE) { if(aE->key() == Qt::Key_Escape) close(); }

Report::~Report()
{
    delete query;
}

void Report::CreateBasicWidgets(QGridLayout *aLt)
{
    QVBoxLayout *lt = new QVBoxLayout;

    QGroupBox *gb = new QGroupBox(tr("Параметры"));
    gb->setLayout(aLt);

    QHBoxLayout *lt1 = new QHBoxLayout;
    btnExport = new QPushButton(tr("Выгрузить"));
    lt1->addStretch(1);
    lt1->addWidget(btnExport);
    lt1->addStretch(0);
    connect(btnExport, SIGNAL(clicked()), this, SLOT(Export()));

    lt->addWidget(gb);
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
        Report(aParent, new SportsmenReport, tr("Спортсмены"))
{
    CreateWidgets();
    InitComboBox(cbCoach, vecId, "SELECT * FROM coaches", 0);
}

void RepSport::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, Sett::GetColName(ttSport, Sport::taCoach) + ":", cbCoach = new QComboBox, 0, 0);
    CreateBasicWidgets(lt);
}

QString RepSport::GetQuery()
{
    return " SELECT s.reg_number, s.name, s.birthday, s.address, s.phone, "
           " s.workplace, s.job, c.name, r.name "
           " FROM sportsmen s "
           " LEFT JOIN coaches c ON s.coach_id = c.id "
           " LEFT JOIN ranks r ON s.rank_id = r.id "
           " WHERE c.id = " + QString::number(vecId[cbCoach->currentIndex()]) + ";";
}

/******************************* Sertifications *******************************/

RepSert::RepSert(QWidget *aParent):
        Report(aParent, new CertificationReport, tr("Аттестации"))
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
        return  " select sp.name, sp.birthday, r1.name, c.name, sp.reg_number, r2.name, se.note "
                " from sertifications se "
                " left join sportsmen sp on se.sportsman_id = sp.id "
                " left join coaches c on sp.coach_id = c.id "
                " left join ranks r1 on se.rank_from_id = r1.id "
                " inner join ranks r2 on se.rank_to_id = r2.id "
                " where c.id = " + QString::number(vecId[cb->currentIndex()]);
    }
    return  " select sp.name, sp.birthday, r1.name, c.name, sp.reg_number, r2.name, se.note "
            " from sertifications se "
            " left join sportsmen sp on se.sportsman_id = sp.id "
            " left join coaches c on sp.coach_id = c.id "
            " left join ranks r1 on se.rank_from_id = r1.id "
            " left join clubs cl on c.club_id = cl.id "
            " inner join ranks r2 on se.rank_to_id = r2.id "
            " where cl.id = " + QString::number(vecId[cb->currentIndex()]);
}

/******************************* Competiiton Based *******************************/

RepCompetitionBased::RepCompetitionBased(QWidget *aParent, BaseReport *report, const QString &title):
    Report(aParent, report, title)
{
    CreateWidgets();
    InitComboBox(cbCompetition, vecId, "select id, strftime('%d.%m.%Y',date) || ' ' || name from competitions; ", 0);
    btnExport->setEnabled(!!cbCompetition->count());
}

void RepCompetitionBased::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    AddWidToLt(lt, tr("Использовать соревнование:"), cbCompetition = new QComboBox, 0, 0);
    QPushButton *btnComp = new QPushButton();
    lt->addWidget(btnComp, 0, 2);
    connect(btnComp, SIGNAL(clicked()), this, SLOT(OpenCardCompetition()));
    CreateBasicWidgets(lt);
}

void RepCompetitionBased::OpenCardCompetition()
{
    if (!btnExport->isEnabled()) return;
    int id = vecId[cbCompetition->currentIndex()];
    if (mapperCard.SetCard(ttComp, id)) return;
    mapperCard.InsertCard(ttComp, id, new CardComp(Sett::GetMA(), 0, id), this);
}

/******************************* Drawing *******************************/


RepDraw::RepDraw(QWidget *aParent): RepCompetitionBased(aParent, new DrawingReport, tr("Жеребьёвка")) {}

QString RepDraw::GetQuery()
{
    return " select ca.name, co.date, s.name, s.birthday, cl.name, r.name "
           " from sportsmen_competitions sc "
           " inner join sportsmen s on sc.sportsman_id = s.id "
           " left join coaches c on s.coach_id = c.id"
           " left join clubs cl on c.club_id = cl.id"
           " left join ranks r on s.rank_id = r.id "
           " inner join categories ca on sc.category_id = ca.id "
           " inner join competitions co on sc.competition_id = co.id "
           " where sc.competition_id = " +  QString::number(vecId[cbCompetition->currentIndex()]) +
           " order by ca.name ";
}

/******************************* Pulka *******************************/

RepPulka::RepPulka(QWidget *aParent): RepCompetitionBased(aParent, new PulkaReport, tr("Пулька")) {}

QString RepPulka::GetQuery()
{
    return " select co.name_prot, co.date, ca.name, s.name, cl.name, r.name, sc.draw_number "
           " from sportsmen_competitions sc "
           " inner join sportsmen s on sc.sportsman_id = s.id "
           " left join coaches c on s.coach_id = c.id "
           " left join clubs cl on c.club_id = cl.id "
           " left join ranks r on s.rank_id = r.id "
           " inner join categories ca on sc.category_id = ca.id "
           " inner join competitions co on sc.competition_id = co.id "
           " where sc.competition_id = " +  QString::number(vecId[cbCompetition->currentIndex()]) +
           " order by ca.name, sc.draw_number ";
}

/******************************* Results *******************************/

RepResults::RepResults(QWidget *aParent): RepCompetitionBased(aParent, new ResultsReport, tr("Протокол Результатов")) {}

QString RepResults::GetQuery()
{
    return " select ca.name, com.name_prot, com.date, s.name, s.birthday, ra.name, pw.region, "
           " pw.city, cl.name, pw.fights_won, pw.fights_count, pw.place, co.name "
           " from prize_winners pw "
           " inner join sportsmen_competitions sc on pw.sportsman_competition_id=sc.id "
           " inner join sportsmen s on sc.sportsman_id=s.id "
           " left join coaches co on s.coach_id=co.id "
           " left join ranks ra on s.rank_id=ra.id "
           " left join clubs cl on co.club_id=cl.id "
           " inner join categories ca on sc.category_id=ca.id "
           " inner join competitions com on sc.competition_id=com.id "
           " where sc.competition_id = " +  QString::number(vecId[cbCompetition->currentIndex()]) +
           " order by ca.name, pw.place ";
}

/******************************* Technical *******************************/

RepTechnical::RepTechnical(QWidget *aParent): RepCompetitionBased(aParent, new TechnicalReport, tr("Технические результаты")) {}

QString RepTechnical::GetQuery()
{
    return " select com.name_prot, ca.name, com.date, s.name, cl.name, pw.city, pw.place "
           " from prize_winners pw "
           " inner join sportsmen_competitions sc on pw.sportsman_competition_id=sc.id"
           " inner join sportsmen s on sc.sportsman_id=s.id "
           " left join coaches co on s.coach_id=co.id "
           " left join clubs cl on co.club_id=cl.id "
           " inner join categories ca on sc.category_id=ca.id "
           " inner join competitions com on sc.competition_id=com.id "
           " where sc.competition_id = " +  QString::number(vecId[cbCompetition->currentIndex()]) +
           " order by ca.name, pw.place";
}
