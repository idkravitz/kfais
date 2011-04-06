#ifndef TABLEMODELVIEW_H
#define TABLEMODELVIEW_H

#include "setting.h"

class TableView: public QTableView
{
    Q_OBJECT

public:
    TableView(QWidget *aParent = 0);
};

class TableModel: public QSqlQueryModel
{
    Q_OBJECT

public:
    TableModel(QWidget *aParent = 0);

    void DelRecord(const QString &aTblName, const QString &aCondition);
    QVariant GetVal(int aRow, int aCol);
    int GetId(int aRow);

    void Refresh();
};

#endif // TABLEMODELVIEW_H
