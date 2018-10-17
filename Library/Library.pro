#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T19:05:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Library
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# pragma warning (disable:4819)

SOURCES += main.cpp\
        widget.cpp \
    users.cpp \
    pageadminister.cpp \
    books.cpp \
    pageuser.cpp

HEADERS  += widget.h \
    users.h \
    pageadminister.h \
    books.h \
    pageuser.h

FORMS    += widget.ui

RESOURCES += \
    resource.qrc
