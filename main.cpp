#include "mainwindow.h"
#include <logindialog.h>
#include <adminpanel.h>

#include <QApplication>
#include <QObject>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog l;
    AdminPanel ap;
    QObject::connect(&l, SIGNAL(LoginAdmin(QString)), &ap, SLOT(ReceiveLogin(QString)));
    l.show();

    return a.exec();
}
