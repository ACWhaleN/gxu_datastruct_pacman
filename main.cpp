#include "gameinterface.h"
#include <QApplication>
#include "GameMap.h"

GameMap globalGameMap(65, 37);


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //新建游戏页面并显示
    GameInterface mainwindow;
    mainwindow.show();

    return a.exec();
}
