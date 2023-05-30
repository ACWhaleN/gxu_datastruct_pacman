#include "player.h"
#include "config.h"
#include "GameMap.h"
extern GameMap globalGameMap;
/**
 * @brief Player类的构造函数
 */
player::player()
{
    //出生坐标
    x = PacStart_x*30;
    y = PacStart_y*30;
    UD=LR = 0;  //初始为静止状态
    speed = player_speed;      //速度设定
    life = initial_life;     //血量设定
    flag = step = 0;
    state = 0;
    //受击体积设定
    player_rect.setWidth(player_width);
    player_rect.setHeight(player_height);
    player_rect.moveTo(x,y);
}
/**
 * @brief 更新玩家数据
 */
void player::Update()
{
    int NewY=y+speed*UD;  //上下
    int NewX=x+speed*LR;  //左右
    if (!globalGameMap.isCollision(NewX, NewY)) {
        // 如果没有碰撞，更新位置
        x = NewX;
        y = NewY;
    }
    int tempX[4]={2,0,-2,0};
    int tempY[4]={0,2,0,-2};
    //吃掉豆子的判定
    for(int k=0;k<4;k++)
    {
        if (globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]==2)
        {
            globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]=0;
            globalGameMap.BeanScore += 10;
        }
    }
    player_rect.moveTo(x,y);
}
