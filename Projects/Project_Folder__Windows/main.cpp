/*! \file main.cpp
    \brief the main initialises and runs the QApplicaion instance

    \see QApplication
*/

#include <QApplication>
#include <QDir>
#include <QString>
#include "mainwindow.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QString appPath;

    QApplication app(argc, argv);
    appPath = QDir::currentPath();
    appPath = appPath + "/";//PATH_SUB_CHAR";

    mainwindow window(appPath);
    window.show();
    return app.exec();
}


