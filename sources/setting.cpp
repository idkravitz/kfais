#include "../headers/setting.h"

namespace Setting
{

TableSettings table_settings[ttCateg + 1];

bool LoadSettings()
{
    table_settings[ttSport].title = "AbstractName";
    table_settings[ttSport].tblName = "AbstractTblName";

    table_settings[ttSport].title = "����������";
    table_settings[ttSport].tblName = "sportsmen";

    table_settings[ttCoach].title = "�������";
    table_settings[ttCoach].tblName = "coach";

    table_settings[ttClub].title = "�����";
    table_settings[ttClub].tblName = "clubs";

    table_settings[ttSert].title = "������������";
    table_settings[ttSert].tblName = "sertifications";

    table_settings[ttFee].title = "������";
    table_settings[ttFee].tblName = "fee";

    table_settings[ttSportComp].title = "������������� \"��������� - ������������\"";
    table_settings[ttSportComp].tblName = "sportsmen_competitions";

    table_settings[ttComp].title = "������������";
    table_settings[ttComp].tblName = "competitions";

    table_settings[ttCateg].title = "���������";
    table_settings[ttCateg].tblName = "categories";

    return true;
}

bool SaveSettings()
{
    //TODO
    return false;
}

} // namespace Setting
