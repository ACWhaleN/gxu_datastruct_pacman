#include"GameMap.h"
#include<iostream>

void GameMap::drawMap(QPainter &painter) {

    //设置画笔形式
    //std::cout<<"\n\n\n";
    QBrush white_brush( QColor("white") );       //把刷子设置为白色
    QBrush green_brush( QColor("green") );

    for (int j = 0; j < height; ++j) {

        for (int i = 0; i < width; ++i) {
            int mapElement = mapData[i][j];
            //std::cout<<mapElement<<" ";
            //if(i==width-1)std::cout<<"\n";
            switch (mapElement) {
                case 0: // 空格
                    // 不绘制任何内容
                    break;
                case 1: // 墙壁
                painter.setPen(QPen(Qt::white,20));//设置画笔形式
                painter.setBrush(white_brush);                //应用刷子
                painter.drawPoint(j*30,i*30);
                    // 绘制墙壁
                    break;
                case 2: // 豆子
                painter.setPen(QPen(Qt::green,13));
                painter.setBrush(green_brush);
                BeanRect.moveTo(30*i,30*j);
                painter.drawPie(BeanRect,0,360*16);
                    // 绘制豆子
                    break;
            }
        }
    }
}


bool GameMap::isCollision(int x, int y) {
    int gridX = x ; // 计算在地图数组中的坐标
    int gridY = y ;

    // 如果数组越界，返回true，表示发生碰撞
    if (gridX < 0 || gridX >= 2400 || gridY < 0 || gridY >= 1440) {
        return true;
    }

    // 如果地图元素是墙壁，则返回true，表示发生碰撞
    if (mapData[(gridY+40)/30][(gridX+40)/30] == 1) {
        return true;
    }

    // 否则返回false，表示没有碰撞
    return false;
}
