#ifndef MYQSQLRELATIONALDELEGATE_H
#define MYQSQLRELATIONALDELEGATE_H

#include <QStringList>
#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QSqlRelationalDelegate>


class MyQSqlRelationalDelegate : public QSqlRelationalDelegate
{
    Q_OBJECT
public:
    explicit MyQSqlRelationalDelegate(QObject *parent = nullptr);

//protected:
    // https://doc.qt.io/qt-5/qstyleditemdelegate.html#reimplemented-public-functions
    virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    //
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


signals:

public slots:
    void CommitAndClose();



private:

};

#endif // MYQSQLRELATIONALDELEGATE_H
