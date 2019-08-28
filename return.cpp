#include "return.h"

Return::Return()
{

}

QStringList Return::internal_holder_ =
{
    "Unkown",
    "No",
    "Yes"
};

int Return::count_ = internal_holder_.length();

QStringList Return::AllStatusStrings()
{
    return internal_holder_;
}

QString Return::EnumToString(Return::ENUM en)
{
    return internal_holder_.at(en);
}

QString Return::EnumToString(int en)
{
    return internal_holder_.at(en);
}

Return::ENUM Return::StringToEnum(QString str)
{
    for (int ret = 0; ret < internal_holder_.size(); ret++)
    {
        if (internal_holder_.at(ret) == str)
            return static_cast<ENUM>(ret);
    }
    return Return::ENUM::UNKNOWN;
}
