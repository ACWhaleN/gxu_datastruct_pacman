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
    y = (PacStart_y+1) *30;
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
    y += speed*UD;  //上下
    x += speed*LR;  //左右
    int tempX[4] = {0, 0, -1, player_width+1};
    int tempY[4] = {-1, player_height+1, 0, 0};
    for (int k = 0; k < 4; k++)
    {
        if (globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30] == 1) //检测玩家墙壁碰撞方向
        {
            switch(k)
            {
            case 0: y += speed/2; UD = 0; break;
            case 1: y -= speed/2; UD = 0; break;
            case 2: x += speed/2; LR = 0; break;
            case 3: x -= speed/2; LR = 0; break;
            }
        }
        else if(globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]==2) //吃掉豆子的判定
        {
            globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]=0;
            globalGameMap.BeanScore += 10;
        }
    }
    player_rect.moveTo(x,y);
}
