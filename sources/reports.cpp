#include "reports.h"
#include <QAxObject>

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

void SportsMen::makeReport()
{
    QAxObject *excel = new QAxObject("Excel.Application", 0);
    excel->dynamicCall("SetVisible(bool)", true); //делаем его видимым
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

