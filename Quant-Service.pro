#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T09:53:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quant-Service
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mngrquerys.cpp \
    mngrconnection.cpp \
    dialogs/add.cpp \
    dialogs/staff.cpp \
    dialogs/storage.cpp

HEADERS  += mainwindow.h \
    mngrquerys.h \
    mngrconnection.h \
    dialogs/add.h \
    dialogs/staff.h \
    dialogs/storage.h

FORMS    += mainwindow.ui \
    dialogs/add.ui \
    dialogs/staff.ui \
    dialogs/storage.ui

RESOURCES += \
    resource.qrc

TRANSLATIONS += \
    Quant-Service_ru.ts
