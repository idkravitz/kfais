#ifndef CARD_H
#define CARD_H

#include "tableModelView.h"
#include "setting.h"

/******************************* Card (basic) *******************************/

typedef QPair<QString, QString> PairQuery;
typedef QMap<PairQuery, bool> MapQuery;

class Card: public QDialog
{
    Q_OBJECT

private:
    TableModel *tblModel;    //For update table after submit
    TblType type;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void keyPressEvent(QKeyEvent *aE);
    void closeEvent(QCloseEvent *aE);

private slots:
    void Ok();

protected:
    int id;
    QLineEdit *edtNote;

    Card(QWidget *aParent, TableModel *aModel, TblType aType, int aId);

    void CreateBasicWidgets(QLayout *aLt);

    inline void AddWid(QGridLayout *aLt, int aTblAtrI, QWidget *aW, int aRow, int aCol = 0);

    virtual bool IsValid() const;
    virtual bool Submit();

    inline bool IsNew() const;
    inline void SetRegExprInt(QLineEdit* aEdt, bool aCanBeZero = true);

    QString CreateQuary(const MapQuery &aMap);

public:
    int GetId() const;
    TblType GetType() const;
};

/******************************* Sportsmen *******************************/

class CardSport: public Card
{
    Q_OBJECT

private:
    QVector<int> vecCoachId;
    QVector<int> vecRankId;

    QLineEdit *edtName;
    QDateEdit *edtDateBirth;
    QLineEdit *edtAddr;
    QLineEdit *edtPhone;
    QLineEdit *edtWorkplace;
    QLineEdit *edtJob;
    QLineEdit *edtRegNum;
    QComboBox *cbRank;
    QComboBox *cbCoach;

    TableModel *modelFee, *modelSert, *modelPrzWin;
    TableView *viewFee, *viewSert, *viewPrzWin;

    void CreateWidgets();
    void InitWidgets();

    QVBoxLayout *CreateInnerTbls();
    inline QGroupBox *_AddTable(TableView *aView, TableModel *aModel, const QString &aTitle);

    bool IsValid() const;
    bool Submit();

private slots:
    void OpenCardRank();
    void OpenCardCoach();

public:
    CardSport(QWidget *aParent, TableModel *aModel, int aId);
};

/******************************* Coaches *******************************/

class CardCoach: public Card
{
    Q_OBJECT

private:
    QVector<int> vecClubId;

    QLineEdit *edtName;
    QLineEdit *edtPhone;
    QComboBox *cbClub;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

private slots:
    void OpenCardClub();

public:
    CardCoach(QWidget *aParent, TableModel *aTblModel, int aId);
};

/******************************* Clubs *******************************/

class CardClub: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;
    QLineEdit *edtAddr;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

public:
    CardClub(QWidget *aParent, TableModel *aTblModel, int aId);
};

/******************************* Sertifications *******************************/

class CardSert: public Card
{
    Q_OBJECT

private:
    QVector<int> vecSportId;
    QVector<int> vecRankFromId;
    QVector<int> vecRankToId;

    QComboBox *cbSport;
    QDateEdit *edtDate;
    QComboBox *cbRankFrom;
    QComboBox *cbRankTo;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

private slots:
    void OpenCardSport();
    void OpenCardRankFrom();
    void OpenCardRankTo();

public:
    CardSert(QWidget *aParent, TableModel *aTblModel, int aId);
};

/******************************* Fees *******************************/

class CardFee: public Card
{
    Q_OBJECT

private:
    QVector<int> vecSportId;

    QComboBox *cbSport;
    QDateEdit *edtDate;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

private slots:
    void OpenCardSport();

public:
    CardFee(QWidget *aParent, TableModel *aTblModel, int aId);
};


/******************************* Sportsmen-Competiotions *******************************/

class CardSportComp: public Card
{
    Q_OBJECT

private:
    QVector<int> vecSportId, vecCompId, vecCategId;

    QComboBox *cbSport;
    QComboBox *cbComp;
    QComboBox *cbCateg;
    QLineEdit *edtDrawNum;
    QLineEdit *edtUnit;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

private slots:
    void OpenCardSport();
    void OpenCardComp();
    void OpenCardCateg();

public:
    CardSportComp(QWidget *aParent, TableModel *aTblModel, int aId);
};

/******************************* Competiotions *******************************/

class CardComp: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;
    QLineEdit *edtNameProt;
    QDateEdit *edtDate;
    QLineEdit *edtLoc;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

private slots:
    void UpdateNameProt();

public:
    CardComp(QWidget *aParent, TableModel *aModel, int aId);
};

/******************************* Categories *******************************/

class CardCateg: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

public:
    CardCateg(QWidget *aParent, TableModel *aModel, int aId);
};

/******************************* Ranks *******************************/

class CardRank: public Card
{
    Q_OBJECT

private:
    QLineEdit *edtName;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

public:
    CardRank(QWidget *aParent, TableModel *aModel, int aId);
};

/******************************* Prize winners *******************************/

class CardPrzWin: public Card
{
    Q_OBJECT

private:
    QVector<int> vecSportId, vecCompId;

    QComboBox *cbSport;
    QComboBox *cbComp;
    QLineEdit *edtFightsCount;
    QLineEdit *edtFightsWon;
    QLineEdit *edtPlace;
    QLineEdit *edtRegion;
    QLineEdit *edtCity;

    void CreateWidgets();
    void InitWidgets();

    bool IsValid() const;
    bool Submit();

private slots:
    void UpdateCBSport(int aIndex);

    void OpenCardComp();
    void OpenCardSport();

public:
    CardPrzWin(QWidget *aParent, TableModel *aModel, int aId);
};

/******************************* Mapper card *******************************/

typedef QPair<TblType, int> KeyMapCard_;
typedef QPair<Card *, QWidget *> ValMapCard_;
typedef QMap<KeyMapCard_, ValMapCard_> MapCard_;

class MapperCard: public QObject
{
    Q_OBJECT

private:
    MapCard_ mapCard;

private slots:
    void CloseCard(QObject *aObj);

public:
    MapperCard();

    bool SetCard(TblType aType, int aId);
    void InsertCard(TblType aType, int aId, Card *aCard, QWidget *aParent);
};

extern MapperCard mapperCard;

#endif // CARD_H
