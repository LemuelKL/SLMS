#ifndef RETURN_H
#define RETURN_H

#include <QString>
#include <QStringList>

class Return
{
public:
    Return();

    enum ENUM
    {
        UNKNOWN = 0,
        NO = 1,
        YES = 2
    };

    static int count_;

    static QStringList AllStatusStrings();
    static QString EnumToString(Return::ENUM);
    static QString EnumToString(int);
    static Return::ENUM StringToEnum(QString str);

private:
    static QStringList internal_holder_;
};

#endif // RETURN_H
