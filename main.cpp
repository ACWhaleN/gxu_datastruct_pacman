#include <QApplication>
#include "GameMap.h"
#include "startinterface.h"

GameMap globalGameMap(65, 37);

int main(int argc, char *argv[])
{
    srand(time(0));//生成随机种子
    QApplication a(argc, argv);
    StartInterface startwindow;
    startwindow.show();

    return a.exec();
}
