QT += testlib
QT += widgets
QT       += core gui
#QT += gui


# Adjust the include paths accordingly
INCLUDEPATH += ../src

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testgui.cpp \
    ../src/mainwindow.cpp \
    ../src/numberguessing.cpp

FORMS +=  ../src/mainwindow.ui

HEADERS += \
    ../src/mainwindow.h \
    ../src/numberguessing.h
