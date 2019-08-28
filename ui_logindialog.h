/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QGroupBox *groupBox;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_login;
    QLineEdit *lineEdit_username;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginDialog->sizePolicy().hasHeightForWidth());
        LoginDialog->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/remix_icons/release/resources/icons/login-circle-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        LoginDialog->setWindowIcon(icon);
        LoginDialog->setWindowOpacity(1.000000000000000);
        groupBox = new QGroupBox(LoginDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 30, 321, 251));
        QFont font;
        font.setPointSize(23);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        lineEdit_password = new QLineEdit(groupBox);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(10, 130, 301, 31));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setWeight(50);
        lineEdit_password->setFont(font1);
        lineEdit_password->setToolTipDuration(3000);
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setCursorPosition(0);
        lineEdit_password->setClearButtonEnabled(true);
        pushButton_login = new QPushButton(groupBox);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(110, 180, 101, 31));
        QFont font2;
        font2.setPointSize(11);
        pushButton_login->setFont(font2);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/remix_icons/release/resources/icons/key-2-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_login->setIcon(icon1);
        lineEdit_username = new QLineEdit(groupBox);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setGeometry(QRect(10, 90, 301, 31));
        lineEdit_username->setFont(font1);
        lineEdit_username->setToolTipDuration(3000);
        lineEdit_username->setClearButtonEnabled(true);
        QWidget::setTabOrder(lineEdit_username, lineEdit_password);
        QWidget::setTabOrder(lineEdit_password, pushButton_login);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Login Window", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LoginDialog", "User Login", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_password->setToolTip(QCoreApplication::translate("LoginDialog", "Enter your password here.", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_password->setText(QString());
        pushButton_login->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_username->setToolTip(QCoreApplication::translate("LoginDialog", "Enter your username here.", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_username->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
