#ifndef TABLE_H
#define TABLE_H

#include "../headers/setting.h"

class Table: public QMainWindow
{
    Q_OBJECT

private:
    Setting::TblType type;

public:
    Table(QWidget *aParent, Setting::TblType aType);

    Setting::TblType Type() const;
};

/******************************* Sportsmen *******************************/

class TblSportsmen: public Table
{
public:
    TblSportsmen(QWidget *aParent = 0);
};

/******************************* Trainer *******************************/

class TblTrainer: public Table
{
public:
    TblTrainer(QWidget *aParent = 0);
};

/******************************* Club *******************************/

class TblClub: public Table
{
public:
    TblClub(QWidget *aParent = 0);
};

#endif // TABLE_H
