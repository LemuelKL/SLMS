/********************************************************************************
** Form generated from reading UI file 'lineeditpopupdialoag.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEEDITPOPUPDIALOAG_H
#define UI_LINEEDITPOPUPDIALOAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_LineEditPopupDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;

    void setupUi(QDialog *LineEditPopupDialog)
    {
        if (LineEditPopupDialog->objectName().isEmpty())
            LineEditPopupDialog->setObjectName(QString::fromUtf8("LineEditPopupDialog"));
        LineEditPopupDialog->resize(211, 80);
        buttonBox = new QDialogButtonBox(LineEditPopupDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 40, 191, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        lineEdit = new QLineEdit(LineEditPopupDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 191, 20));

        retranslateUi(LineEditPopupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LineEditPopupDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LineEditPopupDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LineEditPopupDialog);
    } // setupUi

    void retranslateUi(QDialog *LineEditPopupDialog)
    {
        LineEditPopupDialog->setWindowTitle(QCoreApplication::translate("LineEditPopupDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LineEditPopupDialog: public Ui_LineEditPopupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEEDITPOPUPDIALOAG_H
