#-------------------------------------------------
#
# Project created by QtCreator 2013-01-07T10:11:51
#
#-------------------------------------------------

QT       += core gui
INCLUDEPATH += /usr/include/postgresql
INCLUDEPATH += src

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ./bin/SimCity2013
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -DBOOST_ALL_NO_LIB -O0
QMAKE_LFLAGS += -lpqxx -lboost_thread -lboost_chrono -lboost_program_options -lboost_serialization -lboost_system

SOURCES += src/main.cpp\
           src/View/SimCityWindow.cpp \
           src/Model/World.cpp \
           src/Model/StaticBaseDriver.cpp \
           src/Model/Exceptions.cpp \
           src/Model/DBDataStructures.cpp \
           src/Model/Model.cpp \
           src/Common/GlobalLogger.cpp \
           src/Model/ObjectManager.cpp \
           src/Model/Physics/NewtonsDynamics.cpp \
           src/Model/Objects/ObjectSnapshot.cpp \
           src/Model/Physics/Positioning.cpp \
           src/Model/Objects/Objects.cpp \
           src/Model/Objects/Object.cpp \
           src/Model/Objects/ObjectsSnapshots.cpp \
           src/Model/Objects/Observer.cpp \
           src/Common/NewStateObserver.cpp \
           src/Controller/Controller.cpp \
           src/Controller/Events/EventBase.cpp \
           src/Controller/QtUnspaghetti.cpp \
           src/Controller/Events/EventStop.cpp \
           src/Controller/Events/EventStart.cpp \
           src/Controller/Events/EventPause.cpp \
           src/Controller/Events/EventInterrput.cpp \
           src/Controller/Events/EventNewMapRequest.cpp \
           src/View/MapScene.cpp \
           src/View/GraphicsElements/Road.cpp \
           src/Controller/Events/EventNewSnapshotRequest.cpp \
           src/View/GraphicsElements/Car.cpp \
           src/Model/Objects/LiveObject.cpp \
           src/Model/Objects/Observers.cpp \
           src/View/GraphicsElements/Sensor.cpp \
           src/Controller/Events/EventSetSimulationSpeed.cpp \
           src/3rd/DynDbDriver/dyndbdriver.cpp \
           src/3rd/DynDbDriver/common.cpp \
           src/3rd/DynDbDriver/logger.cpp \
           src/Controller/Events/EventSetCarLimit.cpp \
           src/View/GraphicsElements/Pedestrian.cpp \
    src/Controller/Events/EventSetPedestrianLimit.cpp \
    src/Model/Timer.cpp

HEADERS  += src/View/SimCityWindow.h \
            src/Model/World.h \
            src/Model/StaticBaseDriver.h \
            src/Model/Exceptions.h \
            src/Model/DBDataStructures.h \
            src/Model/ConstrainedNumeric.hpp \
            src/Model/Model.h \
            src/Model/SimulationPart.h \
            src/Common/GeneralTypes.h \
            src/Common/GlobalLogger.h \
            src/Model/ObjectManager.h \
            src/Model/Objects/Object.h \
            src/Model/Physics/NewtonsDynamics.h \
            src/Model/Objects/ObjectSnapshot.h \
            src/Model/Physics/Positioning.h \
            src/Model/Objects/Objects.h \
            src/Model/Objects/ObjectsSnapshots.h \
            src/Model/Objects/Observer.h \
            src/Common/NewStateObserver.h \
            src/Controller/Controller.h \
            src/Utils/BlockingQueue.hpp \
            src/Controller/Events/EventBase.h \
            src/Controller/QtUnspaghetti.h \
            src/Controller/Events/EventStop.h \
            src/Controller/Events/EventStart.h \
            src/Controller/Events/EventPause.h \
            src/Controller/Events/AllEvents.h \
            src/Controller/Events/EventInterrput.h \
            src/Controller/Events/EventNewMapRequest.h \
            src/View/MapScene.h \
            src/View/GraphicsElements/Road.h \
            src/Controller/Events/EventNewSnapshotRequest.h \
            src/View/GraphicsElements/Car.h \
            src/Model/Objects/LiveObject.h \
            src/Model/Objects/Observers.h \
            src/View/GraphicsElements/Sensor.h \
            src/Controller/Events/EventSetSimulationSpeed.h \
            src/3rd/DynDbDriver/dyndbdriver.h \
            src/3rd/DynDbDriver/common.h \
            src/3rd/DynDbDriver/logger.h \
            src/Controller/Events/EventSetCarLimit.h \
            src/View/GraphicsElements/Pedestrian.h \
    src/Controller/Events/EventSetPedestrianLimit.h \
    src/Model/Timer.h

FORMS    += src/View/SimCityWindow.ui
