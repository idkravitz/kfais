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

    inline void _SetCBModel(QComboBox *aCB, int aIn, int aOut);

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
    QLineEdit *edtRegNum;
    QComboBox *cbRank;
    QComboBox *cbCoach;

    QSqlRelationalTableModel *modelFee, *modelSert, *modelSC;
    QTableView *viewFee, *viewSert, *viewSC;

    void CreateWidgets();
    QVBoxLayout *CreateInnerTbls();
    inline QTableView *_InitViewModel(QTableView *aView, QSqlRelationalTableModel *aModel, TblType aType);
    inline QGroupBox *_AddTable(TblType aType, QTableView *aView, QSqlRelationalTableModel *aModel);
    inline QGroupBox *_AddTable(TblType aType, QTableView *aView, QSqlRelationalTableModel *aModel, const QString &aTitle);

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

/******************************* Sertifications *******************************/

class CardSert: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtNum;
    QComboBox *cbSport;
    QDateEdit *edtDate;
    QComboBox *cbRankFrom;
    QComboBox *cbRankTo;
    QLineEdit *edtRes;

    void CreateWidgets();

public:
    CardSert(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Fees *******************************/

class CardFee: public Card
{
    Q_OBJECT

private:
    QComboBox *cbSport;
    QDateEdit *edtDate;

    void CreateWidgets();

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
