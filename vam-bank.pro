#-------------------------------------------------
#
# Project created by QtCreator 2019-10-07T14:30:05
#
#-------------------------------------------------

QT       += core gui serialport sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vam-bank
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
        Account/AccountProxy.cpp \
        Card/CardModel.cpp \
        Card/CardProxy.cpp \
        Account/CreditAccount.cpp \
        Account/IAccount.cpp \
        Card/ICard.cpp \
        Database/LocalConfig.cpp \
        Transaction/ITransaction.cpp \
        User/IUser.cpp \
        Database/LocalConfig.cpp \
        Processing/PayrollProcessor.cpp \
        Account/SavingsAccount.cpp \
        Database/Storage.cpp \
        Database/DatabaseConnect.cpp \
        Processing/TerminalConnector.cpp \
        Transaction/TransactionModel.cpp \
        Processing/TransactionQueue.cpp \
        Processing/TransactionQueueProcessor.cpp \
        User/UserModel.cpp \
        User/UserProxy.cpp \
        main.cpp \
        mainpageview.cpp \
        mainwindow.cpp \
        manageaccountview.cpp \
        signinview.cpp

HEADERS += \
        Account/AccountModel.h \
        Account/AccountPolicy.h \
        Account/AccountProxy.h \
        Card/CardModel.h \
        Card/CardProxy.h \
        Account/CreditAccount.h \
        Database/DatabaseConnect.h \
        Account/DebitAccount.h \
        Account/IAccount.h \
        Card/ICard.h \
        Transaction/ITransaction.h \
        User/IUser.h \
        Database/LocalConfig.h \
        Account/PayrollAccount.h \
        Processing/PayrollProcessor.h \
        Account/SavingsAccount.h \
        Database/Storage.h \
        StringUtils.h \
        Processing/TerminalConnector.h \
        Transaction/TransactionModel.h \
        Processing/TransactionQueue.h \
        Processing/TransactionQueueProcessor.h \
        User/UserModel.h \
        User/UserProxy.h \
        mainpageview.h \
        mainwindow.h \
        manageaccountview.h \
        signinview.h

FORMS += \
        mainpageview.ui \
        mainwindow.ui \
        manageaccountview.ui \
        signinview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
