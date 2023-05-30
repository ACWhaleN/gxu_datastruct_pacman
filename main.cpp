#include "gameinterface.h"
#include <QApplication>
#include "GameMap.h"
#include "startinterface.h"

GameMap globalGameMap(65, 37);
using namespace std;


int main(int argc, char *argv[])
{
    srand(time(0));//生成随机种子
    QApplication a(argc, argv);
    //新建游戏页面并显示
    //    GameInterface gamewindow;
    //    gamewindow.show();
    StartInterface startwindow;
    startwindow.show();

    return a.exec();
}
