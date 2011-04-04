#ifndef REPORTS_H
#define REPORTS_H

#include "setting.h"
#include <QAxObject>

/********************************************************************/
/******************************* Model ******************************/
/********************************************************************/

class BaseReport
{
protected:
    QSqlQuery *query;
    QAxObject *openDocument();
    enum LineStyle {
        xlSingle = 1,
        xlDouble = -4119,
    };

public:
    BaseReport(QSqlQuery *aQuery = 0):
        query(aQuery) {}
    virtual void makeReport() = 0;
    void setQuery(QSqlQuery *aQuery) { query = aQuery; }
};

class SportsmenReport: public BaseReport
{
protected:
    void writeBody(const char *header[], uint length);
public:
    virtual void makeReport();
};

class CertificationReport: public SportsmenReport
{
public:
    virtual void makeReport();
};

class DrawingReport: public BaseReport
{
    uint currentRow;
    uint currentPage;
    uint pageStartRow;
    QAxObject *sheet;
    void writeHeader(const QString& category);
    void writeFooter(uint written);
    void writeLine(uint written);
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

class RepDraw: public Report{
    Q_OBJECT

private:
//    QComboBox *cbTbl;
//    QLabel *lbl;
//    QComboBox *cb;
//    QVector<int> vecId;

    void CreateWidgets();

    QString GetQuery();

//private slots:
//    void ChangeTbl(int aIndex);

public:
    RepDraw(QWidget *aParent);
};

#endif // REPORTS_H
