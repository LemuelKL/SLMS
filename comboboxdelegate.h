#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <myqsqlrelationaldelegate.h>

#include <QStringList>
#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QSqlRelationalDelegate>

class ComboBoxDelegate : public QSqlRelationalDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(QObject *parent = nullptr);

    MyQSqlRelationalDelegate *pMy_;

protected:
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

#endif // COMBOBOXDELEGATE_H
