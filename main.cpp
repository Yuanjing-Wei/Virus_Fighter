#include "mainwindow.h"
#include "gameengine.h"
#include <QApplication>
#include <QDir>
GameEngine * game;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    MainWindow w;
    w.show();
    return a.exec();
}
