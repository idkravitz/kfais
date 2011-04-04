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

    table_settings[ttSport].title = "Спортсмены";
    table_settings[ttSport].tblName = "sportsmen";
    table_settings[ttSport].colName << "id" << "Ф.И.О"
            << "Дата рождения" << "Разряд" << "Регистрационный №"
            << "Тренер" << "Адрес" << "Телефон" << "Место работы"
            << "Должность" << "Примечание";

    table_settings[ttCoach].title = "Тренеры";
    table_settings[ttCoach].tblName = "coaches";
    table_settings[ttCoach].colName << "id" << "Ф.И.О." << "Телефон"
            << "Клуб" << "Примечание";

    table_settings[ttClub].title = "Клубы";
    table_settings[ttClub].tblName = "clubs";
    table_settings[ttClub].colName << "id" << "Название" << "Адрес"
            << "Примечание";

    table_settings[ttSert].title = "Аттестации";
    table_settings[ttSert].tblName = "sertifications";
    table_settings[ttSert].colName << "id" << "Спорстмен" << "Дата"
            << "Разряд с" << "Разряд на" << "Примечание";

    table_settings[ttFee].title = "Взносы";
    table_settings[ttFee].tblName = "fee";
    table_settings[ttFee].colName << "id" << "Спортсмен" << "Дата"
            << "Примечание";

    table_settings[ttSportComp].title = "Распределения \"Спортсмен - соревнование\"";
    table_settings[ttSportComp].tblName = "sportsmen_competitions";
    table_settings[ttSportComp].colName << "id" << "Спортсмен" << "Соревнование"
            << "Категория" << "№ жеребьёвки" << "Примечание";

    table_settings[ttComp].title = "Соревнования";
    table_settings[ttComp].tblName = "competitions";
    table_settings[ttComp].colName << "id" << "Название" << "Дата"
            << "Место проведения" << "Примечание";

    table_settings[ttCateg].title = "Категории";
    table_settings[ttCateg].tblName = "categories";
    table_settings[ttCateg].colWidth << 40 << 200 << 200;
    table_settings[ttCateg].colName << "id" << "Название" << "Примечание";

    table_settings[ttRank].title = "Разряд";
    table_settings[ttRank].tblName = "ranks";
    table_settings[ttRank].colName << "id" << "Название" << "Примечание";

    table_settings[ttPrzWin].title = "Призеры";
    table_settings[ttPrzWin].tblName = "prize_winners";
    table_settings[ttPrzWin].colName << "id" << "Спортсмен"
            << "Соревнование" << "Число боев"
            << "Число побед" << "Место"
            << "Регион" << "Город" << "Примечание";

    report_settings[rtSport].title = "Спортсмены";
    report_settings[rtSert].title = "Аттестации";
    report_settings[rtDraw].title = "Протокол взвешивания, мандатной комиссии и жеребьевки";

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
    return QObject::tr("Примечание");
}

void Sett::SetParam(QTableView *aView)
{
    aView->setSelectionMode(QAbstractItemView::SingleSelection); //Selection mode - single
    aView->setSelectionBehavior(QAbstractItemView::SelectRows);  //Selection mode - full row
    aView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //Disable editing
}

QString Sett::GetErrMsgTitle()
{
    return QObject::tr("Ошибка");
}

QString Sett::GetErrMsgDef()
{
    return QObject::tr("Вееденные данные не корректны");
}

QString Sett::GetRepTitle(RepType aType)
{
    return QObject::tr(report_settings[aType].title);
}
