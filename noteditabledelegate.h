#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H

#include <QItemDelegate>

class NotEditableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit NotEditableDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent)
    {}

protected:
    bool editorEvent(QEvent *, QAbstractItemModel *, const QStyleOptionViewItem &, const QModelIndex &)
    { return false; }
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
    { return Q_NULLPTR; }

};
#endif // NOTEDITABLEDELEGATE_H
