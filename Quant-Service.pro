#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T09:53:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quant-Service
TEMPLATE = app

VERSION = 0.6.0.0
#Last digit:
# 0 - Pre-Alpha
# 1 - Alpha
# 2 - Beta
# 3 - Release Candidate
# 4 - Release

# RC_ICONS = images/DBA_Icon.ico
QMAKE_TARGET_COMPANY = Quant
QMAKE_TARGET_PRODUCT = QuantService
QMAKE_TARGET_DESCRIPTION = Menegement of service-center
QMAKE_TARGET_COPYRIGHT = (CopyLeft) Demetri0

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
    QuantService_ru.ts
