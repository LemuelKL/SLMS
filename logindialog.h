#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

signals:
    void LoginAdmin(QString username);
    void LoginTeacher(QString username);
    void LoginStudent(QString username);
    void LoginGuest(QString username);

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::LoginDialog *ui;

    void ShowWarnPassMsg(QString title, QString text);
    void HashBySha512(const char *, char *);
    bool IsEmptyDB();

    bool _empty_db;
};

#endif // LOGINDIALOG_H
