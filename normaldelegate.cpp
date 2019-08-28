#include "normaldelegate.h"
#include "comboboxdelegate.h"
#include <category.h>

#include <QComboBox>
#include <QLineEdit>
#include <QDebug>
#include <QApplication>
#include <QTimer>

NormalDelegate::NormalDelegate()
{

}

QWidget * NormalDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *line_edit = new QLineEdit(parent);
    (void) option;
    (void) index;
    return line_edit;
}
/*
void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}
*/
void NormalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *line_edit = static_cast<QLineEdit *>(editor);
    line_edit->setText(index.data().toString());
}

void NormalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *line_edit = static_cast<QLineEdit *>(editor);

    if (index.column() == 1)    // ISBN13
    {
        if (line_edit->text().length() != 13)   // Length-check
        {
            emit InvalidIsbn();
            return;
        }
        QRegExp re("\\d*"); // Type-check
        if (!re.exactMatch(line_edit->text().toStdString().c_str()))
        {
            if (line_edit->text().toStdString().back() != 'X')
            {
                emit InvalidIsbn();
                return;
            }
        }
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}

/*
QSize NormalDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}
*/
/*
void NormalDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    (void) index;
}
*/
