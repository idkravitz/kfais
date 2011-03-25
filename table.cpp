#include "table.h"

using namespace Setting;

Table::Table(QWidget *aParent, TblType aType):
        QMainWindow(aParent),
        type(aType)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

TblType Table::Type() const
{
    return type;
}

/******************************* Sportsmen *******************************/

TblSportmen::TblSportmen(QWidget *aParent):
        Table(aParent, ttSportsmen)
{

}

/******************************* Trainer *******************************/

TblTrainer::TblTrainer(QWidget *aParent):
        Table(aParent, ttTrainer)
{

}

/******************************* Club *******************************/

TblClub::TblClub(QWidget *aParent):
        Table(aParent, ttClub)
{

}
