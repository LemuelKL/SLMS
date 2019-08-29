#ifndef EDITBOOKRECORDDIALOG_H
#define EDITBOOKRECORDDIALOG_H

#include <QDialog>
#include <QObject>

namespace Ui {
class EditBookRecordDialog;
}

class EditBookRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditBookRecordDialog(QWidget *parent = nullptr);
    ~EditBookRecordDialog();

    void SetId(int id);
    void SetIsbn13(QString isbn13);
    void SetTitle(QString title);
    void SetAuthor(QString author);
    void SetCategory(int category);
    void SetStatus(int status);

    void PopulateWidgets();

public slots:
    void HandleValidIsbn13();
signals:
    void Submitted(QString isbn13, QString title, QString author, int category, int status, int id);

private slots:
    void on_pushButton_submit_clicked();

    void HandleInvalidIsbn13();

    void HandleIntermidateIsbn13();

private:
    Ui::EditBookRecordDialog *ui;

    int id_;
    QString isbn13_;
    QString title_;
    QString author_;
    int category_;
    int status_;
};

#endif // EDITBOOKRECORDDIALOG_H
