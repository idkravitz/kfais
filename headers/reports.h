#ifndef REPORTS_H
#define REPORTS_H

#include "setting.h"

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

class BaseReport{
protected:
    QSqlQuery *query;
public:
    BaseReport(QSqlQuery *aQuery = 0):
        query(aQuery) {}
    virtual void makeReport() = 0;
    void setQuery(QSqlQuery *aQuery) { query = aQuery; }
};

class SportsMen: public BaseReport {
public:
    virtual void makeReport();
};

/********************************************************************/
/******************************* View *******************************/
/********************************************************************/

class Report: public QDialog
{
   Q_OBJECT

private:
    BaseReport *logRep;
    QSqlQuery *query;
    QPushButton *btnExport;

private slots:
    void Export();

protected:
    void CreateBasicWidgets(QGridLayout *aLt);

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
