#include "../headers/card.h"

using namespace Setting;

Card::Card(QWidget *aParent, Setting::TblType aType):
        QDialog(aParent),
        type(aType)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

/******************************* Sportsmen *******************************/

CardSport::CardSport(QWidget *aParent):
        Card(aParent, ttSport)
{

}

/******************************* Trainers *******************************/

CardCoach::CardCoach(QWidget *aParent):
        Card(aParent, ttCoach)
{

}

/******************************* Clubs *******************************/

CardClub::CardClub(QWidget *aParent):
        Card(aParent, ttClub)
{

}

/******************************* Sertifications *******************************/

CardSert::CardSert(QWidget *aParent):
        Card(aParent, ttSert)
{

}

/******************************* Fee *******************************/

CardFee::CardFee(QWidget *aParent):
        Card(aParent, ttFee)
{

}

/******************************* Sportsmen-Competiotions *******************************/

CardSportComp::CardSportComp(QWidget *aParent):
        Card(aParent, ttSportComp)
{

}

/******************************* Competiotions *******************************/

CardComp::CardComp(QWidget *aParent):
        Card(aParent, ttComp)
{

}

/******************************* Categories *******************************/

CardCateg::CardCateg(QWidget *aParent):
        Card(aParent, ttCateg)
{

}
