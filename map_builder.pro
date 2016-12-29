#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T22:15:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = map_builder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    callbackgraphicsrectitem.cpp \
    callablegraphicscircleitem.cpp \
    shapegenerator.cpp \
    random_color_generator.cpp \
    generateasdialog.cpp

HEADERS  += mainwindow.h \
    shapedata.h \
    callbackgraphicsrectitem.h \
    callablegraphicscircleitem.h \
    shapegenerator.h \
    random_color_generator.h \
    generateasdialog.h

FORMS    += mainwindow.ui \
    generateasdialog.ui

RESOURCES += \
    resources.qrc
