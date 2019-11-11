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
        AccountProxy.cpp \
        CardModel.cpp \
        CardProxy.cpp \
        CreditAccount.cpp \
        IAccount.cpp \
        ICard.cpp \
        ITransaction.cpp \
        IUser.cpp \
        LocalConfig.cpp \
        PayrollProcessor.cpp \
        SavingsAccount.cpp \
        Storage.cpp \
        DatabaseConnect.cpp \
        TerminalConnector.cpp \
        TransactionModel.cpp \
        TransactionQueue.cpp \
        TransactionQueueProcessor.cpp \
        UserModel.cpp \
        UserProxy.cpp \
        acountlistview.cpp \
        main.cpp \
        mainmenuview.cpp \
        mainwindow.cpp \
        signinview.cpp

HEADERS += \
        AccountModel.h \
        AccountPolicy.h \
        AccountProxy.h \
        CardModel.h \
        CardProxy.h \
        CreditAccount.h \
        DatabaseConnect.h \
        DebitAccount.h \
        IAccount.h \
        ICard.h \
        ITransaction.h \
        IUser.h \
        LocalConfig.h \
        PayrollAccount.h \
        PayrollProcessor.h \
        SavingsAccount.h \
        Storage.h \
        StringUtils.h \
        TerminalConnector.h \
        TransactionModel.h \
        TransactionQueue.h \
        TransactionQueueProcessor.h \
        UserModel.h \
        UserProxy.h \
        acountlistview.h \
        mainmenuview.h \
        mainwindow.h \
        signinview.h

FORMS += \
        acountlistview.ui \
        mainmenuview.ui \
        mainwindow.ui \
        signinview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
