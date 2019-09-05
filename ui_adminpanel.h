/********************************************************************************
** Form generated from reading UI file 'adminpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPANEL_H
#define UI_ADMINPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminPanel
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QFrame *frame_main;
    QHBoxLayout *horizontalLayout_14;
    QFrame *frame_views;
    QHBoxLayout *horizontalLayout_15;
    QTabWidget *tabWidget;
    QWidget *tab_bookRecords_3;
    QHBoxLayout *horizontalLayout_19;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_numBookRecords;
    QLabel *label_numBookRecords_var;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_readOnly;
    QTableView *tableView_bookRecords;
    QWidget *tab_loanRecords_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_numLoanRecords;
    QLabel *label_numOverdueLoanRecords_var;
    QLabel *label_numLoanRecords_var;
    QLabel *label_numOverdueLoanRecords;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_5;
    QCheckBox *checkBox_highlight_onLoan;
    QCheckBox *checkBox_filter_loanRecord_onLoan;
    QCheckBox *checkBox_highlight_overdue;
    QCheckBox *checkBox_filter_loanRecord_overdue;
    QPushButton *pushButton_reloadLoans;
    QTableView *tableView_loanRecords;
    QFrame *frame_actions;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_today;
    QComboBox *comboBox_qDateFormat;
    QHBoxLayout *horizontalLayout_27;
    QGroupBox *groupBox_recordManipulation;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_22;
    QPushButton *pushButton_addBook;
    QPushButton *pushButton_deleteRecords;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_editBook;
    QPushButton *pushButton_reloadBook;
    QGroupBox *groupBox_loanAndReturn;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_3;
    QPushButton *pushButton_editPersonId;
    QLineEdit *lineEdit_personId;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_2;
    QPushButton *pushButton_editBookId;
    QLineEdit *lineEdit_bookId;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_4;
    QComboBox *comboBox_nDays;
    QHBoxLayout *horizontalLayout_26;
    QPushButton *pushButton_loan;
    QPushButton *pushButton_return;
    QGroupBox *groupBox_searching;
    QHBoxLayout *horizontalLayout_20;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_11;
    QFrame *frame_bookRecords_columnFilters;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkBox_filter_id;
    QCheckBox *checkBox_filter_isbn13;
    QCheckBox *checkBox_filter_title;
    QCheckBox *checkBox_filter_author;
    QCheckBox *checkBox_filter_category;
    QCheckBox *checkBox_filter_status;
    QFrame *frame_loanRecords_columnFilters;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox_filter_loanRecord_recordId;
    QCheckBox *checkBox_filter_loanRecord_bookId;
    QCheckBox *checkBox_filter_loanRecord_personId;
    QCheckBox *checkBox_filter_loanRecord_loanDate;
    QCheckBox *checkBox_filter_loanRecord_dueDate;
    QCheckBox *checkBox_filter_loanRecord_hvReturned;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_updateView;
    QCheckBox *checkBox_filter_caseSensitive;
    QCheckBox *checkBox_searchInViewOnly;
    QCheckBox *checkBox_updateViewAsIType;
    QGroupBox *groupBox_sqlMassAction;
    QHBoxLayout *horizontalLayout_12;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminPanel)
    {
        if (AdminPanel->objectName().isEmpty())
            AdminPanel->setObjectName(QString::fromUtf8("AdminPanel"));
        AdminPanel->resize(1130, 662);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AdminPanel->sizePolicy().hasHeightForWidth());
        AdminPanel->setSizePolicy(sizePolicy);
        AdminPanel->setMinimumSize(QSize(1130, 662));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/remix_icons/resources/icons/admin-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        AdminPanel->setWindowIcon(icon);
        centralwidget = new QWidget(AdminPanel);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        frame_main = new QFrame(centralwidget);
        frame_main->setObjectName(QString::fromUtf8("frame_main"));
        frame_main->setFrameShape(QFrame::StyledPanel);
        frame_main->setFrameShadow(QFrame::Raised);
        horizontalLayout_14 = new QHBoxLayout(frame_main);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(-1, 9, -1, -1);
        frame_views = new QFrame(frame_main);
        frame_views->setObjectName(QString::fromUtf8("frame_views"));
        sizePolicy.setHeightForWidth(frame_views->sizePolicy().hasHeightForWidth());
        frame_views->setSizePolicy(sizePolicy);
        frame_views->setMinimumSize(QSize(693, 580));
        frame_views->setFrameShape(QFrame::StyledPanel);
        frame_views->setFrameShadow(QFrame::Raised);
        horizontalLayout_15 = new QHBoxLayout(frame_views);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(-1, 9, -1, -1);
        tabWidget = new QTabWidget(frame_views);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(670, 563));
        tab_bookRecords_3 = new QWidget();
        tab_bookRecords_3->setObjectName(QString::fromUtf8("tab_bookRecords_3"));
        horizontalLayout_19 = new QHBoxLayout(tab_bookRecords_3);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_numBookRecords = new QLabel(tab_bookRecords_3);
        label_numBookRecords->setObjectName(QString::fromUtf8("label_numBookRecords"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_numBookRecords->sizePolicy().hasHeightForWidth());
        label_numBookRecords->setSizePolicy(sizePolicy1);
        label_numBookRecords->setMinimumSize(QSize(0, 25));

        horizontalLayout_16->addWidget(label_numBookRecords);

        label_numBookRecords_var = new QLabel(tab_bookRecords_3);
        label_numBookRecords_var->setObjectName(QString::fromUtf8("label_numBookRecords_var"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_numBookRecords_var->sizePolicy().hasHeightForWidth());
        label_numBookRecords_var->setSizePolicy(sizePolicy2);
        label_numBookRecords_var->setMinimumSize(QSize(20, 25));

        horizontalLayout_16->addWidget(label_numBookRecords_var);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_2);

        checkBox_readOnly = new QCheckBox(tab_bookRecords_3);
        checkBox_readOnly->setObjectName(QString::fromUtf8("checkBox_readOnly"));
        checkBox_readOnly->setChecked(true);

        horizontalLayout_16->addWidget(checkBox_readOnly);


        verticalLayout_6->addLayout(horizontalLayout_16);

        tableView_bookRecords = new QTableView(tab_bookRecords_3);
        tableView_bookRecords->setObjectName(QString::fromUtf8("tableView_bookRecords"));
        sizePolicy.setHeightForWidth(tableView_bookRecords->sizePolicy().hasHeightForWidth());
        tableView_bookRecords->setSizePolicy(sizePolicy);
        tableView_bookRecords->setMinimumSize(QSize(650, 470));
        tableView_bookRecords->setAlternatingRowColors(false);
        tableView_bookRecords->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView_bookRecords->setIconSize(QSize(30, 30));
        tableView_bookRecords->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableView_bookRecords->setSortingEnabled(true);
        tableView_bookRecords->verticalHeader()->setVisible(false);

        verticalLayout_6->addWidget(tableView_bookRecords);


        horizontalLayout_19->addLayout(verticalLayout_6);

        tabWidget->addTab(tab_bookRecords_3, QString());
        tab_loanRecords_3 = new QWidget();
        tab_loanRecords_3->setObjectName(QString::fromUtf8("tab_loanRecords_3"));
        sizePolicy.setHeightForWidth(tab_loanRecords_3->sizePolicy().hasHeightForWidth());
        tab_loanRecords_3->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(tab_loanRecords_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_numLoanRecords = new QLabel(tab_loanRecords_3);
        label_numLoanRecords->setObjectName(QString::fromUtf8("label_numLoanRecords"));

        gridLayout->addWidget(label_numLoanRecords, 0, 0, 1, 1);

        label_numOverdueLoanRecords_var = new QLabel(tab_loanRecords_3);
        label_numOverdueLoanRecords_var->setObjectName(QString::fromUtf8("label_numOverdueLoanRecords_var"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_numOverdueLoanRecords_var->sizePolicy().hasHeightForWidth());
        label_numOverdueLoanRecords_var->setSizePolicy(sizePolicy3);
        label_numOverdueLoanRecords_var->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(label_numOverdueLoanRecords_var, 1, 1, 1, 1);

        label_numLoanRecords_var = new QLabel(tab_loanRecords_3);
        label_numLoanRecords_var->setObjectName(QString::fromUtf8("label_numLoanRecords_var"));
        sizePolicy3.setHeightForWidth(label_numLoanRecords_var->sizePolicy().hasHeightForWidth());
        label_numLoanRecords_var->setSizePolicy(sizePolicy3);
        label_numLoanRecords_var->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(label_numLoanRecords_var, 0, 1, 1, 1);

        label_numOverdueLoanRecords = new QLabel(tab_loanRecords_3);
        label_numOverdueLoanRecords->setObjectName(QString::fromUtf8("label_numOverdueLoanRecords"));

        gridLayout->addWidget(label_numOverdueLoanRecords, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        checkBox_highlight_onLoan = new QCheckBox(tab_loanRecords_3);
        checkBox_highlight_onLoan->setObjectName(QString::fromUtf8("checkBox_highlight_onLoan"));
        sizePolicy2.setHeightForWidth(checkBox_highlight_onLoan->sizePolicy().hasHeightForWidth());
        checkBox_highlight_onLoan->setSizePolicy(sizePolicy2);
        checkBox_highlight_onLoan->setMinimumSize(QSize(160, 0));

        gridLayout_5->addWidget(checkBox_highlight_onLoan, 0, 0, 1, 1);

        checkBox_filter_loanRecord_onLoan = new QCheckBox(tab_loanRecords_3);
        checkBox_filter_loanRecord_onLoan->setObjectName(QString::fromUtf8("checkBox_filter_loanRecord_onLoan"));
        sizePolicy2.setHeightForWidth(checkBox_filter_loanRecord_onLoan->sizePolicy().hasHeightForWidth());
        checkBox_filter_loanRecord_onLoan->setSizePolicy(sizePolicy2);
        checkBox_filter_loanRecord_onLoan->setMinimumSize(QSize(160, 0));

        gridLayout_5->addWidget(checkBox_filter_loanRecord_onLoan, 0, 1, 1, 1);

        checkBox_highlight_overdue = new QCheckBox(tab_loanRecords_3);
        checkBox_highlight_overdue->setObjectName(QString::fromUtf8("checkBox_highlight_overdue"));
        sizePolicy2.setHeightForWidth(checkBox_highlight_overdue->sizePolicy().hasHeightForWidth());
        checkBox_highlight_overdue->setSizePolicy(sizePolicy2);
        checkBox_highlight_overdue->setMinimumSize(QSize(160, 0));

        gridLayout_5->addWidget(checkBox_highlight_overdue, 1, 0, 1, 1);

        checkBox_filter_loanRecord_overdue = new QCheckBox(tab_loanRecords_3);
        checkBox_filter_loanRecord_overdue->setObjectName(QString::fromUtf8("checkBox_filter_loanRecord_overdue"));
        sizePolicy2.setHeightForWidth(checkBox_filter_loanRecord_overdue->sizePolicy().hasHeightForWidth());
        checkBox_filter_loanRecord_overdue->setSizePolicy(sizePolicy2);
        checkBox_filter_loanRecord_overdue->setMinimumSize(QSize(160, 0));

        gridLayout_5->addWidget(checkBox_filter_loanRecord_overdue, 1, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_5);

        pushButton_reloadLoans = new QPushButton(tab_loanRecords_3);
        pushButton_reloadLoans->setObjectName(QString::fromUtf8("pushButton_reloadLoans"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_reloadLoans->sizePolicy().hasHeightForWidth());
        pushButton_reloadLoans->setSizePolicy(sizePolicy4);
        pushButton_reloadLoans->setMinimumSize(QSize(0, 50));
        pushButton_reloadLoans->setMaximumSize(QSize(130, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/remix_icons/resources/icons/refresh-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_reloadLoans->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_reloadLoans);

        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        tableView_loanRecords = new QTableView(tab_loanRecords_3);
        tableView_loanRecords->setObjectName(QString::fromUtf8("tableView_loanRecords"));
        sizePolicy.setHeightForWidth(tableView_loanRecords->sizePolicy().hasHeightForWidth());
        tableView_loanRecords->setSizePolicy(sizePolicy);
        tableView_loanRecords->setMinimumSize(QSize(650, 470));
        tableView_loanRecords->setSortingEnabled(true);
        tableView_loanRecords->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView_loanRecords);


        horizontalLayout_2->addLayout(verticalLayout);

        tabWidget->addTab(tab_loanRecords_3, QString());

        horizontalLayout_15->addWidget(tabWidget);


        horizontalLayout_14->addWidget(frame_views);

        frame_actions = new QFrame(frame_main);
        frame_actions->setObjectName(QString::fromUtf8("frame_actions"));
        frame_actions->setEnabled(true);
        sizePolicy2.setHeightForWidth(frame_actions->sizePolicy().hasHeightForWidth());
        frame_actions->setSizePolicy(sizePolicy2);
        frame_actions->setMinimumSize(QSize(390, 580));
        frame_actions->setMaximumSize(QSize(390, 580));
        frame_actions->setFrameShape(QFrame::StyledPanel);
        frame_actions->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_actions);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_today = new QLabel(frame_actions);
        label_today->setObjectName(QString::fromUtf8("label_today"));
        sizePolicy4.setHeightForWidth(label_today->sizePolicy().hasHeightForWidth());
        label_today->setSizePolicy(sizePolicy4);
        label_today->setMinimumSize(QSize(150, 20));

        horizontalLayout_3->addWidget(label_today);

        comboBox_qDateFormat = new QComboBox(frame_actions);
        comboBox_qDateFormat->addItem(QString());
        comboBox_qDateFormat->addItem(QString());
        comboBox_qDateFormat->addItem(QString());
        comboBox_qDateFormat->addItem(QString());
        comboBox_qDateFormat->addItem(QString());
        comboBox_qDateFormat->addItem(QString());
        comboBox_qDateFormat->addItem(QString());
        comboBox_qDateFormat->addItem(QString());
        comboBox_qDateFormat->setObjectName(QString::fromUtf8("comboBox_qDateFormat"));
        sizePolicy2.setHeightForWidth(comboBox_qDateFormat->sizePolicy().hasHeightForWidth());
        comboBox_qDateFormat->setSizePolicy(sizePolicy2);
        comboBox_qDateFormat->setMinimumSize(QSize(80, 0));
        comboBox_qDateFormat->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(comboBox_qDateFormat);


        verticalLayout_7->addLayout(horizontalLayout_3);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        groupBox_recordManipulation = new QGroupBox(frame_actions);
        groupBox_recordManipulation->setObjectName(QString::fromUtf8("groupBox_recordManipulation"));
        sizePolicy2.setHeightForWidth(groupBox_recordManipulation->sizePolicy().hasHeightForWidth());
        groupBox_recordManipulation->setSizePolicy(sizePolicy2);
        groupBox_recordManipulation->setMinimumSize(QSize(220, 230));
        groupBox_recordManipulation->setMaximumSize(QSize(220, 230));
        gridLayout_3 = new QGridLayout(groupBox_recordManipulation);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        pushButton_addBook = new QPushButton(groupBox_recordManipulation);
        pushButton_addBook->setObjectName(QString::fromUtf8("pushButton_addBook"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButton_addBook->sizePolicy().hasHeightForWidth());
        pushButton_addBook->setSizePolicy(sizePolicy5);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/remix_icons/resources/icons/file-add-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_addBook->setIcon(icon2);

        horizontalLayout_22->addWidget(pushButton_addBook);

        pushButton_deleteRecords = new QPushButton(groupBox_recordManipulation);
        pushButton_deleteRecords->setObjectName(QString::fromUtf8("pushButton_deleteRecords"));
        sizePolicy5.setHeightForWidth(pushButton_deleteRecords->sizePolicy().hasHeightForWidth());
        pushButton_deleteRecords->setSizePolicy(sizePolicy5);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/remix_icons/resources/icons/delete-bin-2-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_deleteRecords->setIcon(icon3);

        horizontalLayout_22->addWidget(pushButton_deleteRecords);


        verticalLayout_10->addLayout(horizontalLayout_22);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        pushButton_editBook = new QPushButton(groupBox_recordManipulation);
        pushButton_editBook->setObjectName(QString::fromUtf8("pushButton_editBook"));
        sizePolicy5.setHeightForWidth(pushButton_editBook->sizePolicy().hasHeightForWidth());
        pushButton_editBook->setSizePolicy(sizePolicy5);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/remix_icons/resources/icons/file-edit-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_editBook->setIcon(icon4);

        horizontalLayout_10->addWidget(pushButton_editBook);

        pushButton_reloadBook = new QPushButton(groupBox_recordManipulation);
        pushButton_reloadBook->setObjectName(QString::fromUtf8("pushButton_reloadBook"));
        sizePolicy5.setHeightForWidth(pushButton_reloadBook->sizePolicy().hasHeightForWidth());
        pushButton_reloadBook->setSizePolicy(sizePolicy5);
        pushButton_reloadBook->setMinimumSize(QSize(0, 50));
        pushButton_reloadBook->setIcon(icon1);

        horizontalLayout_10->addWidget(pushButton_reloadBook);


        verticalLayout_10->addLayout(horizontalLayout_10);


        gridLayout_3->addLayout(verticalLayout_10, 0, 0, 1, 1);


        horizontalLayout_27->addWidget(groupBox_recordManipulation);

        groupBox_loanAndReturn = new QGroupBox(frame_actions);
        groupBox_loanAndReturn->setObjectName(QString::fromUtf8("groupBox_loanAndReturn"));
        sizePolicy2.setHeightForWidth(groupBox_loanAndReturn->sizePolicy().hasHeightForWidth());
        groupBox_loanAndReturn->setSizePolicy(sizePolicy2);
        groupBox_loanAndReturn->setMinimumSize(QSize(140, 230));
        groupBox_loanAndReturn->setMaximumSize(QSize(140, 230));
        gridLayout_2 = new QGridLayout(groupBox_loanAndReturn);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_3 = new QLabel(groupBox_loanAndReturn);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_23->addWidget(label_3);

        pushButton_editPersonId = new QPushButton(groupBox_loanAndReturn);
        pushButton_editPersonId->setObjectName(QString::fromUtf8("pushButton_editPersonId"));
        sizePolicy2.setHeightForWidth(pushButton_editPersonId->sizePolicy().hasHeightForWidth());
        pushButton_editPersonId->setSizePolicy(sizePolicy2);
        pushButton_editPersonId->setMaximumSize(QSize(57, 16777215));

        horizontalLayout_23->addWidget(pushButton_editPersonId);


        verticalLayout_11->addLayout(horizontalLayout_23);

        lineEdit_personId = new QLineEdit(groupBox_loanAndReturn);
        lineEdit_personId->setObjectName(QString::fromUtf8("lineEdit_personId"));
        lineEdit_personId->setEnabled(true);
        lineEdit_personId->setToolTipDuration(3000);
        lineEdit_personId->setReadOnly(true);
        lineEdit_personId->setClearButtonEnabled(false);

        verticalLayout_11->addWidget(lineEdit_personId);


        verticalLayout_14->addLayout(verticalLayout_11);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_2 = new QLabel(groupBox_loanAndReturn);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_24->addWidget(label_2);

        pushButton_editBookId = new QPushButton(groupBox_loanAndReturn);
        pushButton_editBookId->setObjectName(QString::fromUtf8("pushButton_editBookId"));
        sizePolicy2.setHeightForWidth(pushButton_editBookId->sizePolicy().hasHeightForWidth());
        pushButton_editBookId->setSizePolicy(sizePolicy2);
        pushButton_editBookId->setMaximumSize(QSize(57, 16777215));

        horizontalLayout_24->addWidget(pushButton_editBookId);


        verticalLayout_12->addLayout(horizontalLayout_24);

        lineEdit_bookId = new QLineEdit(groupBox_loanAndReturn);
        lineEdit_bookId->setObjectName(QString::fromUtf8("lineEdit_bookId"));
        lineEdit_bookId->setToolTipDuration(3000);
        lineEdit_bookId->setReadOnly(true);

        verticalLayout_12->addWidget(lineEdit_bookId);


        verticalLayout_14->addLayout(verticalLayout_12);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_4 = new QLabel(groupBox_loanAndReturn);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_25->addWidget(label_4);

        comboBox_nDays = new QComboBox(groupBox_loanAndReturn);
        comboBox_nDays->addItem(QString());
        comboBox_nDays->addItem(QString());
        comboBox_nDays->addItem(QString());
        comboBox_nDays->addItem(QString());
        comboBox_nDays->addItem(QString());
        comboBox_nDays->setObjectName(QString::fromUtf8("comboBox_nDays"));

        horizontalLayout_25->addWidget(comboBox_nDays);


        verticalLayout_13->addLayout(horizontalLayout_25);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        pushButton_loan = new QPushButton(groupBox_loanAndReturn);
        pushButton_loan->setObjectName(QString::fromUtf8("pushButton_loan"));
        sizePolicy5.setHeightForWidth(pushButton_loan->sizePolicy().hasHeightForWidth());
        pushButton_loan->setSizePolicy(sizePolicy5);

        horizontalLayout_26->addWidget(pushButton_loan);

        pushButton_return = new QPushButton(groupBox_loanAndReturn);
        pushButton_return->setObjectName(QString::fromUtf8("pushButton_return"));
        sizePolicy5.setHeightForWidth(pushButton_return->sizePolicy().hasHeightForWidth());
        pushButton_return->setSizePolicy(sizePolicy5);

        horizontalLayout_26->addWidget(pushButton_return);


        verticalLayout_13->addLayout(horizontalLayout_26);


        verticalLayout_14->addLayout(verticalLayout_13);


        gridLayout_2->addLayout(verticalLayout_14, 0, 0, 1, 1);


        horizontalLayout_27->addWidget(groupBox_loanAndReturn);


        verticalLayout_7->addLayout(horizontalLayout_27);

        groupBox_searching = new QGroupBox(frame_actions);
        groupBox_searching->setObjectName(QString::fromUtf8("groupBox_searching"));
        sizePolicy2.setHeightForWidth(groupBox_searching->sizePolicy().hasHeightForWidth());
        groupBox_searching->setSizePolicy(sizePolicy2);
        groupBox_searching->setMinimumSize(QSize(370, 190));
        groupBox_searching->setMaximumSize(QSize(370, 190));
        horizontalLayout_20 = new QHBoxLayout(groupBox_searching);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lineEdit = new QLineEdit(groupBox_searching);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_3->addWidget(lineEdit);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        frame_bookRecords_columnFilters = new QFrame(groupBox_searching);
        frame_bookRecords_columnFilters->setObjectName(QString::fromUtf8("frame_bookRecords_columnFilters"));
        frame_bookRecords_columnFilters->setFrameShape(QFrame::StyledPanel);
        frame_bookRecords_columnFilters->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_bookRecords_columnFilters);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        checkBox_filter_id = new QCheckBox(frame_bookRecords_columnFilters);
        checkBox_filter_id->setObjectName(QString::fromUtf8("checkBox_filter_id"));
        checkBox_filter_id->setLayoutDirection(Qt::LeftToRight);
        checkBox_filter_id->setChecked(true);

        verticalLayout_4->addWidget(checkBox_filter_id);

        checkBox_filter_isbn13 = new QCheckBox(frame_bookRecords_columnFilters);
        checkBox_filter_isbn13->setObjectName(QString::fromUtf8("checkBox_filter_isbn13"));
        checkBox_filter_isbn13->setLayoutDirection(Qt::LeftToRight);
        checkBox_filter_isbn13->setChecked(true);

        verticalLayout_4->addWidget(checkBox_filter_isbn13);

        checkBox_filter_title = new QCheckBox(frame_bookRecords_columnFilters);
        checkBox_filter_title->setObjectName(QString::fromUtf8("checkBox_filter_title"));
        checkBox_filter_title->setLayoutDirection(Qt::LeftToRight);
        checkBox_filter_title->setChecked(true);

        verticalLayout_4->addWidget(checkBox_filter_title);

        checkBox_filter_author = new QCheckBox(frame_bookRecords_columnFilters);
        checkBox_filter_author->setObjectName(QString::fromUtf8("checkBox_filter_author"));
        checkBox_filter_author->setLayoutDirection(Qt::LeftToRight);
        checkBox_filter_author->setChecked(true);

        verticalLayout_4->addWidget(checkBox_filter_author);

        checkBox_filter_category = new QCheckBox(frame_bookRecords_columnFilters);
        checkBox_filter_category->setObjectName(QString::fromUtf8("checkBox_filter_category"));
        checkBox_filter_category->setChecked(true);

        verticalLayout_4->addWidget(checkBox_filter_category);

        checkBox_filter_status = new QCheckBox(frame_bookRecords_columnFilters);
        checkBox_filter_status->setObjectName(QString::fromUtf8("checkBox_filter_status"));
        checkBox_filter_status->setChecked(true);

        verticalLayout_4->addWidget(checkBox_filter_status);


        horizontalLayout_11->addWidget(frame_bookRecords_columnFilters);

        frame_loanRecords_columnFilters = new QFrame(groupBox_searching);
        frame_loanRecords_columnFilters->setObjectName(QString::fromUtf8("frame_loanRecords_columnFilters"));
        frame_loanRecords_columnFilters->setFrameShape(QFrame::StyledPanel);
        frame_loanRecords_columnFilters->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_loanRecords_columnFilters);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        checkBox_filter_loanRecord_recordId = new QCheckBox(frame_loanRecords_columnFilters);
        checkBox_filter_loanRecord_recordId->setObjectName(QString::fromUtf8("checkBox_filter_loanRecord_recordId"));
        checkBox_filter_loanRecord_recordId->setChecked(true);

        verticalLayout_5->addWidget(checkBox_filter_loanRecord_recordId);

        checkBox_filter_loanRecord_bookId = new QCheckBox(frame_loanRecords_columnFilters);
        checkBox_filter_loanRecord_bookId->setObjectName(QString::fromUtf8("checkBox_filter_loanRecord_bookId"));
        checkBox_filter_loanRecord_bookId->setChecked(true);

        verticalLayout_5->addWidget(checkBox_filter_loanRecord_bookId);

        checkBox_filter_loanRecord_personId = new QCheckBox(frame_loanRecords_columnFilters);
        checkBox_filter_loanRecord_personId->setObjectName(QString::fromUtf8("checkBox_filter_loanRecord_personId"));
        checkBox_filter_loanRecord_personId->setChecked(true);

        verticalLayout_5->addWidget(checkBox_filter_loanRecord_personId);

        checkBox_filter_loanRecord_loanDate = new QCheckBox(frame_loanRecords_columnFilters);
        checkBox_filter_loanRecord_loanDate->setObjectName(QString::fromUtf8("checkBox_filter_loanRecord_loanDate"));
        checkBox_filter_loanRecord_loanDate->setChecked(true);

        verticalLayout_5->addWidget(checkBox_filter_loanRecord_loanDate);

        checkBox_filter_loanRecord_dueDate = new QCheckBox(frame_loanRecords_columnFilters);
        checkBox_filter_loanRecord_dueDate->setObjectName(QString::fromUtf8("checkBox_filter_loanRecord_dueDate"));
        checkBox_filter_loanRecord_dueDate->setChecked(true);

        verticalLayout_5->addWidget(checkBox_filter_loanRecord_dueDate);

        checkBox_filter_loanRecord_hvReturned = new QCheckBox(frame_loanRecords_columnFilters);
        checkBox_filter_loanRecord_hvReturned->setObjectName(QString::fromUtf8("checkBox_filter_loanRecord_hvReturned"));
        checkBox_filter_loanRecord_hvReturned->setChecked(true);

        verticalLayout_5->addWidget(checkBox_filter_loanRecord_hvReturned);


        horizontalLayout_11->addWidget(frame_loanRecords_columnFilters);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_updateView = new QPushButton(groupBox_searching);
        pushButton_updateView->setObjectName(QString::fromUtf8("pushButton_updateView"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pushButton_updateView->sizePolicy().hasHeightForWidth());
        pushButton_updateView->setSizePolicy(sizePolicy6);
        pushButton_updateView->setMinimumSize(QSize(0, 6));
        QFont font;
        font.setPointSize(8);
        pushButton_updateView->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/remix_icons/resources/icons/search-eye-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_updateView->setIcon(icon5);

        verticalLayout_2->addWidget(pushButton_updateView);

        checkBox_filter_caseSensitive = new QCheckBox(groupBox_searching);
        checkBox_filter_caseSensitive->setObjectName(QString::fromUtf8("checkBox_filter_caseSensitive"));

        verticalLayout_2->addWidget(checkBox_filter_caseSensitive);

        checkBox_searchInViewOnly = new QCheckBox(groupBox_searching);
        checkBox_searchInViewOnly->setObjectName(QString::fromUtf8("checkBox_searchInViewOnly"));
        checkBox_searchInViewOnly->setChecked(true);

        verticalLayout_2->addWidget(checkBox_searchInViewOnly);

        checkBox_updateViewAsIType = new QCheckBox(groupBox_searching);
        checkBox_updateViewAsIType->setObjectName(QString::fromUtf8("checkBox_updateViewAsIType"));

        verticalLayout_2->addWidget(checkBox_updateViewAsIType);


        horizontalLayout_11->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_11);


        horizontalLayout_20->addLayout(verticalLayout_3);


        verticalLayout_7->addWidget(groupBox_searching);

        groupBox_sqlMassAction = new QGroupBox(frame_actions);
        groupBox_sqlMassAction->setObjectName(QString::fromUtf8("groupBox_sqlMassAction"));
        sizePolicy2.setHeightForWidth(groupBox_sqlMassAction->sizePolicy().hasHeightForWidth());
        groupBox_sqlMassAction->setSizePolicy(sizePolicy2);
        groupBox_sqlMassAction->setMinimumSize(QSize(370, 100));
        groupBox_sqlMassAction->setMaximumSize(QSize(370, 100));
        horizontalLayout_12 = new QHBoxLayout(groupBox_sqlMassAction);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        plainTextEdit = new QPlainTextEdit(groupBox_sqlMassAction);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy7);
        plainTextEdit->setMinimumSize(QSize(0, 70));
        plainTextEdit->setMaximumSize(QSize(16777215, 70));
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(227, 227, 227)"));
        plainTextEdit->setFrameShape(QFrame::WinPanel);
        plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_12->addWidget(plainTextEdit);

        pushButton = new QPushButton(groupBox_sqlMassAction);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy4.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy4);
        pushButton->setMinimumSize(QSize(0, 70));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/remix_icons/resources/icons/send-plane-2-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon6);

        horizontalLayout_12->addWidget(pushButton);


        verticalLayout_7->addWidget(groupBox_sqlMassAction);


        horizontalLayout_14->addWidget(frame_actions);


        gridLayout_4->addWidget(frame_main, 0, 0, 1, 1);

        AdminPanel->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdminPanel);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1130, 21));
        AdminPanel->setMenuBar(menubar);
        statusbar = new QStatusBar(AdminPanel);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AdminPanel->setStatusBar(statusbar);
        QWidget::setTabOrder(tableView_bookRecords, pushButton_reloadBook);
        QWidget::setTabOrder(pushButton_reloadBook, pushButton_addBook);
        QWidget::setTabOrder(pushButton_addBook, pushButton_deleteRecords);
        QWidget::setTabOrder(pushButton_deleteRecords, lineEdit);

        retranslateUi(AdminPanel);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AdminPanel);
    } // setupUi

    void retranslateUi(QMainWindow *AdminPanel)
    {
        AdminPanel->setWindowTitle(QCoreApplication::translate("AdminPanel", "Admin Panel", nullptr));
        label_numBookRecords->setText(QCoreApplication::translate("AdminPanel", "Number of book records:", nullptr));
        label_numBookRecords_var->setText(QString());
        checkBox_readOnly->setText(QCoreApplication::translate("AdminPanel", "Read Only", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_bookRecords_3), QCoreApplication::translate("AdminPanel", "Book Records", nullptr));
        label_numLoanRecords->setText(QCoreApplication::translate("AdminPanel", "Number of loan records:", nullptr));
        label_numOverdueLoanRecords_var->setText(QString());
        label_numLoanRecords_var->setText(QString());
        label_numOverdueLoanRecords->setText(QCoreApplication::translate("AdminPanel", "Number of overdue records:", nullptr));
        checkBox_highlight_onLoan->setText(QCoreApplication::translate("AdminPanel", "Highlight On Loan Records", nullptr));
        checkBox_filter_loanRecord_onLoan->setText(QCoreApplication::translate("AdminPanel", "Show On Loan Records Only", nullptr));
        checkBox_highlight_overdue->setText(QCoreApplication::translate("AdminPanel", "Highlight Overdue Records", nullptr));
        checkBox_filter_loanRecord_overdue->setText(QCoreApplication::translate("AdminPanel", "Show Overdue Records Only", nullptr));
        pushButton_reloadLoans->setText(QCoreApplication::translate("AdminPanel", "Reload\n"
"Loan Records", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_loanRecords_3), QCoreApplication::translate("AdminPanel", "Loan Records (Read Only)", nullptr));
        label_today->setText(QString());
        comboBox_qDateFormat->setItemText(0, QCoreApplication::translate("AdminPanel", "yyyyMMdd", nullptr));
        comboBox_qDateFormat->setItemText(1, QCoreApplication::translate("AdminPanel", "yyyy-MM-dd", nullptr));
        comboBox_qDateFormat->setItemText(2, QCoreApplication::translate("AdminPanel", "dddd MMMM d yyyy", nullptr));
        comboBox_qDateFormat->setItemText(3, QCoreApplication::translate("AdminPanel", "dddd MMMM d", nullptr));
        comboBox_qDateFormat->setItemText(4, QCoreApplication::translate("AdminPanel", "dd MMMM yy", nullptr));
        comboBox_qDateFormat->setItemText(5, QCoreApplication::translate("AdminPanel", "MMMM d", nullptr));
        comboBox_qDateFormat->setItemText(6, QCoreApplication::translate("AdminPanel", "MM-dd", nullptr));
        comboBox_qDateFormat->setItemText(7, QCoreApplication::translate("AdminPanel", "MM-d", nullptr));

        groupBox_recordManipulation->setTitle(QCoreApplication::translate("AdminPanel", "Record Manipulation", nullptr));
        pushButton_addBook->setText(QCoreApplication::translate("AdminPanel", "Register\n"
"New Books", nullptr));
        pushButton_deleteRecords->setText(QCoreApplication::translate("AdminPanel", "Delete\n"
"Selected\n"
"Books", nullptr));
        pushButton_editBook->setText(QCoreApplication::translate("AdminPanel", "Edit\n"
"Selected\n"
"Books", nullptr));
        pushButton_reloadBook->setText(QCoreApplication::translate("AdminPanel", "Reload\n"
"Books\n"
"From DB", nullptr));
        groupBox_loanAndReturn->setTitle(QCoreApplication::translate("AdminPanel", "Loan / Return", nullptr));
        label_3->setText(QCoreApplication::translate("AdminPanel", "Person ID:", nullptr));
        pushButton_editPersonId->setText(QCoreApplication::translate("AdminPanel", "Edit", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_personId->setToolTip(QCoreApplication::translate("AdminPanel", "Click the Edit button to make changes.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        lineEdit_personId->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        label_2->setText(QCoreApplication::translate("AdminPanel", "Book ID: ", nullptr));
        pushButton_editBookId->setText(QCoreApplication::translate("AdminPanel", "Edit", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_bookId->setToolTip(QCoreApplication::translate("AdminPanel", "Click the Edit button to make changes.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("AdminPanel", "No. Days:", nullptr));
        comboBox_nDays->setItemText(0, QCoreApplication::translate("AdminPanel", "1", nullptr));
        comboBox_nDays->setItemText(1, QCoreApplication::translate("AdminPanel", "3", nullptr));
        comboBox_nDays->setItemText(2, QCoreApplication::translate("AdminPanel", "7", nullptr));
        comboBox_nDays->setItemText(3, QCoreApplication::translate("AdminPanel", "14", nullptr));
        comboBox_nDays->setItemText(4, QCoreApplication::translate("AdminPanel", "30", nullptr));

        pushButton_loan->setText(QCoreApplication::translate("AdminPanel", "Loan\n"
"[F8]", nullptr));
        pushButton_return->setText(QCoreApplication::translate("AdminPanel", "Return\n"
"[F9]", nullptr));
        groupBox_searching->setTitle(QCoreApplication::translate("AdminPanel", "Record Searching", nullptr));
        checkBox_filter_id->setText(QCoreApplication::translate("AdminPanel", "ID", nullptr));
        checkBox_filter_isbn13->setText(QCoreApplication::translate("AdminPanel", "ISBN13", nullptr));
        checkBox_filter_title->setText(QCoreApplication::translate("AdminPanel", "Title", nullptr));
        checkBox_filter_author->setText(QCoreApplication::translate("AdminPanel", "Author", nullptr));
        checkBox_filter_category->setText(QCoreApplication::translate("AdminPanel", "Category", nullptr));
        checkBox_filter_status->setText(QCoreApplication::translate("AdminPanel", "Status", nullptr));
        checkBox_filter_loanRecord_recordId->setText(QCoreApplication::translate("AdminPanel", "Record ID", nullptr));
        checkBox_filter_loanRecord_bookId->setText(QCoreApplication::translate("AdminPanel", "Book ID", nullptr));
        checkBox_filter_loanRecord_personId->setText(QCoreApplication::translate("AdminPanel", "Person ID", nullptr));
        checkBox_filter_loanRecord_loanDate->setText(QCoreApplication::translate("AdminPanel", "Loan Date", nullptr));
        checkBox_filter_loanRecord_dueDate->setText(QCoreApplication::translate("AdminPanel", "Return Date", nullptr));
        checkBox_filter_loanRecord_hvReturned->setText(QCoreApplication::translate("AdminPanel", "Returned?", nullptr));
        pushButton_updateView->setText(QCoreApplication::translate("AdminPanel", "Search", nullptr));
        checkBox_filter_caseSensitive->setText(QCoreApplication::translate("AdminPanel", "Case Sensitive", nullptr));
        checkBox_searchInViewOnly->setText(QCoreApplication::translate("AdminPanel", "Search In View Only", nullptr));
        checkBox_updateViewAsIType->setText(QCoreApplication::translate("AdminPanel", "Search As I Type", nullptr));
        groupBox_sqlMassAction->setTitle(QCoreApplication::translate("AdminPanel", "SQL Mass Action", nullptr));
        pushButton->setText(QCoreApplication::translate("AdminPanel", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminPanel: public Ui_AdminPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPANEL_H
