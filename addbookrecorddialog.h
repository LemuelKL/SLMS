#ifndef ADDBOOKRECORDDIALOG_H
#define ADDBOOKRECORDDIALOG_H

#include <QDialog>

namespace Ui {
class AddBookRecordDialog;
}

class AddBookRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookRecordDialog(QWidget *parent = nullptr);
    ~AddBookRecordDialog();

public slots:
    void HandleInvalidIsbn13();
    void HandleIntermidateIsbn13();
    void HandleValidIsbn13();
signals:
    void Submitted(QString isbn13, QString title, QString author, int category, int status, int amount);

private slots:
    void on_pushButton_submit_clicked();

private:
    Ui::AddBookRecordDialog *ui;
};

#endif // ADDBOOKRECORDDIALOG_H
