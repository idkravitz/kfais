#ifndef REPORTS_H
#define REPORTS_H

#include "setting.h"

class BaseReport {
protected:
    QSqlQuery *query;
public:
    BaseReport(QSqlQuery *aQuery = 0):
        query(aQuery) {}
    virtual void makeReport() = 0;
    void setQuery(QSqlQuery *aQuery) { query = aQuery; }
};

class SportsMen: public BaseReport {
public:
    virtual void makeReport();
};


#endif // REPORTS_H
