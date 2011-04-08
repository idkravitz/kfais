#include "controlPanel.h"

ControlPanel::ControlPanel(QWidget *aParent):
        QToolBar(aParent)
{
    CreateWidgets();
    InitWidgets();
    setFloatable(false);
    setAllowedAreas(Qt::BottomToolBarArea | Qt::TopToolBarArea);
}

void ControlPanel::CreateWidgets()
{
    ltH = new QGridLayout;

    AddWidToLt(ltH, lblSport = new QLabel(tr("Спортсмен:")), cbSport = new QComboBox, 0, 0);
    ltH->addWidget(btnSport = new BtnCardSport(cbSport, &vecSportId, this), 0, 2);

    AddWidToLt(ltH, lblCoach = new QLabel(tr("Тренер:")), cbCoach = new QComboBox, 0, 3);
    ltH->addWidget(btnCoach = new BtnCardCoach(cbCoach, &vecCoachId, this), 0, 5);

    AddWidToLt(ltH, lblClub = new QLabel(tr("Клуб:")), cbClub = new QComboBox, 0, 6);
    ltH->addWidget(btnClub = new BtnCardClub(cbClub, &vecClubId, this), 0, 8);

    AddWidToLt(ltH, lblComp = new QLabel(tr("Соревнование:")), cbComp = new QComboBox, 1, 0);
    ltH->addWidget(btnComp = new BtnCardComp(cbComp, &vecCompId, this), 1, 2);

    AddWidToLt(ltH, lblRank = new QLabel(tr("Разряд:")), cbRank = new QComboBox, 1, 3);
    ltH->addWidget(btnRank = new BtnCardRank(cbRank, &vecRankId, this), 1, 5);

    AddWidToLt(ltH, lblCateg = new QLabel(tr("Категория:")), cbCateg = new QComboBox, 1, 6);
    ltH->addWidget(btnCateg = new BtnCardCateg(cbCateg, &vecCategId, this), 1, 8);

    gb = new QGroupBox;
    gb->setLayout(ltH);
    addWidget(gb);
}

void ControlPanel::InitWidgets()
{
    InitComboBox(cbSport, vecSportId, "SELECT id, name FROM sportsmen", 0);
    InitComboBox(cbCoach, vecCoachId, "SELECT id, name FROM coaches", 0);
    InitComboBox(cbClub, vecClubId, "SELECT id, name FROM clubs", 0);
    InitComboBox(cbComp, vecCompId, "SELECT id, name || ' ' || date FROM competitions", 0);
    InitComboBox(cbRank, vecRankId, "SELECT id, name FROM ranks", 0);
    InitComboBox(cbCateg, vecCategId, "SELECT id, name FROM categories", 0);
}
