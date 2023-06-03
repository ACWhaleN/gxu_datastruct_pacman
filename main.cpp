#include <QApplication>
#include "GameMap.h"
#include "startinterface.h"

GameMap globalGameMap(65, 37);

int main(int argc, char *argv[])
{
    srand(time(0)); //生成随机种子
    QApplication a(argc, argv);
    // 新建开始界面并显示
    StartInterface startwindow;
    startwindow.show();

    return a.exec();
}
