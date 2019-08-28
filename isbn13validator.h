#ifndef ISBN13VALIDATOR_H
#define ISBN13VALIDATOR_H

#include <QObject>
#include <QValidator>

class Isbn13Validator : public QRegExpValidator
{
    Q_OBJECT
public:
    Isbn13Validator(QObject *parent = 0);

    virtual State validate( QString & input, int & pos ) const;

signals:
    void InvalidIsbn13() const;
    void IntermediateIsbn13() const;
    void ValidIsbn13() const;
};

#endif // ISBN13VALIDATOR_H
