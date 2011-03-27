#ifndef TABLE_H
#define TABLE_H

#include "setting.h"
#include "card.h"

/******************************* Card (basic) *******************************/

typedef QMap<int, Card *> MapCard;

class Table: public QMainWindow
{
    Q_OBJECT

private:
    Setting::TblType type;
    QTableView *view;
    MapCard mapCard;

    void CreateWidgets();

    void ApplyTableSettings();
    void SaveTableSettings();

private slots:
    void SetFirst();
    void SetNext();
    void SetPrev();
    void SetLast();
    void Add();
    void Delete();
    void Edit();

    void OpenCard(QModelIndex aMIndex);
    void CloseCard(QObject *aObj);

protected:
    QSqlRelationalTableModel *model;

    void Init(const QString &aTitle, const QString &aTblName);
    virtual Card *CreateCard(int aId) const = 0;

    virtual void TableSpecificConfig();

public:
    Table(QWidget *aParent, Setting::TblType aType);    
    ~Table();
    Setting::TblType Type() const;
};

/******************************* Sportsmen *******************************/

class TblSport: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblSport(QWidget *aParent = 0);
};

/******************************* Coaches *******************************/

class TblCoach: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblCoach(QWidget *aParent = 0);
};

/******************************* Clubs *******************************/

class TblClub: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblClub(QWidget *aParent = 0);
};

/******************************* Certifications *******************************/

class TblSert: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblSert(QWidget *aParent = 0);
};

/******************************* Fee *******************************/

class TblFee: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblFee(QWidget *aParent = 0);
};


/******************************* Sportsmen-Competiotions *******************************/

class TblSportComp: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblSportComp(QWidget *aParent = 0);
};

/******************************* Competiotions *******************************/

class TblComp: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblComp(QWidget *aParent = 0);
};

/******************************* Categories *******************************/

class TblCateg: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblCateg(QWidget *aParent = 0);
};

/******************************* Ranks *******************************/

class TblRank: public Table
{
    Q_OBJECT

private:
    Card *CreateCard(int aId) const;

public:
    TblRank(QWidget *aParent = 0);
};

#endif // TABLE_H

