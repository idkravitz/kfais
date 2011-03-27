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
    table_settings[ttCateg].colWidth << 40 << 200 << 200;
    table_settings[ttCateg].colName << "id" << "���������"
            << "����������";

    table_settings[ttRank].title = "�����";
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

QVector<int> &Sett::GetColWidth(TblType aType)
{
    return table_settings[aType].colWidth;
}

QVector<char*> &Sett::GetColName(TblType aType)
{
    return table_settings[aType].colName;
}
