#ifndef CARD_H
#define CARD_H

#include "setting.h"

class Card: public QDialog
{
    Q_OBJECT

private:
    Setting::TblType type;

protected:
    Card(QWidget *aParent, Setting::TblType aType);
};

/******************************* Sportsmens *******************************/

class CardSport: public Card
{
    Q_OBJECT

public:
    CardSport(QWidget *aParent = 0);
};

/******************************* Trainers *******************************/

class CardCoach: public Card
{
    Q_OBJECT

public:
    CardCoach(QWidget *aParent = 0);
};

/******************************* Clubs *******************************/

class CardClub: public Card
{
    Q_OBJECT

public:
    CardClub(QWidget *aParent = 0);
};

/******************************* Certifications *******************************/

class CardSert: public Card
{
    Q_OBJECT

public:
    CardSert(QWidget *aParent = 0);
};

/******************************* Fees *******************************/

class CardFee: public Card
{
    Q_OBJECT

public:
    CardFee(QWidget *aParent = 0);
};


/******************************* Sportsmen-Competiotions *******************************/

class CardSportComp: public Card
{
    Q_OBJECT

public:
    CardSportComp(QWidget *aParent = 0);
};

/******************************* Competiotions *******************************/

class CardComp: public Card
{
    Q_OBJECT

public:
    CardComp(QWidget *aParent = 0);
};

/******************************* Categories *******************************/

class CardCateg: public Card
{
    Q_OBJECT

public:
    CardCateg(QWidget *aParent = 0);
};

#endif // CARD_H
