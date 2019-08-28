#include "status.h"

Status::Status()
{

}

QStringList Status::internal_holder_ =
{
    "Unknown",
    "Available",
    "On loan",
    "Lost"
};

int Status::count_ = internal_holder_.length();

QStringList Status::AllStatusStrings()
{
    return internal_holder_;
}

QString Status::EnumToString(Status::ENUM en)
{
    return internal_holder_.at(en);
}

QString Status::EnumToString(int en)
{
    return internal_holder_.at(en);
}

Status::ENUM Status::StringToEnum(QString str)
{
    for (int ret = 0; ret < internal_holder_.size(); ret++)
    {
        if (internal_holder_.at(ret) == str)
            return static_cast<ENUM>(ret);
    }
    return Status::ENUM::UNKNOWN;
}

