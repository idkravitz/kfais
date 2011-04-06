#include "setting.h"

QMdiArea *Sett::mdiArea;
TblSett Sett::table_settings[ttPrzWin + 1];
RepSett Sett::report_settings[rtDraw + 1];

void AddWidToLt(QGridLayout *aLt, const QString &aLblStr, QWidget *aW, int aRow, int aCol)
{
    QLabel *lbl = new QLabel(aLblStr);
    AddWidToLt(aLt, lbl, aW, aRow, aCol);
}

void AddWidToLt(QGridLayout *aLt, QLabel *aLbl, QWidget *aW, int aRow, int aCol)
{
    aLt->addWidget(aLbl, aRow, aCol);
    aLt->addWidget(aW, aRow, aCol + 1);
    aLbl->setBuddy(aW);
}

void InitComboBox(QComboBox *aCB, QVector<int> &aVecId, const QString &aStrQ, int aCurId)
{
    aVecId.clear();
    QSqlQuery q(aStrQ);
    QStringList lst;
    while (q.next())
    {
        aVecId.push_back(q.record().value(0).toInt());
        lst.push_back(q.record().value(1).toString());
    }
    aCB->clear();
    aCB->addItems(lst);
    aCB->setInsertPolicy(QComboBox::NoInsert);
    aCB->setEditable(true);

    QCompleter *comp = new QCompleter(lst);
    aCB->setCompleter(comp);

    int i = 0;
    while (i < aVecId.size() && aCurId != aVecId[i])
    {
        ++i;
    }
    if (i < aVecId.size())
    {
        aCB->setCurrentIndex(i);
    }
    else
    {
        aCB->setEditText("");
    }
}

QMdiArea *Sett::GetMA()
{
    return mdiArea;
}

bool Sett::LoadSettings()
{
    mdiArea = new QMdiArea;

    table_settings[ttSport].title = "����������";
    table_settings[ttSport].tblName = "sportsmen";
    table_settings[ttSport].colName << "id" << "�.�.�"
            << "���� ��������" << "������" << "���. �"
            << "������" << "�����" << "�������" << "����� ������"
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
    table_settings[ttSert].colName << "id" << "���������" << "����"
            << "������ �" << "������ ��" << "����������";

    table_settings[ttFee].title = "������";
    table_settings[ttFee].tblName = "fee";
    table_settings[ttFee].colName << "id" << "���������" << "����"
            << "����������";

    table_settings[ttSportComp].title = "������������� \"��������� - ������������\"";
    table_settings[ttSportComp].tblName = "sportsmen_competitions";
    table_settings[ttSportComp].colName << "id" << "���������" << "������������"
            << "����" << "���������" << "� ����������"
            << "�������" << "����������";

    table_settings[ttComp].title = "������������";
    table_settings[ttComp].tblName = "competitions";
    table_settings[ttComp].colName << "id" << "��������" << "�������� � ���������" << "����"
            << "����� ����������" << "����������";

    table_settings[ttCateg].title = "���������";
    table_settings[ttCateg].tblName = "categories";
    table_settings[ttCateg].colWidth << 40 << 200 << 200;
    table_settings[ttCateg].colName << "id" << "��������" << "����������";

    table_settings[ttRank].title = "������";
    table_settings[ttRank].tblName = "ranks";
    table_settings[ttRank].colName << "id" << "��������" << "����������";

    table_settings[ttPrzWin].title = "�������";
    table_settings[ttPrzWin].tblName = "prize_winners";
    table_settings[ttPrzWin].colName << "id" << "���������" << "������������"
            << "����" << "����� ����" << "����� �����" << "�����"
            << "������" << "�����" << "����������";

    report_settings[rtSport].title = "����������";
    report_settings[rtSert].title = "����������";
    report_settings[rtDraw].title = "�������� �����������, ��������� �������� � ����������";
    report_settings[rtPulka].title = "������";
    report_settings[rtResults].title = "�������� �����������";
    report_settings[rtTechnical].title = "����������� ����������";
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

QString Sett::GetErrMsgTitle()
{
    return QObject::tr("������");
}

QString Sett::GetErrMsgDef()
{
    return QObject::tr("��������� ������ �� ���������");
}

QString Sett::GetRepTitle(RepType aType)
{
    return QObject::tr(report_settings[aType].title);
}
