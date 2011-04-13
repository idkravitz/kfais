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

    QString CreateQuery(const MapQuery &aMap);

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
    void SetParentNull(QObject *aObj);

public:
    MapperCard();

    bool IsExist(TblType aType, int aId);
    bool SetCard(TblType aType, int aId);
    void InsertCard(TblType aType, int aId, Card *aCard, QWidget *aParent);
};

extern MapperCard mapperCard;

/******************************* Button for open card *******************************/

class BtnCard: public QPushButton
{
    Q_OBJECT

private:
    TblType type;
    QVector<int> *vecId;
    QComboBox *cb;
    QWidget *parent;

private slots:
    void OpenCard();

protected:
    BtnCard(TblType aType, QComboBox *aCB, QVector<int> *aVecId, QWidget *aParent);

    virtual Card *CreateCard(int aId) = 0;
};

class BtnCardSport: public BtnCard
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) {return new CardSport(Sett::GetMA(), 0, aId);}

public:
    BtnCardSport(QComboBox *aCB, QVector<int> *aVecId, QWidget *aParent):
            BtnCard(ttSport, aCB, aVecId, aParent) {}
};

class BtnCardCoach: public BtnCard
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) {return new CardCoach(Sett::GetMA(), 0, aId);}

public:
    BtnCardCoach(QComboBox *aCB, QVector<int> *aVecId, QWidget *aParent):
            BtnCard(ttCoach, aCB, aVecId, aParent) {}
};

class BtnCardClub: public BtnCard
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) {return new CardClub(Sett::GetMA(), 0, aId);}

public:
    BtnCardClub(QComboBox *aCB, QVector<int> *aVecId, QWidget *aParent):
            BtnCard(ttClub, aCB, aVecId, aParent) {}
};

class BtnCardComp: public BtnCard
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) {return new CardComp(Sett::GetMA(), 0, aId);}

public:
    BtnCardComp(QComboBox *aCB, QVector<int> *aVecId, QWidget *aParent):
            BtnCard(ttComp, aCB, aVecId, aParent) {}
};

class BtnCardRank: public BtnCard
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) {return new CardRank(Sett::GetMA(), 0, aId);}

public:
    BtnCardRank(QComboBox *aCB, QVector<int> *aVecId, QWidget *aParent):
            BtnCard(ttRank, aCB, aVecId, aParent) {}
};

class BtnCardCateg: public BtnCard
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) {return new CardCateg(Sett::GetMA(), 0, aId);}

public:
    BtnCardCateg(QComboBox *aCB, QVector<int> *aVecId, QWidget *aParent):
            BtnCard(ttCateg, aCB, aVecId, aParent) {}
};

#endif // CARD_H
