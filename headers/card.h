#ifndef CARD_H
#define CARD_H

#include "setting.h"

/******************************* Card (basic) *******************************/

class Card: public QDialog
{
    Q_OBJECT

private:
    Setting::TblType type;
    int id;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void Ok();
    void closeEvent(QCloseEvent *aE);

protected:
    QSqlRelationalTableModel *model;
    QLineEdit *edtNote;

    Card(QWidget *aParent, Setting::TblType aType, int aId);
    void CreateBasicWidgets(QLayout *aLt);

public:
    int GetId() const;
};

/******************************* Sportsmen *******************************/

class CardSport: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;
    QDateEdit *edtDateBirth;
    QLineEdit *edtAddr;
    QLineEdit *edtPhone;
    QLineEdit *edtWorkplace;
    QLineEdit *edtJob;
    QSpinBox *sbRegNum;
    QSpinBox *sbRank;
    QComboBox *cbCoach;

    void CreateWidgets();

public:
    CardSport(QWidget *aParent, int aId);
};

/******************************* Trainers *******************************/

class CardCoach: public Card
{
    Q_OBJECT

public:
    CardCoach(QWidget *aParent, int aId);
};

/******************************* Clubs *******************************/

class CardClub: public Card
{
    Q_OBJECT

public:
    CardClub(QWidget *aParent, int aId);
};

/******************************* Certifications *******************************/

class CardSert: public Card
{
    Q_OBJECT

public:
    CardSert(QWidget *aParent, int aId);
};

/******************************* Fees *******************************/

class CardFee: public Card
{
    Q_OBJECT

public:
    CardFee(QWidget *aParent, int aId);
};


/******************************* Sportsmen-Competiotions *******************************/

class CardSportComp: public Card
{
    Q_OBJECT

public:
    CardSportComp(QWidget *aParent, int aId);
};

/******************************* Competiotions *******************************/

class CardComp: public Card
{
    Q_OBJECT

public:
    CardComp(QWidget *aParent, int aId);
};

/******************************* Categories *******************************/

class CardCateg: public Card
{
    Q_OBJECT

public:
    CardCateg(QWidget *aParent, int aId);
};

#endif // CARD_H
