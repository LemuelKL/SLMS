#include "isbn13validator.h"

#include <QDebug>

Isbn13Validator::Isbn13Validator(QObject *parent) : QRegExpValidator (parent)
{

}

QValidator::State Isbn13Validator::validate(QString &input, int &pos) const
{
    QRegExp rx("(?=.{13}$)97(?:8|9)\\d{1,10}");
    QRegExpValidator v(rx, 0);

    if (v.validate(input, pos) == Invalid)
    {
        emit InvalidIsbn13();
    }
    else
    {
        qDebug() << "Original input:" << input;
        long long int d = input.toLongLong();
        qDebug() << "input toInt:" << d;
        long long int input_check_digit = d/1%10;
        qDebug() << "input_check_digit" << input_check_digit;

        int cal_check_digit = 10 - (d/1000000000000%10 + d/100000000000%10 * 3 + d/10000000000%10 + d/1000000000%10 * 3 + d/100000000%10 + d/10000000%10 * 3 + d/1000000%10 + d/100000%10 * 3 + d/10000%10 + d/1000%10 * 3 + d/100%10 + d/10%10 * 3) % 10;
        qDebug() << "cal_check_digit" << cal_check_digit;
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
