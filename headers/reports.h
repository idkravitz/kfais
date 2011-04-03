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

    void closeEvent(QCloseEvent *aE);

private slots:
    void Export();

protected:
    void CreateBasicWidgets(QGridLayout *aLt);

    virtual QString GetQuery();

public:
    Report(QWidget *aParent, BaseReport *aLogRep);
    ~Report();
};

/******************************* Sportsmen *******************************/

class RepSport: public Report
{
    Q_OBJECT

private:
    QComboBox *cbCoach;
    QVector<int> vecId;

    void CreateWidgets();

    QString GetQuery();

public:
    RepSport(QWidget *aParent);
};

/******************************* Sertifications *******************************/

class RepSert: public Report{
    Q_OBJECT

private:
    QComboBox *cbTbl;
    QLabel *lbl;
    QComboBox *cb;
    QVector<int> vecId;

    void CreateWidgets();

    QString GetQuery();

private slots:
    void ChangeTbl(int aIndex);

public:
    RepSert(QWidget *aParent);
};

#endif // REPORTS_H
