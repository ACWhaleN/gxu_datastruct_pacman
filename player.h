#ifndef PLAYER_H
#define PLAYER_H

#include <QPixmap>
#include "config.h"
class player
{
public:

    player();   //初始化
    void Update();  //坐标及状态更新
    int x, y;    //玩家坐标
    int speed;
    int life;   //玩家剩余命数
    int UD, LR;  //玩家运动状态（0：静止，UD代表上下，LR代表左右）
    int flag, step;   //记录图片状态及张闭嘴间隔的变量
    int state;  //记录玩家朝向
    int inviDelay; //无敌时延
    bool invincible; //无敌状态
    QRect player_rect;  //碰撞体积
    int tempX[4] = {0, 0, 0, player_width};
    int tempY[4] = {0, player_height, 0, 0};
    int judgeX[4] = {0, 0, 4, player_width-4};
    int judgeY[4] = {4, player_height-4, 0, 0};
};

#endif // PLAYER_H
