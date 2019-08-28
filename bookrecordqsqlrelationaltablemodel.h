#ifndef MYQSQLTABLEMODEL_H
#define MYQSQLTABLEMODEL_H

#include <QObject>
#include <QSqlRelationalTableModel>

class BookRecordQSqlRelationalTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    BookRecordQSqlRelationalTableModel(QObject *, QSqlDatabase);

signals:
    void DataIsEmpty(QModelIndex);

public slots:

protected:
    virtual QVariant data(const QModelIndex&, int) const override;
    virtual bool setData(const QModelIndex&, const QVariant&, int) override;
};

#endif // MYQSQLTABLEMODEL_H
