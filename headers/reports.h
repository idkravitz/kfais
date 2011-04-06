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
    QAxObject *sheet;
    QAxObject *excel;
    QAxObject *openDocument();
    QAxObject *getRange(const QString& range);
    enum LineStyle {
        xlContinious = 1,
        xlSingle = 1,
        xlDouble = -4119,
    };
    enum Alignment {
        xlCenter = -4108,
        xlRight  = -4152,
        xlTop    = -4160,
        xlBottom = -4107,
    };
    enum Edges {
        xlEdgeBottom = 9,
    };
    enum Weight {
        xlHairline = 1,
    };
    enum PageOrientation {
        xlLandscape = 2,
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
    void writeHeader(const QString& category, const QDate &date);
    void writeFooter(uint written);
    void writeLine(uint written);
public:
    virtual void makeReport();
};

class PulkaReport: public BaseReport
{
    static const uint pageHeight = 36;
    static const uint firstRecOffset = 4;
    static const uint pageWidth = 12;

    uint currentPage;
    void writeHeader(const QString& category, const QString &competition, const QDate &date);
    void writeFooter();
    void writeRec(uint draw_number);
public:
    virtual void makeReport();
};

class ResultsReport: public BaseReport
{
    static const uint pageHeight = 34;
    uint currentPage;
    void writeHeader(const QString& category, const QString &competition, const QDate &date);
    void writeFooter();
    void writeRec();
public:
    virtual void makeReport();
};

class TechnicalReport: public BaseReport
{
    uint currentRow;
    void writeSuperHeader();
    void writeHeader();
    void writeLine();
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

/******************************* Drawing *******************************/


class RepDraw: public Report{
    Q_OBJECT

private:
    void CreateWidgets();

    QString GetQuery();
public:
    RepDraw(QWidget *aParent);
};

/******************************* Pulka *******************************/

class RepPulka: public Report{
    Q_OBJECT

private:
    void CreateWidgets();

    QString GetQuery();
public:
    RepPulka(QWidget *aParent);
};

/******************************* Results *******************************/

class RepResults: public Report{
    Q_OBJECT

private:
    void CreateWidgets();

    QString GetQuery();
public:
    RepResults(QWidget *aParent);
};

/******************************* Technical Results *******************************/

class RepTechnical: public Report{
    Q_OBJECT

private:
    void CreateWidgets();

    QString GetQuery();
public:
    RepTechnical(QWidget *aParent);
};


#endif // REPORTS_H
