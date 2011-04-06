#include "tableModelView.h"

TableView::TableView(QWidget *aParent):
        QTableView(aParent)
{
    setSelectionMode(QAbstractItemView::SingleSelection); //Selection mode - single
    setSelectionBehavior(QAbstractItemView::SelectRows);  //Selection mode - full row
    setEditTriggers(QAbstractItemView::NoEditTriggers);   //Disable editing
    horizontalHeader()->setHighlightSections(false);
}

TableModel::TableModel(QWidget *aParent):
        QSqlQueryModel(aParent)
{

}

void TableModel::DelRecord(const QString &aTblName, const QString &aCondition)
{
    QString q = query().executedQuery();
    setQuery("DELETE FROM " + aTblName + " WHERE " + aCondition);
    setQuery(q);
}

QVariant TableModel::GetVal(int aRow, int aCol)
{
    return record(aRow).value(aCol);
}

int TableModel::GetId(int aRow)
{
    return record(aRow).value(0).toInt();
}

void TableModel::Select()
{
    QString str = qMain;
    if (!qFilter.isEmpty()) str += " WHERE " + qFilter;
    if (!qSort.isEmpty()) str +=  " " + qSort;
    setQuery(str);

    emit Refresh();
}

void TableModel::SetQuery(const QString &aQuery)
{
    qMain = aQuery;
}

void TableModel::SetFilter(const QString &aFilter)
{
    qFilter = aFilter;
}

void TableModel::SetSort(const QString &aSort)
{
    qSort = aSort;
}
