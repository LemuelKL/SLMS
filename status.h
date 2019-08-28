#ifndef STATUS_H
#define STATUS_H

#include <QString>
#include <QStringList>

class Status
{
public:
    Status();

    enum ENUM
    {
        UNKNOWN = 0,
        AVAILABLE = 1,
        ON_LOAN = 2,
        LOST = 3
    };

    static int count_;

    static QStringList AllStatusStrings();
    static QString EnumToString(Status::ENUM);
    static QString EnumToString(int);
    static Status::ENUM StringToEnum(QString str);

private:
    static QStringList internal_holder_;
};

#endif // STATUS_H
