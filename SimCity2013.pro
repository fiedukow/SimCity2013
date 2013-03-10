#-------------------------------------------------
#
# Project created by QtCreator 2013-01-07T10:11:51
#
#-------------------------------------------------

QT       += core gui opengl
INCLUDEPATH += /usr/local/include/OGRE
INCLUDEPATH += /usr/include/ois
INCLUDEPATH += /usr/include/postgresql
INCLUDEPATH += src

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../bin/SimCity2013
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -DBOOST_ALL_NO_LIB -O3
QMAKE_LFLAGS += -lOgreMain -lOIS -lpqxx -lboost_thread

SOURCES += src/main.cpp\
           src/View/SimCityWindow.cpp \
           src/View/OgreWidget.cpp \
           src/View/BaseApplication.cpp \
           src/Model/World.cpp \
           src/Model/StaticBaseDriver.cpp \
           src/Model/Exceptions.cpp \
           src/Model/DBDataStructures.cpp \
    src/Model/Model.cpp \
    src/Common/GlobalLogger.cpp

HEADERS  += src/View/SimCityWindow.h \
            src/View/OgreWidget.h \
            src/View/BaseApplication.h \
            src/Model/World.h \
            src/Model/StaticBaseDriver.h \
            src/Model/Exceptions.h \
            src/Model/DBDataStructures.h \
            src/Model/ConstrainedNumeric.hpp \
    src/Model/Model.h \
    src/Model/SimulationPart.h \
    src/Common/GeneralTypes.h \
    src/Common/GlobalLogger.h

FORMS    += src/View/SimCityWindow.ui
