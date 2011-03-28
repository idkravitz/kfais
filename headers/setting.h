#ifndef SETTING_H
#define SETTING_H

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QtSql>

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

struct TblSett{
    const char *title;
    QString tblName;
    QVector<int> colWidth;
    QVector<char*> colName;
    QVector<char*> atrName;
};

class Sett
{
private:
    static QMdiArea *mdiArea;
    static TblSett table_settings[ttRank + 1];

public:
    static QMdiArea *GetMA();

    static const char *GetTblTitle(TblType aType);
    static QString &GetTblName(TblType aType);
    static const char *GetColName(TblType aType, int aColNum);
    static const char *GetAtrName(TblType aType, int aNum);

    static QVector<int> &GetVecColWidth(TblType aType);
    static QVector<char*> &GetVecColName(TblType aType);

    static const char *GetNoteName();

    static bool LoadSettings();
    static bool SaveSettings();
};

namespace Sport
{
    enum Atr
    {
        taId = 0,
        taPhoto = 1,
        taName = 2,
        taBirth = 3,
        taRank = 4,
        taRegNum = 5,
        taCoach = 6,
        taAddr = 7,
        taPhone = 8,
        taWork = 9,
        taJob = 10
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
        taRankTo = 4,
        taRes = 5
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

#endif // SETTING_H
