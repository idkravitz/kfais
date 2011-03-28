#include "../headers/setting.h"

QMdiArea *Sett::mdiArea;
TblSett Sett::table_settings[ttRank + 1];

QMdiArea *Sett::GetMA()
{
    return mdiArea;
}

bool Sett::LoadSettings()
{
    mdiArea = new QMdiArea;

    table_settings[ttAbstract].title = "AbstractName";
    table_settings[ttAbstract].tblName = "AbstractTblName";

    table_settings[ttSport].title = "Спрортмены";
    table_settings[ttSport].tblName = "sportsmen";

    table_settings[ttCoach].title = "Тренеры";
    table_settings[ttCoach].tblName = "coaches";
    table_settings[ttCoach].colName << "id" << "Тренер" << "Телефон"
            << "Клуб" << "Примечание";

    table_settings[ttClub].title = "Клубы";
    table_settings[ttClub].tblName = "clubs";
    table_settings[ttClub].colName << "id" << "Название" << "Адрес";

    table_settings[ttSert].title = "Сертефикации";
    table_settings[ttSert].tblName = "sertifications";

    table_settings[ttFee].title = "Взносы";
    table_settings[ttFee].tblName = "fee";

    table_settings[ttSportComp].title = "Распределения \"Спортсмен - соревнование\"";
    table_settings[ttSportComp].tblName = "sportsmen_competitions";

    table_settings[ttComp].title = "Соревнования";
    table_settings[ttComp].tblName = "competitions";

    table_settings[ttCateg].title = "Категории";
    table_settings[ttCateg].tblName = "categories";
    table_settings[ttCateg].colWidth << 40 << 200 << 200;
    table_settings[ttCateg].colName << "id" << "Категория";

    table_settings[ttRank].title = "Ранги";
    table_settings[ttRank].tblName = "ranks";

    return true;
}

bool Sett::SaveSettings()
{
    //TODO
    return false;
}

const char *Sett::GetTblTitle(TblType aType)
{
    return table_settings[aType].title;
}

QString &Sett::GetTblName(TblType aType)
{
    return table_settings[aType].tblName;
}

QVector<int> &Sett::GetVecColWidth(TblType aType)
{
    return table_settings[aType].colWidth;
}

QVector<char*> &Sett::GetVecColName(TblType aType)
{
    return table_settings[aType].colName;
}

const char *Sett::GetColName(TblType aType, int aColNum)
{
    return table_settings[aType].colName[aColNum];
}

const char *Sett::GetNoteName()
{
    return "Примечание";
}
