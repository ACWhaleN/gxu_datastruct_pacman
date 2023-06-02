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
    x = (PacStart_x+1) * 30;
    y = (PacStart_y+1) * 30;
    UD=LR = 0;  //初始为静止状态
    speed = player_speed;      //速度设定
    life = initial_life;     //血量设定
    flag = step = 0;
    state = 0;
    invincible = false;
    inviDelay = 50/Game_rate;
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
    if(invincible && inviDelay-- == 0)
    {
        inviDelay = 50/Game_rate;
        invincible = false;
    }
    int NewY = y + speed*UD;//上下
    int NewX = x + speed*LR;//左右
    bool mark = true;
    for (int k = 0; k < 4; k++)
    {
        if(globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]==2) //吃掉豆子的判定
        {
            globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]=0;
            globalGameMap.BeanScore += 10;
        }
        if (globalGameMap.mapData[(NewX+judgeX[k])/30][(NewY+judgeY[k])/30] == 1)
        {
            mark = false;
        }
        if(globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]==3) //吃掉大力丸的判定
        {
            globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]=0;
            globalGameMap.BeanScore += 100;
            globalGameMap.AttackModel=true;
        }
    }
    if(mark)
    {
        y = NewY;
        x = NewX;
    }
    for(int k = 0; k < 4; k++)
    {
        if (globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30] == 1) //检测玩家墙壁碰撞方向
        {
            switch(k)
            {
            case 0: y ++; UD = 0; break;
            case 1: y --; UD = 0; break;
            case 2: x ++; LR = 0; break;
            case 3: x --; LR = 0; break;
            }
        }
    }
    player_rect.moveTo(x,y);
}
