#ifndef REPORTS_H
#define REPORTS_H

#include "setting.h"

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

class BaseReport{
protected:
    QSqlQuery &query;
public:
    BaseReport(QSqlQuery &aQuery): query(aQuery) {}
    virtual void makeReport() = 0;
};

class SportsMen: public BaseReport {
public:
    virtual void makeReport();
};

/********************************************************************/
/******************************* View *******************************/
/********************************************************************/

class Report: public QMainWindow
{
   Q_OBJECT

private:
    BaseReport *logRep;
    QPushButton *btnExport;

    void CreateBasicWidgets();

public:
    Report(QWidget *aParent, BaseReport *aLogRep);
};

class RepSport: public Report
{
    Q_OBJECT

private:
    QComboBox *cbCoach;

    void CreateWidgets();

public:
    RepSport(QWidget *aParent);
};


#endif // REPORTS_H
