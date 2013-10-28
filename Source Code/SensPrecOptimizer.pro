#-------------------------------------------------
#
# Project created by QtCreator 2013-09-14T21:24:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = SensPrecOptimizer
TEMPLATE = app
CONFIG += release \
    embed_manifest_exe
    #debug \
    #warn_on \
    #rtti \
    #exceptions \
#QMAKE_CXXFLAGS_RELEASE *= -O3
#QMAKE_LFLAGS = -static -static-libSystem -static-libstdc++

macx
{
    INCLUDEPATH += /opt/local/include
    LIBS += -L/opt/local/lib
    LIBS += -lboost_system-mt \
        -lboost_filesystem-mt
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.5
}
linux-g++
{
}
win32
{
    CONFIG -= x86_64 \
        embed_manifest_dll
    INCLUDEPATH += "C:\local\boost_1_54_0"
    #LIBS += -L"C:\local\boost_1_54_0\lib32-msvc-10.0" \
    #    -L"C:\local\boost_1_54_0\libs"

    #LIBS += -lboost_system-vc100-mt-1_54 \
    #    -lboost_filesystem-vc100-mt-1_54
}

SOURCES += main.cpp\
    mainwindow.cpp \
    writeFile.cpp \
    readFile.cpp \
    parameters.cpp \
    algorithm.cpp \
    logger.cpp \
    manager.cpp

HEADERS  += mainwindow.h \
    ui_mainwindow.h \
    writeFile.h \
    readFile.h \
    parameters.h \
    global.h \
    algorithm.h \
    logger.h \
    manager.h

FORMS    += \
    mainwindow.ui
