#ifndef TABLEMODELVIEW_H
#define TABLEMODELVIEW_H

#include "setting.h"

class TableView: public QTableView
{
    Q_OBJECT

private:
    TblType type;

public:
    TableView(QWidget *aParent = 0);
};

class TableModel: public QSqlQueryModel
{
    Q_OBJECT

private:
    QString qMain;
    QString qFilter;
    QString qSort;

signals:
    void Refresh();

public:
    TableModel(QWidget *aParent = 0);

    void SetQuery(const QString &aQuery);
    void SetFilter(const QString &aFilter);
    void SetSort(const QString &aSort);

    void DelRecord(const QString &aTblName, const QString &aCondition);
    QVariant GetVal(int aRow, int aCol);
    int GetId(int aRow);

    void Select();
};

#endif // TABLEMODELVIEW_H
