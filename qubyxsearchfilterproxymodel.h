#ifndef QUBYXSEARCHFILTERPROXYMODEL_H
#define QUBYXSEARCHFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class QubyxSearchFilterProxyModel : public QSortFilterProxyModel
{
public:
    QubyxSearchFilterProxyModel();
    void ClearColsToFilter();
    void SetColsToFilter(QVector<int>);

    void SetOverdueFilterEnabled(bool);
    void SetOnLoanFilterEnabled(bool);

public slots:
    void SetFilterEnabled(bool);

protected:
    bool filterAcceptsRow(int, const QModelIndex &) const;

private:
    bool filter_enabled;
    bool filter_overdue_enabled;
    bool filter_onLoan_enabled;
    QVector<int> cols_to_filter_;
};

#endif // QUBYXSEARCHFILTERPROXYMODEL_H
