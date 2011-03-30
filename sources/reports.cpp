#include "reports.h"
#include <QAxObject>

void SportsMen::makeReport()
{
    QAxObject *excel = new QAxObject("Excel.Application", 0);
    excel->dynamicCall("SetVisible(bool)", true); //делаем его видимым
}
