#include "comboboxdelegate.h"
#include <category.h>
#include <status.h>
#include <myqsqlrelationaldelegate.h>

#include <QComboBox>
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QSortFilterProxyModel>
#include <QAbstractItemModel>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) : QSqlRelationalDelegate (parent)
{
    pMy_ = new MyQSqlRelationalDelegate();
    connect(pMy_, &MyQSqlRelationalDelegate::closeEditor, this, &ComboBoxDelegate::CommitAndClose);
}

QWidget * ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QSortFilterProxyModel *proxy = qobject_cast<const QSortFilterProxyModel*>(index.model());
    auto base_index = proxy->mapToSource(index);
    return QSqlRelationalDelegate::createEditor(parent, option, base_index);
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QSortFilterProxyModel *proxy = qobject_cast<const QSortFilterProxyModel*>(index.model());
    auto base_index = proxy->mapToSource(index);
    QSqlRelationalDelegate::setEditorData(editor, base_index);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const QSortFilterProxyModel *proxy = qobject_cast<const QSortFilterProxyModel*>(model);
    auto base_index = proxy->mapToSource(index);
    QSqlRelationalTableModel *base_model = qobject_cast<QSqlRelationalTableModel*>(proxy->sourceModel());
    QSqlRelationalDelegate::setModelData(editor, base_model, base_index);
}

QSize ComboBoxDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto hint = QSqlRelationalDelegate::sizeHint(option, index);

    QFontMetrics fm(option.font);
    QStyleOptionComboBox comboOption;
    comboOption.rect = option.rect;
    comboOption.state = option.state | QStyle::State_Enabled;

    if (index.column() == 4)
    {
        Q_FOREACH (const auto& value, Category::AllCategoryStrings())
        {
            hint = hint.expandedTo(qApp->style()->sizeFromContents(QStyle::CT_ComboBox, &comboOption, QSize(fm.horizontalAdvance(value), hint.height())));
        }
    }
    if (index.column() == 5)
    {
        Q_FOREACH (const auto& value, Status::AllStatusStrings())
        {
            hint = hint.expandedTo(qApp->style()->sizeFromContents(QStyle::CT_ComboBox, &comboOption, QSize(fm.horizontalAdvance(value), hint.height())));
        }
    }

    return hint;
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    (void) index;
}


void ComboBoxDelegate::CommitAndClose()
{
    QComboBox *editor = qobject_cast<QComboBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

