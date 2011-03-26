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
        ttSport,        //sportmen
        ttCoach,        //coachs
        ttClub,         //clubs
        ttSert,         //sertification
        ttFee,          //fee
        ttSportComp,    //sportsmen-competitions
        ttComp,         //competitions
        ttCateg         //categories
    };

    namespace Sport
    {
        const char *const title = "����������";
        const QString tblName = "sportsmen";
    }

    namespace Coach
    {
        const char *const title = "�������";
        const QString tblName = "coach";
    }

    namespace Club
    {
        const char *const title = "�����";
        const QString tblName = "clubs";
    }

    namespace Sert
    {
        const char *const title = "�����������";
        const QString tblName = "sertifications";
    }

    namespace Fee
    {
        const char *const title = "������";
        const QString tblName = "fee";
    }

    namespace SportComp
    {
        const char *const title = "������������� \"��������� - ������������\"";
        const QString tblName = "sportsmen_competitions";
    }

    namespace Comp
    {
        const char *const title = "������������";
        const QString tblName = "competitions";
    }

    namespace Categ
    {
        const char *const title = "���������";
        const QString tblName = "categories";
    }
}

#endif // SETTING_H
