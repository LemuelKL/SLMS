#include "qubyxsearchfilterproxymodel.h"
#include <return.h>

#include <QDebug>
#include <QDate>

QubyxSearchFilterProxyModel::QubyxSearchFilterProxyModel()
{
    filter_enabled = true;
    filter_overdue_enabled = false;
    filter_onLoan_enabled = false;
}

bool QubyxSearchFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (filter_enabled)
    {
        for(int i = 0; i < sourceModel()->columnCount(); i++)
        {
            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
            if (cols_to_filter_.contains(index.column()))
            {
                if(sourceModel()->data(index).toString().trimmed().contains(filterRegExp()))
                {
                    QModelIndex index_due_date = sourceModel()->index(sourceRow, 4, sourceParent);
                    QModelIndex index_hv_returned = sourceModel()->index(sourceRow, 5, sourceParent);

                    QDate today = QDate::currentDate();
                    QDate due_date = QDate::fromString(index_due_date.data(Qt::EditRole).toString(), "yyyyMMdd");

                    if (filter_overdue_enabled)
                    {
                        if (Return::StringToEnum(index_hv_returned.data().toString()) == Return::YES)
                        {
                            return false;
                        }
                        else if (today <= due_date) // Haven't returned, but today is still on or before due date
                        {
                            return false;
                        }
                        else // Haven't returned and today is after the due date
                        {
                            return true;
                        }
                    }
                    if (filter_onLoan_enabled)
                    {
                        if (Return::StringToEnum(index_hv_returned.data().toString()) == Return::YES)
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    }
    return false;
}

void QubyxSearchFilterProxyModel::SetFilterEnabled(bool b)
{
    qDebug() << "Filter Enabled? " << b;
    filter_enabled = b;
}

void QubyxSearchFilterProxyModel::SetColsToFilter(QVector<int> cols)
{
    cols_to_filter_ = cols;
}

void QubyxSearchFilterProxyModel::ClearColsToFilter()
{
    cols_to_filter_.clear();
}

void QubyxSearchFilterProxyModel::SetOverdueFilterEnabled(bool enabled)
{
    filter_overdue_enabled = enabled;
}

void QubyxSearchFilterProxyModel::SetOnLoanFilterEnabled(bool enabled)
{
    filter_onLoan_enabled = enabled;
}

