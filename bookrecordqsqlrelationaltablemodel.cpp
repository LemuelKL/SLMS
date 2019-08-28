#include "bookrecordqsqlrelationaltablemodel.h"
#include <category.h>
#include <status.h>
#include <adminpanel.h>

#include <QtDebug>
#include <QTimer>
#include <QLabel>
#include <QApplication>
#include <QDir>

BookRecordQSqlRelationalTableModel::BookRecordQSqlRelationalTableModel(QObject * parent, QSqlDatabase db = QSqlDatabase()) : QSqlRelationalTableModel(parent, db)
{

}

QVariant BookRecordQSqlRelationalTableModel::data(const QModelIndex & index, int role = Qt::DisplayRole) const
{
    if (role == Qt::ToolTipRole && index.column() == AdminPanel::TITLE)
    {
        QModelIndex index_isbn13 = index.sibling(index.row(), AdminPanel::ISBN13);
        QVariant value = QSqlRelationalTableModel::data(index_isbn13, Qt::DisplayRole);
        QString img_dir_path = QCoreApplication::applicationDirPath() + QDir::separator() + "book_cover_pics" + QDir::separator();
        QString arg;
        QString arg_png = img_dir_path+value.toString()+".png";
        QString arg_jpg = img_dir_path+value.toString()+".jpg";
        if (QFileInfo::exists(arg_png) && QFileInfo(arg_png).isFile())
            arg = arg_png;
        if (QFileInfo::exists(arg_jpg) && QFileInfo(arg_jpg).isFile())
            arg = arg_jpg;
        return QString("<img src='%1'>").arg(arg);
    }
    if (role == Qt::DecorationRole && index.column() == AdminPanel::ID)
    {
        QModelIndex index_status = index.sibling(index.row(), AdminPanel::STATUS);
        QVariant value = QSqlRelationalTableModel::data(index_status, Qt::DisplayRole);
        QPixmap book_icon;
        if (Status::StringToEnum(value.toString()) == Status::UNKNOWN)
            book_icon = QPixmap(":/book_statuses/release/resources/images/book_statuses/book_unknown.png");
        if (Status::StringToEnum(value.toString()) == Status::AVAILABLE)
            book_icon = QPixmap(":/book_statuses/release/resources/images/book_statuses/book_available.png");
        if (Status::StringToEnum(value.toString()) == Status::ON_LOAN)
            book_icon = QPixmap(":/book_statuses/release/resources/images/book_statuses/book_onLoan.png");
        if (Status::StringToEnum(value.toString()) == Status::LOST)
            book_icon = QPixmap(":/book_statuses/release/resources/images/book_statuses/book_lost.png");

        book_icon = book_icon.scaled(32, 32, Qt::KeepAspectRatio);
        return book_icon;
    }
    return QSqlRelationalTableModel::data(index, role);
}


bool BookRecordQSqlRelationalTableModel::setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole)
{
    if (value.toString().size() < 1 && role == Qt::EditRole)
    {
        qDebug() << "setData - Empty Data Detected At Index Col:" << index.column();
        QVariant new_value = QVariant(QString("UNCONFIGURED UNKNOWN_COLUMN"));
        if (index.column() == AdminPanel::BookRecordTableViewColumns::ISBN13)
            new_value = QVariant(QString("UNCONFIGURED ISBN13"));
        if (index.column() == AdminPanel::BookRecordTableViewColumns::TITLE)
            new_value = QVariant(QString("UNCONFIGURED TITLE"));
        if (index.column() == AdminPanel::BookRecordTableViewColumns::AUTHOR)
            new_value = QVariant(QString("UNCONFIGURED AUTHOR"));
        if (index.column() == AdminPanel::BookRecordTableViewColumns::CATEGORY)
            new_value = QVariant(0);
        if (index.column() == AdminPanel::BookRecordTableViewColumns::STATUS)
            new_value = QVariant(0);
        emit DataIsEmpty(index);
        return QSqlRelationalTableModel::setData(index, new_value, role);
    }
    else
    {
        qDebug() << "setData - Data Passthrough:" << value.toString() << "Role:" << role;
        return QSqlRelationalTableModel::setData(index, value, role);
    }
}
