#ifndef NORMALDELEGATE_H
#define NORMALDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>

class NormalDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    NormalDelegate();

signals:
    void InvalidIsbn() const;

protected:
    // https://doc.qt.io/qt-5/qstyleditemdelegate.html#reimplemented-public-functions
    virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    //
    //virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // NORMALDELEGATE_H
