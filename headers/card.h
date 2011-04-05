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
    void InitModel(int aId);
    void AddWid(QGridLayout *aLt, int aTblAtrI, QWidget *aW, int aRow, int aCol = 0);

    virtual bool IsValid() const;

    inline void _SetCBModel(QComboBox *aCB, int aIn, int aOut);
    inline void SetRegExprInt(QLineEdit* aEdt, bool aCanBeZero = true);

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

    bool IsValid() const;

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

    bool IsValid() const;

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

    bool IsValid() const;

public:
    CardClub(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Sertifications *******************************/

class CardSert: public Card
{
    Q_OBJECT

private:
    QComboBox *cbSport;
    QDateEdit *edtDate;
    QComboBox *cbRankFrom;
    QComboBox *cbRankTo;

    void CreateWidgets();

    bool IsValid() const;

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

    bool IsValid() const;

public:
    CardFee(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};


/******************************* Sportsmen-Competiotions *******************************/

class CardSportComp: public Card
{
    Q_OBJECT

private:
    QComboBox *cbSport;
    QComboBox *cbComp;
    QComboBox *cbCateg;
    QLineEdit *edtDrawNum;
    QLineEdit *edtUnit;

    void CreateWidgets();

    bool IsValid() const;

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

    bool IsValid() const;

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

    bool IsValid() const;

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

    bool IsValid() const;

public:
    CardRank(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

/******************************* Prize winners *******************************/

class CardPrzWin: public Card
{
    Q_OBJECT

private:
    QVector<int> vecSportId, vecCompId;

    QComboBox *cbSport;
    QComboBox *cbComp;
    QLineEdit *edtSportComp;    //For hack
    QLineEdit *edtFightsCount;
    QLineEdit *edtFightsWon;
    QLineEdit *edtPlace;
    QLineEdit *edtRegion;
    QLineEdit *edtCity;

    void CreateWidgets();

    bool IsValid() const;

private slots:
    void UpdateCBSport(int aIndex);

public:
    CardPrzWin(QWidget *aParent, QSqlRelationalTableModel *aTblModel, int aId);
};

#endif // CARD_H
