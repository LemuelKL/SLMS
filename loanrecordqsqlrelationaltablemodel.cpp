#include "loanrecordqsqlrelationaltablemodel.h"

#include <adminpanel.h>
#include <QtDebug>
#include <return.h>
#include <QFileIconProvider>
#include <QDate>

LoanRecordQSqlRelationalTableModel::LoanRecordQSqlRelationalTableModel(QObject * parent, QSqlDatabase db = QSqlDatabase())  : QSqlRelationalTableModel(parent, db)
{
    qDate_format_ = "yyyyMMdd";
}

QVariant LoanRecordQSqlRelationalTableModel::data(const QModelIndex & index, int role = Qt::DisplayRole) const
{
    if (index.column() == AdminPanel::LoanRecordTableViewColumns::HAVE_RETURNED)
    {
        QVariant value = QSqlRelationalTableModel::data(index, Qt::DisplayRole);
        if (role == Qt::DecorationRole)
        {
            QFileIconProvider icon_provider;
            if (Return::StringToEnum(value.toString()) == Return::YES)
            {
                return QPixmap(":/remix_icons/resources/icons/check-line.svg");
            }
            if (Return::StringToEnum(value.toString()) == Return::NO)
            {
                return QPixmap(":/remix_icons/resources/icons/close-line.svg");
            }
            if (Return::StringToEnum(value.toString()) == Return::UNKNOWN)
            {
                return QPixmap(":/remix_icons/resources/icons/question-line.svg");
            }
        }
        if (highlight_overdue_enabled_ && role == Qt::BackgroundRole)
        {
            QModelIndex index_hv_returned = index.sibling(index.row(), 5);
            if (Return::StringToEnum(index_hv_returned.data().toString()) == Return::NO)
            {
                QModelIndex index_due_date = index.sibling(index.row(), 4);
                QString str_due_date = index_due_date.data(Qt::EditRole).toString();
                QDate due_date = QDate::fromString(str_due_date, "yyyyMMdd");
                if (QDate::currentDate() > due_date)
                    return QColor(Qt::GlobalColor::red);
            }
        }
    }
    if (highlight_onLoan_enabled_ && role == Qt::BackgroundRole)
    {
        QModelIndex index_hv_returned = index.sibling(index.row(), 5);
        if (Return::StringToEnum(index_hv_returned.data().toString()) == Return::NO)
            return QColor(Qt::GlobalColor::yellow);
    }
    if (index.column() == AdminPanel::LoanRecordTableViewColumns::LOAN_DATE || index.column() == AdminPanel::LoanRecordTableViewColumns::DUE_DATE)
    {
        if (role == Qt::DisplayRole)
        {
            QVariant value = QSqlRelationalTableModel::data(index, Qt::DisplayRole);
            QDate date = QDate::fromString(value.toString(), "yyyyMMdd");
            return date.toString(qDate_format_);
        }
    }
    return QSqlRelationalTableModel::data(index, role);
}


bool LoanRecordQSqlRelationalTableModel::setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole)
{
    return QSqlRelationalTableModel::setData(index, value, role);
}

void LoanRecordQSqlRelationalTableModel::SetHightlightOverdueEnabled(bool enabled)
{
    highlight_overdue_enabled_ = enabled;
}

void LoanRecordQSqlRelationalTableModel::SetHightlightOnLoanEnabled(bool enabled)
{
    highlight_onLoan_enabled_ = enabled;
}

void LoanRecordQSqlRelationalTableModel::SetQDateFormat(QString format)
{
    qDate_format_ = format;
    qDebug() << "LoanRecordQSqlRelationalTableModel qDate_format updated" << qDate_format_;
}
