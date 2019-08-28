#include "isbn13validator.h"

#include <QDebug>

Isbn13Validator::Isbn13Validator(QObject *parent) : QRegExpValidator (parent)
{

}

QValidator::State Isbn13Validator::validate(QString &input, int &pos) const
{
    QRegExp rx("(?=.{13}$)97(?:8|9)\\d{1,10}\\1$");
    QRegExpValidator v(rx, 0);

    if (v.validate(input, pos) == Invalid)
    {
        emit InvalidIsbn13();
    }
    else
    {
        int d = std::atoi(input.toStdString().c_str());
        int input_check_digit = d % 10;

        int cal_check_digit = 10 - (d%10000000000000 + d%1000000000000 * 3 + d%100000000000 + d%10000000000 * 3 + d%1000000000 + d%100000000 * 3 + d%10000000 + d%1000000 * 3 + d%100000 + d%10000 * 3 + d%1000 + d%100 * 3) % 10;
        if (input_check_digit == cal_check_digit)
        {
            emit ValidIsbn13();
        }
        else
        {
            emit InvalidIsbn13();
        }
    }
    if (input.isEmpty())
        emit InvalidIsbn13();
    return Acceptable;
}
