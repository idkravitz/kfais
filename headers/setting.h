#ifndef SETTING_H
#define SETTING_H

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QtSql>

extern void AddWidToLt(QGridLayout *aLt, const QString &aLblStr, QWidget *aW, int aRow, int aCol);

enum TblType
{
    ttAbstract = 0,
    ttSport = 1,        //sportmen
    ttCoach = 2,        //coachs
    ttClub = 3,         //clubs
    ttSert = 4,         //sertifications
    ttFee = 5,          //fee
    ttSportComp = 6,    //sportsmen-competitions
    ttComp = 7,         //competitions
    ttCateg = 8,        //categories
    ttRank = 9          //ranks
};

enum RepType
{
    rtAbstract = 0,
    rtSport = 1
};

struct TblSett{
    const char *title;
    QString tblName;
    QVector<int> colWidth;
    QVector<char*> colName;
};

struct RepSett{
    const char *title;
};

class Sett
{
private:
    static QMdiArea *mdiArea;
    static TblSett table_settings[ttRank + 1];
    static RepSett report_settings[rtSport + 1];

public:
    static QMdiArea *GetMA();

    static QString GetTblTitle(TblType aType);
    static QString &GetTblName(TblType aType);
    static QString GetColName(TblType aType, int aColNum);

    static QVector<int> &GetVecColWidth(TblType aType);
    static QVector<char*> &GetVecColName(TblType aType);

    static QString GetRepTitle(RepType aType);

    static QString GetNoteName();

    static void SetParam(QTableView *aView);

    static bool LoadSettings();
    static bool SaveSettings();

    static QString GetErrMsgTitle();
    static QString GetErrMsgDef();
};

namespace Sport
{
    enum Atr
    {
        taId = 0,
        taName = 1,
        taBirth = 2,
        taRank = 3,
        taRegNum = 4,
        taCoach = 5,
        taAddr = 6,
        taPhone = 7,
        taWork = 8,
        taJob = 9
    };
}

namespace Coach
{
    enum Atr
    {
        taId = 0,
        taName = 1,
        taPhone = 2,
        taClub = 3
    };
}

namespace Club
{
    enum Atr
    {
        taId = 0,
        taName = 1,
        taAddr = 2
    };
}

namespace Rank
{
    enum Atr
    {
        taId = 0,
        taName = 1
    };
}

namespace Sert
{
    enum Atr
    {
        taNumRecSert = 0,
        taSport = 1,
        taDate = 2,
        taRankFrom = 3,
        taRankTo = 4
    };
}

namespace Fee
{
    enum Atr
    {
        taId = 0,
        taSport = 1,
        taDate = 2
    };
}

namespace SportComp
{
    enum Atr
    {
        taId = 0,
        taSport = 1,
        taName = 2,
        taDSO = 3,
        taCateg = 4,
        taDrawNum = 5,
        taUnit = 6,
        taPrzPlc = 7,
        taFigCount = 8,
        taFigWon = 9
    };
}

namespace Comp
{
    enum Atr
    {
        taId = 0,
        taName = 1,
        taDate = 2,
        taLoc = 3
    };
}

namespace Categ
{
    enum Atr
    {
        taId = 0,
        taName = 1
    };
}
#endif // SETTING_H
