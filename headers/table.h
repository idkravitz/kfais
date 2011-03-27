#ifndef TABLE_H
#define TABLE_H

#include "setting.h"
#include "card.h"

class Table: public QMainWindow
{
    Q_OBJECT

private:
    Setting::TblType type;
    QTableView *view;
    QSqlRelationalTableModel *model;

    void CreateWidgets();

private slots:
    void SetFirst();
    void SetNext();
    void SetPrev();
    void SetLast();
    void Add();
    void Delete();
    void Edit();

private:
    void ApplyTableSettings();
    void SaveTableSettings();

protected:
    virtual void TableSpecificConfig();

public:
    Table(QWidget *aParent, Setting::TblType aType);    
    ~Table();
    Setting::TblType Type() const;
};

/******************************* Sportsmens *******************************/

class TblSport: public Table
{
    Q_OBJECT

public:
    TblSport(QWidget *aParent = 0);
};

/******************************* Trainers *******************************/

class TblCoach: public Table
{
    Q_OBJECT

public:
    TblCoach(QWidget *aParent = 0);
};

/******************************* Clubs *******************************/

class TblClub: public Table
{
    Q_OBJECT

public:
    TblClub(QWidget *aParent = 0);
};

/******************************* Certifications *******************************/

class TblSert: public Table
{
    Q_OBJECT

public:
    TblSert(QWidget *aParent = 0);
};

/******************************* Fees *******************************/

class TblFee: public Table
{
    Q_OBJECT

public:
    TblFee(QWidget *aParent = 0);
};


/******************************* Sportsmen-Competiotions *******************************/

class TblSportComp: public Table
{
    Q_OBJECT

public:
    TblSportComp(QWidget *aParent = 0);
};

/******************************* Competiotions *******************************/

class TblComp: public Table
{
    Q_OBJECT

public:
    TblComp(QWidget *aParent = 0);
};

/******************************* Categories *******************************/

class TblCateg: public Table
{
    Q_OBJECT

public:
    TblCateg(QWidget *aParent = 0);
};

#endif // TABLE_H

