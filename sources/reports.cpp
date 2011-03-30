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

Report::Report(QWidget *aParent, BaseReport *aLogRep):
        QDialog(aParent),
        logRep(aLogRep),
        query(new QSqlQuery)
{
    setAttribute(Qt::WA_DeleteOnClose);

}

void Report::CreateBasicWidgets(QGridLayout *aLt)
{
    QVBoxLayout *lt = new QVBoxLayout;
    lt->addLayout(aLt);

    QHBoxLayout *lt1 = new QHBoxLayout;
    btnExport = new QPushButton(tr("Выгрузить"));
    lt1->addWidget(btnExport);
    connect(btnExport, SIGNAL(clicked()), this, SLOT(Export()));

    lt->addLayout(aLt);
    lt->addLayout(lt1);

    setLayout(lt);
}

void Report::Export()
{
    query->exec("select * from sportsmen");
    logRep->setQuery(query);
    logRep->makeReport();
}

RepSport::RepSport(QWidget *aParent):
        Report(aParent, new SportsMen)
{
    CreateWidgets();
}

void RepSport::CreateWidgets()
{
    QGridLayout *lt = new QGridLayout;
    CreateBasicWidgets(lt);
}

