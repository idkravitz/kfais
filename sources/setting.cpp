#include "../headers/setting.h"

QMdiArea *Setting::mdiArea;

namespace Setting
{

TableSettings table_settings[ttCateg + 1];

bool LoadSettings()
{
    table_settings[ttAbstract].title = "AbstractName";
    table_settings[ttAbstract].tblName = "AbstractTblName";

    table_settings[ttSport].title = "Спрортмены";
    table_settings[ttSport].tblName = "sportsmen";

    table_settings[ttCoach].title = "Тренеры";
    table_settings[ttCoach].tblName = "coach";

    table_settings[ttClub].title = "Клубы";
    table_settings[ttClub].tblName = "clubs";

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
    table_settings[ttCateg].colName << "id" << "Категория"
            << "Примечание";

    return true;
}

bool SaveSettings()
{
    //TODO
    return false;
}

} // namespace Setting
