#include "table.h"

Table::Table(QWidget *aParent):
        QMainWindow(aParent)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

/******************************* Sportsmen *******************************/

TblSportmen::TblSportmen(QWidget *aParent):
        Table(aParent)
{

}

/******************************* Trainer *******************************/

TblTrainer::TblTrainer(QWidget *aParent):
        Table(aParent)
{

}

/******************************* Club *******************************/

TblClub::TblClub(QWidget *aParent):
        Table(aParent)
{

}
