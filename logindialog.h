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

    void InitializeDatabase();
    
signals:
    void LoginGuest(QString username);
    void LoginStudent(QString username);
    void LoginTeacher(QString username);
    void LoginAdmin(QString username);

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::LoginDialog *ui;

    void HashBySha512(const char *, char *);
    bool IsEmptyDB();

    bool empty_db_;
};

#endif // LOGINDIALOG_H
