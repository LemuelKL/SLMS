/********************************************************************************
** Form generated from reading UI file 'addbookrecorddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDBOOKRECORDDIALOG_H
#define UI_ADDBOOKRECORDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddBookRecordDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit_isbn13;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_title;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_author;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox_category;
    QComboBox *comboBox_status;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpinBox *spinBox_amount;
    QPushButton *pushButton_submit;

    void setupUi(QDialog *AddBookRecordDialog)
    {
        if (AddBookRecordDialog->objectName().isEmpty())
            AddBookRecordDialog->setObjectName(QString::fromUtf8("AddBookRecordDialog"));
        AddBookRecordDialog->resize(288, 184);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddBookRecordDialog->sizePolicy().hasHeightForWidth());
        AddBookRecordDialog->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/remix_icons/resources/icons/file-add-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        AddBookRecordDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(AddBookRecordDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(AddBookRecordDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setMinimumSize(QSize(50, 0));
        label_4->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_isbn13 = new QLineEdit(AddBookRecordDialog);
        lineEdit_isbn13->setObjectName(QString::fromUtf8("lineEdit_isbn13"));

        horizontalLayout_2->addWidget(lineEdit_isbn13);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(AddBookRecordDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMinimumSize(QSize(50, 0));
        label_3->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_title = new QLineEdit(AddBookRecordDialog);
        lineEdit_title->setObjectName(QString::fromUtf8("lineEdit_title"));

        horizontalLayout_3->addWidget(lineEdit_title);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(AddBookRecordDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(50, 0));
        label_2->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(label_2);

        lineEdit_author = new QLineEdit(AddBookRecordDialog);
        lineEdit_author->setObjectName(QString::fromUtf8("lineEdit_author"));

        horizontalLayout_4->addWidget(lineEdit_author);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        comboBox_category = new QComboBox(AddBookRecordDialog);
        comboBox_category->setObjectName(QString::fromUtf8("comboBox_category"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(5);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_category->sizePolicy().hasHeightForWidth());
        comboBox_category->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(comboBox_category);

        comboBox_status = new QComboBox(AddBookRecordDialog);
        comboBox_status->setObjectName(QString::fromUtf8("comboBox_status"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox_status->sizePolicy().hasHeightForWidth());
        comboBox_status->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(comboBox_status);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(AddBookRecordDialog);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(8);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        spinBox_amount = new QSpinBox(AddBookRecordDialog);
        spinBox_amount->setObjectName(QString::fromUtf8("spinBox_amount"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(spinBox_amount->sizePolicy().hasHeightForWidth());
        spinBox_amount->setSizePolicy(sizePolicy4);
        spinBox_amount->setMinimumSize(QSize(0, 0));
        spinBox_amount->setFont(font);

        horizontalLayout->addWidget(spinBox_amount);

        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 5);

        horizontalLayout_6->addLayout(horizontalLayout);

        pushButton_submit = new QPushButton(AddBookRecordDialog);
        pushButton_submit->setObjectName(QString::fromUtf8("pushButton_submit"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButton_submit->sizePolicy().hasHeightForWidth());
        pushButton_submit->setSizePolicy(sizePolicy5);
        pushButton_submit->setMinimumSize(QSize(0, 50));
        pushButton_submit->setFont(font);
        pushButton_submit->setIcon(icon);

        horizontalLayout_6->addWidget(pushButton_submit);

        horizontalLayout_6->setStretch(0, 5);
        horizontalLayout_6->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_6);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AddBookRecordDialog);

        QMetaObject::connectSlotsByName(AddBookRecordDialog);
    } // setupUi

    void retranslateUi(QDialog *AddBookRecordDialog)
    {
        AddBookRecordDialog->setWindowTitle(QCoreApplication::translate("AddBookRecordDialog", "Dialog", nullptr));
        label_4->setText(QCoreApplication::translate("AddBookRecordDialog", "ISBN13", nullptr));
        label_3->setText(QCoreApplication::translate("AddBookRecordDialog", "Title", nullptr));
        label_2->setText(QCoreApplication::translate("AddBookRecordDialog", "Author", nullptr));
        label->setText(QCoreApplication::translate("AddBookRecordDialog", "Amount:", nullptr));
        pushButton_submit->setText(QCoreApplication::translate("AddBookRecordDialog", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddBookRecordDialog: public Ui_AddBookRecordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDBOOKRECORDDIALOG_H
