#ifndef SETTING_H
#define SETTING_H

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QtSql>

namespace Setting
{
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

    extern QMdiArea *mdiArea;

    struct TableSettings{
        const char *title;
        QString tblName;
        QVector<int> colWidth;
        QVector<char*> colName;
    };

    extern TableSettings table_settings[ttRank + 1];

    bool LoadSettings();
    bool SaveSettings();
}

#endif // SETTING_H
