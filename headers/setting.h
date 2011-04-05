#ifndef SETTING_H
#define SETTING_H

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QtSql>

extern void AddWidToLt(QGridLayout *aLt, const QString &aLblStr, QWidget *aW, int aRow, int aCol);
extern void AddWidToLt(QGridLayout *aLt, QLabel *aLbl, QWidget *aW, int aRow, int aCol);

enum TblType
{
    ttAbstract = 0,
    ttSport,        //sportmen
    ttCoach,        //coachs
    ttClub,         //clubs
    ttSert,         //sertifications
    ttFee,          //fee
    ttSportComp,    //sportsmen_competitions
    ttComp,         //competitions
    ttCateg,        //categories
    ttRank,         //ranks
    ttPrzWin,       //prize_winners
    ttPrzWinView
};

enum RepType
{
    rtAbstract = 0,
    rtSport,
    rtSert,
    rtDraw,
    rtPulka,
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
    static TblSett table_settings[ttPrzWinView + 1];
    static RepSett report_settings[rtDraw + 1];

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
        taName,
        taBirth,
        taRank,
        taRegNum,
        taCoach,
        taAddr,
        taPhone,
        taWork,
        taJob
    };
}

namespace Coach
{
    enum Atr
    {
        taId = 0,
        taName,
        taPhone,
        taClub
    };
}

namespace Club
{
    enum Atr
    {
        taId = 0,
        taName,
        taAddr
    };
}

namespace Rank
{
    enum Atr
    {
        taId = 0,
        taName
    };
}

namespace Sert
{
    enum Atr
    {
        taId = 0,
        taSport,
        taDate,
        taRankFrom,
        taRankTo
    };
}

namespace Fee
{
    enum Atr
    {
        taId = 0,
        taSport,
        taDate
    };
}

namespace SportComp
{
    enum Atr
    {
        taId = 0,
        taSport,
        taComp,
        taCateg,
        taDrawNum,
        taUnit
    };
}

namespace Comp
{
    enum Atr
    {
        taId = 0,
        taName,
        taDate,
        taLoc
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

namespace PrzWin
{
    enum Atr
    {
        taId = 0,
        taSportComp,
        taFightsCount,
        taFightsWon,
        taPlace,
        taRegion,
        taCity
    };
}

#endif // SETTING_H
