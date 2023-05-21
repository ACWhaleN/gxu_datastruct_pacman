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
                painter.setPen(QPen(Qt::white,30));//设置画笔形式
                painter.setBrush(white_brush);                //应用刷子
                painter.drawPoint(i*30+30,j*30+30);
                    // 绘制墙壁
                    break;
                case 2: // 豆子
                painter.setPen(QPen(Qt::green,13));
                painter.setBrush(green_brush);
                BeanRect.moveTo(30*i+15,30*j+15);
                painter.drawPie(BeanRect,0,360*16);
                    // 绘制豆子
                    break;
            }
        }
    }
}


bool GameMap::isCollision(int x, int y) {

    // 如果地图元素是墙壁，则返回true，表示发生碰撞
    int tempX[4]={16,0,-16,0};
    int tempY[4]={0,16,0,-16};
    for(int k=0;k<4;k++){
        if (mapData[(x+tempX[k])/30][(y+tempY[k])/30] == 1) {
        return true;
    }}

    // 否则返回false，表示没有碰撞
    return false;
}
