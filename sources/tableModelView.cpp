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
    QString str = query().executedQuery();
    emit BeforeRefresh();
    setQuery("DELETE FROM " + aTblName + " WHERE " + aCondition);
    setQuery(str);
    emit Refresh();
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
    emit BeforeRefresh();

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

void TableModel::sort(int column, Qt::SortOrder order)
{
    qSort = QString("ORDER BY %1 %2").arg(column + 1).arg(order == Qt::AscendingOrder ? "ASC": "DESC");
    Select();
}
