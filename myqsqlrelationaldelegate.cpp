#include "myqsqlrelationaldelegate.h"
#include <category.h>
#include <status.h>

#include <QComboBox>
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QAbstractItemModel>

MyQSqlRelationalDelegate::MyQSqlRelationalDelegate(QObject *parent) : QSqlRelationalDelegate (parent)
{
}

QWidget * MyQSqlRelationalDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 4)
    {
        QComboBox *combobox = new QComboBox(parent);
        combobox->addItems(Category::AllCategoryStrings());
        QTimer::singleShot(0, combobox, &QComboBox::showPopup); // Queued connection
        (void) option;
        (void) index;
        return combobox;
    }
    if (index.column() == 5)
    {
        QComboBox *combobox = new QComboBox(parent);
        combobox->addItems(Status::AllStatusStrings());
        QTimer::singleShot(0, combobox, &QComboBox::showPopup); // Queued connection
        (void) option;
        (void) index;
        return combobox;
    }
}
/*
void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}
*/
void MyQSqlRelationalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *combobox = static_cast<QComboBox *>(editor);
    if (index.column() == 4)
        combobox->setCurrentIndex(Category::StringToEnum(index.data().toString()));
    if (index.column() == 5)
        combobox->setCurrentIndex(Status::StringToEnum(index.data().toString()));
    connect(combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(CommitAndClose()));
}

void MyQSqlRelationalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *combobox = static_cast<QComboBox *>(editor);
    model->setData(index, combobox->currentIndex());    // "Convert" string to enum here instead of reimplementing setData() of the Model // Unused too after inheriting from QSqlRelationalDelegate
    //model->setData(index, combobox->currentText());   // Unused
}

QSize MyQSqlRelationalDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
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
            hint = hint.expandedTo(qApp->style()->sizeFromContents(QStyle::CT_ComboBox, &comboOption, QSize(fm.width(value), hint.height())));
        }
    }
    if (index.column() == 5)
    {
        Q_FOREACH (const auto& value, Status::AllStatusStrings())
        {
            hint = hint.expandedTo(qApp->style()->sizeFromContents(QStyle::CT_ComboBox, &comboOption, QSize(fm.width(value), hint.height())));
        }
    }


    return hint;
}

void MyQSqlRelationalDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    (void) index;
}


void MyQSqlRelationalDelegate::CommitAndClose()
{
    QComboBox *editor = qobject_cast<QComboBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

