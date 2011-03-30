#ifndef REPORTS_H
#define REPORTS_H

#include "setting.h"

class BaseReport {
protected:
    QSqlQuery &query;
public:
    BaseReport(QSqlQuery &aQuery): query(aQuery) {}
    virtual void makeReport() = 0;
};

class SportsMen: public BaseReport {
public:
    virtual void makeReport();
};




#endif // REPORTS_H
