/********************************************************************************
** Form generated from reading UI file 'personidpopupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONIDPOPUPDIALOG_H
#define UI_PERSONIDPOPUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_PersonIdPopUpDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_personId;

    void setupUi(QDialog *PersonIdPopUpDialog)
    {
        if (PersonIdPopUpDialog->objectName().isEmpty())
            PersonIdPopUpDialog->setObjectName(QString::fromUtf8("PersonIdPopUpDialog"));
        PersonIdPopUpDialog->resize(209, 80);
        buttonBox = new QDialogButtonBox(PersonIdPopUpDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 40, 191, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        lineEdit_personId = new QLineEdit(PersonIdPopUpDialog);
        lineEdit_personId->setObjectName(QString::fromUtf8("lineEdit_personId"));
        lineEdit_personId->setGeometry(QRect(10, 10, 191, 20));

        retranslateUi(PersonIdPopUpDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PersonIdPopUpDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PersonIdPopUpDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PersonIdPopUpDialog);
    } // setupUi

    void retranslateUi(QDialog *PersonIdPopUpDialog)
    {
        PersonIdPopUpDialog->setWindowTitle(QCoreApplication::translate("PersonIdPopUpDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PersonIdPopUpDialog: public Ui_PersonIdPopUpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONIDPOPUPDIALOG_H
