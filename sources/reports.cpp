#include "reports.h"

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

void SportsMen::makeReport()
{
    // foo
}

/********************************************************************/
/******************************* View *******************************/
/********************************************************************/

Report::Report(QWidget *aParent, BaseReport *aLogRep):
        QDialog(aParent),
        logRep(aLogRep)
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
    setLayout(lt);
}

RepSport::RepSport(QWidget *aParent):
        Report(aParent, new SportsMen)
{

}

void RepSport::CreateWidgets()
{

}

