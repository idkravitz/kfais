#ifndef SETTING_H
#define SETTING_H

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QtSql>

struct TblSett{
    const char *title;
    QString tblName;
    QVector<int> colWidth;
    QVector<char*> colName;
};

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

class Sett
{
private:
    static QMdiArea *mdiArea;
    static TblSett table_settings[ttRank + 1];

public:
    static QMdiArea *GetMA();

    static const char *GetTblTitle(TblType aType);
    static QString &GetTblName(TblType aType);
    static QVector<int> &GetColWidth(TblType aType);
    static QVector<char*> &GetColName(TblType aType);

    static bool LoadSettings();
    static bool SaveSettings();
};

#endif // SETTING_H
