#-------------------------------------------------
#
# Project created by QtCreator 2013-01-07T10:11:51
#
#-------------------------------------------------

QT       += core gui opengl
INCLUDEPATH += /usr/local/include/OGRE
INCLUDEPATH += /usr/include/ois

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../bin/SimCity2013
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -DBOOST_ALL_NO_LIB
QMAKE_LFLAGS += -lOgreMain -lOIS

SOURCES += src/main.cpp\
           src/SimCityWindow.cpp \
           src/OgreWidget.cpp \
           src/BaseApplication.cpp

HEADERS  += src/SimCityWindow.h \
            src/OgreWidget.h \
            src/BaseApplication.h

FORMS    += src/SimCityWindow.ui
