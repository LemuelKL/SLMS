#include "normaldelegate.h"
#include "comboboxdelegate.h"
#include <category.h>

#include <QComboBox>
#include <QLineEdit>
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <isbn13validator.h>

NormalDelegate::NormalDelegate()
{

}

QWidget * NormalDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *line_edit = new QLineEdit(parent);
    (void) option;
    (void) index;
    line_edit->setMaxLength(13);
    return line_edit;
}

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
        QRegExp rx("(?=.{13}$)97(?:8|9)\\d{1,10}\\1$");
        QRegExpValidator v(rx, 0);

        QString text = line_edit->text();
        int pos = 0;
        if (v.validate(text, pos) == 0)
        {
            emit InvalidIsbn();
        }
        else
        {
            QString input = line_edit->text();
            input = input.trimmed();
            qDebug() << "Original input:" << input;
            long long int d = input.toLongLong();
            qDebug() << "input toInt:" << d;
            long long int input_check_digit = d/1%10;
            qDebug() << "input_check_digit" << input_check_digit;

            int cal_check_digit = 10 - (d/1000000000000%10 + d/100000000000%10 * 3 + d/10000000000%10 + d/1000000000%10 * 3 + d/100000000%10 + d/10000000%10 * 3 + d/1000000%10 + d/100000%10 * 3 + d/10000%10 + d/1000%10 * 3 + d/100%10 + d/10%10 * 3) % 10;
            qDebug() << "cal_check_digit" << cal_check_digit;if (input_check_digit == cal_check_digit)
            {
                QStyledItemDelegate::setModelData(editor, model, index);
                return;
            }
            else
            {
                emit InvalidIsbn();
            }
        }
        if (line_edit->text().isEmpty())
            emit InvalidIsbn();

    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}
