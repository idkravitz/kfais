#ifndef TABLE_H
#define TABLE_H

#include "setting.h"

class Table: public QMainWindow
{
    Q_OBJECT

public:
    Table(QWidget *aParent = 0);
};

/******************************* Sportsmen *******************************/

class TblSportmen: public Table
{
public:
    TblSportmen(QWidget *aParent = 0);
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
