#include "setting.h"

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
    table_settings[ttAbstract].colName << "AbstractColName";

    table_settings[ttSport].title = "����������";
    table_settings[ttSport].tblName = "sportsmen";
    table_settings[ttSport].colName << "id" << "�.�.�"
            << "���� ��������" << "�������" << "��������������� �"
            << "������" << "������" << "�������" << "����� ������"
            << "���������" << "����������";

    table_settings[ttCoach].title = "�������";
    table_settings[ttCoach].tblName = "coaches";
    table_settings[ttCoach].colName << "id" << "�.�.�." << "�������"
            << "����" << "����������";

    table_settings[ttClub].title = "�����";
    table_settings[ttClub].tblName = "clubs";
    table_settings[ttClub].colName << "id" << "��������" << "�����"
            << "����������";

    table_settings[ttSert].title = "����������";
    table_settings[ttSert].tblName = "sertifications";
    table_settings[ttSert].colName << "���. � �����������" << "���������" << "����"
            << "������ �" << "������ ��" << "����������";

    table_settings[ttFee].title = "������";
    table_settings[ttFee].tblName = "fee";
    table_settings[ttFee].colName << "id" << "���������" << "����"
            << "����������";

    table_settings[ttSportComp].title = "������������� \"��������� - ������������\"";
    table_settings[ttSportComp].tblName = "sportsmen_competitions";
    table_settings[ttSportComp].colName << "id" << "���������"
            << "��������" << "���" << "���������" << "draw number"
            << "�������" << "prize_place" << "���������"
            << "�����" << "����������";

    table_settings[ttComp].title = "������������";
    table_settings[ttComp].tblName = "competitions";
    table_settings[ttComp].colName << "id" << "��������" << "����"
            << "����� ����������" << "����������";

    table_settings[ttCateg].title = "���������";
    table_settings[ttCateg].tblName = "categories";
    table_settings[ttCateg].colWidth << 40 << 200 << 200;
    table_settings[ttCateg].colName << "id" << "��������" << "����������";

    table_settings[ttRank].title = "������";
    table_settings[ttRank].tblName = "ranks";
    table_settings[ttRank].colName << "id" << "��������" << "����������";

    return true;
}

bool Sett::SaveSettings()
{
    //TODO
    return false;
}

QString Sett::GetTblTitle(TblType aType)
{
    return QObject::tr(table_settings[aType].title);
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

QString Sett::GetColName(TblType aType, int aColNum)
{
    return QObject::tr(table_settings[aType].colName[aColNum]);
}

QString Sett::GetNoteName()
{
    return QObject::tr("����������");
}

void Sett::SetParam(QTableView *aView)
{
    aView->setSelectionMode(QAbstractItemView::SingleSelection); //Selection mode - single
    aView->setSelectionBehavior(QAbstractItemView::SelectRows);  //Selection mode - full row
    aView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //Disable editing
}

QString Sett::GetErrMsgTitle()
{
    return QObject::tr("������");
}

QString Sett::GetErrMsgDef()
{
    return QObject::tr("��������� ������ �� ���������");
}
