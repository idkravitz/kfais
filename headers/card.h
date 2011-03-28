#ifndef CARD_H
#define CARD_H

#include "setting.h"

/******************************* Card (basic) *******************************/

class Card: public QDialog
{
    Q_OBJECT

private:
    QSqlRelationalTableModel *tblModel;    //For update table after submit
    TblType type;
    int id;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void closeEvent(QCloseEvent *aE);

private slots:
    void Ok();
    void Cancel();

protected:
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    QLineEdit *edtNote;

    Card(QWidget *aParent, QSqlRelationalTableModel *aTblModel, TblType aType, int aId);
    void CreateBasicWidgets(QLayout *aLt);
    void InitModel(const QString &aFilter);
    void AddWidToLt(QGridLayout *aLt, int aTblAtrI, QWidget *aW, int aRow, int aCol = 0);

    virtual bool IsValid() const;

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
    CardSport(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Coaches *******************************/

class CardCoach: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;
    QLineEdit *edtPhone;
    QComboBox *cbClub;

    void CreateWidgets();

public:
    CardCoach(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Clubs *******************************/

class CardClub: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;
    QLineEdit *edtAddr;

    void CreateWidgets();

public:
    CardClub(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Certifications *******************************/

class CardSert: public Card
{
    Q_OBJECT

public:
    CardSert(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Fees *******************************/

class CardFee: public Card
{
    Q_OBJECT

public:
    CardFee(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};


/******************************* Sportsmen-Competiotions *******************************/

class CardSportComp: public Card
{
    Q_OBJECT

public:
    CardSportComp(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Competiotions *******************************/

class CardComp: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;
    QDateEdit *edtDate;
    QLineEdit *edtLoc;

    void CreateWidgets();

public:
    CardComp(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Categories *******************************/

class CardCateg: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;

    void CreateWidgets();

public:
    CardCateg(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Ranks *******************************/

class CardRank: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;

    void CreateWidgets();

public:
    CardRank(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

#endif // CARD_H
