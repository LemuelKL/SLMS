#ifndef HEADERMODEL_H
#define HEADERMODEL_H

#include <QIdentityProxyModel>
#include <QIcon>

class HeaderModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit HeaderModel(QObject * parent = nullptr)
        : QIdentityProxyModel(parent)
    { }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if(orientation == Qt::Horizontal)
        {
            if(role == Qt::DisplayRole)
                switch(section)
                {
                case 0: return "ID";
                case 1: return "ISBN13";
                case 2: return "Book Title";
                case 3: return "Author";
                case 4: return "Category";
                default:
                    return QString("Column %1").arg(section + 1);
                }
        }
        else if(orientation == Qt::Vertical)
        {
            if(role == Qt::DecorationRole)
                return QIcon("book.png");
        }

        return QVariant();
    }
};

#endif // HEADERMODEL_H
