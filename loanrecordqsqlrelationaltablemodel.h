#ifndef LOANRECORDQSQLRELATIONALTABLEMODEL_H
#define LOANRECORDQSQLRELATIONALTABLEMODEL_H

#include <QObject>
#include <QSqlRelationalTableModel>
#include <QColor>

class LoanRecordQSqlRelationalTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    LoanRecordQSqlRelationalTableModel(QObject *, QSqlDatabase);

    void SetHightlightOverdueEnabled(bool enabled);
    void SetHightlightOnLoanEnabled(bool enabled);

    void SetQDateFormat(QString);

public slots:

private:
    bool highlight_overdue_enabled_;
    bool highlight_onLoan_enabled_;
    QColor overdue_color_;
    QColor onLoan_color_;
    QString qDate_format_;

protected:
    virtual QVariant data(const QModelIndex&, int) const override;
    virtual bool setData(const QModelIndex&, const QVariant&, int) override;

};
#endif // LOANRECORDQSQLRELATIONALTABLEMODEL_H
