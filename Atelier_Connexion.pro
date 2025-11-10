QT += core gui sql widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Atelier_Connexion
TEMPLATE = app

SOURCES += \
    employes.cpp \
    main.cpp \
    connection.cpp

HEADERS += \
    connection.h \
    employes.h
