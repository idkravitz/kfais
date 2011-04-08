#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "card.h"

class ControlPanel: public QToolBar
{
    Q_OBJECT

private:
    QGridLayout *ltH, *ltV;
    QGroupBox *gb;
    QLabel *lblSport, *lblCoach, *lblClub, *lblComp, *lblRank, *lblCateg;
    QComboBox *cbSport, *cbCoach, *cbClub, *cbComp, *cbRank, *cbCateg;
    QVector<int> vecSportId, vecCoachId, vecClubId, vecCompId, vecRankId, vecCategId;
    BtnCardSport *btnSport;
    BtnCardCoach *btnCoach;
    BtnCardClub *btnClub;
    BtnCardComp *btnComp;
    BtnCardRank *btnRank;
    BtnCardCateg *btnCateg;

    void CreateWidgets();
    void InitWidgets();

public:
    ControlPanel(QWidget *aParent = 0);
};

#endif // CONTROLPANEL_H
