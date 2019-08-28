#-------------------------------------------------
#
# Project created by QtCreator 2019-04-18T13:15:36
#
#-------------------------------------------------

QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SLMS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    bookrecordqsqlrelationaltablemodel.cpp \
    lineeditpopupdialoag.cpp \
    loanrecordqsqlrelationaltablemodel.cpp \
        main.cpp \
        mainwindow.cpp \
    logindialog.cpp \
    adminpanel.cpp \
    comboboxdelegate.cpp \
    category.cpp \
    headermodel.cpp \
    normaldelegate.cpp \
    return.cpp \
    status.cpp \
    myqsqlrelationaldelegate.cpp \
    noteditabledelegate.cpp \
    qubyxsearchfilterproxymodel.cpp

HEADERS += \
    bookrecordqsqlrelationaltablemodel.h \
    lineeditpopupdialoag.h \
    loanrecordqsqlrelationaltablemodel.h \
        mainwindow.h \
    logindialog.h \
    adminpanel.h \
    comboboxdelegate.h \
    category.h \
    headermodel.h \
    normaldelegate.h \
    return.h \
    status.h \
    myqsqlrelationaldelegate.h \
    noteditabledelegate.h \
    qubyxsearchfilterproxymodel.h

FORMS += \
    lineeditpopupdialoag.ui \
        mainwindow.ui \
    logindialog.ui \
    adminpanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

RC_ICONS = SLMS.ico
