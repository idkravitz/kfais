#ifndef LOADER_H
#define LOADER_H

#import "setting.h"
#import "exceptions.h"
#import "card.h"

/******************************* CSV parser *******************************/

class ParserCSV: public QObject
{
    Q_OBJECT

private:
    QString TrimItemCSV(const QString &aItem);
public:
    ParserCSV();
    QList<QStringList> ParseFile(const QString &aFileName, const QChar &aSeparator, unsigned int aColCount);
};

/******************************* Basic class for loading *******************************/

typedef QPair<QString, unsigned int> TblHeaderItem;
typedef QVector<TblHeaderItem> TblHeader;

class Loader: public QDialog
{
    Q_OBJECT

private:
    bool isReadyToLoad;

    void closeEvent(QCloseEvent *aE);
    void CreateWidgets();

    ParserCSV parser;

private slots:
    void ChangeFile();
    void ImportFromFile();
    void LoadToBase();

protected:
    void keyPressEvent(QKeyEvent *aE);

    QPushButton *btnChangeFile;
    QPushButton *btnImport;
    QPushButton *btnLoad;
    QLineEdit *edtFileName;
    QTableWidget *tblResult;

    QTextEdit *edtMessages;

    void BasicInitWidgets(const TblHeader &aTblH);
    void EmptyTblResult();

    virtual unsigned int GetColCountConstraint() const = 0;
    virtual bool Handle(const QList<QStringList> &aList) = 0;
    virtual void SpecLoadToBase() = 0;

public:
    Loader(QWidget *aParent, const QString &aTitle);
};

/******************************* Class for loading reg nums *******************************/

class LoaderRegNum: public Loader
{
    Q_OBJECT

private:
    struct RecSportsman
    {
        int idSp;
        QString fioDB;
        QString regDB, regFile;
        unsigned int rxIndex;

        RecSportsman() {}
        RecSportsman(int aId, const QString &aFioDB, const QString &aRegDB, const QString &aRegFile, unsigned int aRxIndex):
            idSp(aId), fioDB(aFioDB), regDB(aRegDB), regFile(aRegFile), rxIndex(aRxIndex) {}
    };

    static const unsigned int CSV_COL_COUNT = 3;
    enum TblCol
    {
        eIdSp = 0,
        eFioFile,
        eFioDB,
        eRegFile,
        eRegDB,
        eSelRec
    };

    void InitWidgets();

protected:
    virtual unsigned int GetColCountConstraint() const;
    virtual bool Handle(const QList<QStringList> &aList);
    virtual void SpecLoadToBase();

public:
    LoaderRegNum(QWidget *aParent);
};

#endif // LOADER_H
