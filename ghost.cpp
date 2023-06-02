#include "ghost.h"
#include "config.h"
#include "GameMap.h"
#include<list>
extern GameMap globalGameMap;
using namespace std;
/**
 * @brief Ghost类的构造函数
 */
Ghost::Ghost()
{
    ApCe[0][0].load(attackable1_path);
    ApCe[1][0].load(attackable2_path);
    ApCe[0][1].load(blue_up1_path);
    ApCe[1][1].load(blue_up2_path);
    ApCe[0][2].load(blue_down1_path);
    ApCe[1][2].load(blue_down2_path);
    ApCe[0][3].load(blue_left1_path);
    ApCe[1][3].load(blue_left2_path);
    ApCe[0][4].load(blue_right1_path);
    ApCe[1][4].load(blue_right2_path);
    ApDe[1].load(deadup_path);
    ApDe[2].load(deaddown_path);
    ApDe[3].load(deadleft_path);
    ApDe[4].load(deadright_path);
    x = int(EnStart_x + EnStart_w/2)*30;
    y = int(EnStart_y + EnStart_h/2)*30;
    rx = int((x+15)/30);
    ry = int((y+15)/30);
    NextNode.x = rx;
    NextNode.y = ry;
    for(int i=0;i<64;i++)
        for(int j=0;j<32;j++)
        {
            SMap[i][j].x = i;
            SMap[i][j].y = j;
        }
    Mrect.setWidth(ghost_width);
    Mrect.setHeight(ghost_height);
    Mrect.moveTo(x,y);
}
/**
 * @brief 计算曼哈顿距离
 * @param start 起始位置
 * @param goal 目标位置
 */
int Ghost::heuristic(Node start, Node goal)
{
    return abs(start.y - goal.y)+abs(start.x - goal.x);
}
/**
 * @brief A*寻路算法
 * @param Pac_x 玩家的x坐标
 * @param Pac_y 玩家的y坐标
 */
void Ghost::A_Start(int Pac_x, int Pac_y)
{
    int player_x = int((Pac_x+player_width/2)/30),player_y = int((Pac_y+player_height/2)/30);
    int break_mark = 0; //防过长
    Node *carry = NULL, tmp, start, goal;
    goal = SMap[player_x][player_y];
    start = SMap[rx][rx];
    SMap[rx][ry].cost = 0;
    open_set.push_back(&SMap[rx][ry]);
    do
    {
        break_mark++;
        if(break_mark > 50)
            break;
        int MinCost = 998;
        for(auto &node : open_set)
        {
            if(node->cost < MinCost)
            {
                MinCost = node->cost;
                NextSearch.clear();
                NextSearch.push_back(node);
            }
            else if(node->cost == MinCost)
            {
                NextSearch.push_back(node);
            }
        }

        //从当次搜索节点中依次提取并拓展
        while(!NextSearch.empty())
        {
            carry = NextSearch.front();
            NextSearch.pop_front();
            open_set.remove(carry);
            SMap[carry->x][carry->y].isVisited = true;
            if(carry->x == player_x && carry->y == player_y)
            {
                break;
            }
            else
            {
                for(int i=0 ; i<4; i++)
                {
                    tmp.x = carry->x + move[i][0];
                    tmp.y = carry->y + move[i][1];
                    if(tmp.x<0||tmp.x>64||tmp.y<0||tmp.y>32)
                        continue;
                    if(globalGameMap.AMap[tmp.x][tmp.y] && !SMap[tmp.x][tmp.y].isVisited)
                    {
                        tmp.cost = heuristic(tmp, goal) + heuristic(tmp, start);
                        if(tmp.cost < SMap[tmp.x][tmp.y].cost)
                        {
                            SMap[tmp.x][tmp.y].cost = tmp.cost;
                            SMap[tmp.x][tmp.y].parent = &SMap[carry->x][carry->y];
                        }
                        open_set.push_back(&SMap[tmp.x][tmp.y]);
                    }
                }
            }
        }
    }while(!open_set.empty() && (carry->x != player_x || carry->y != player_y));
    open_set.clear();
    PathNode.clear();
    NextSearch.clear();
    //录入生成的路径
    int count = 2;
    while((carry->x != rx || carry->y != ry)|| carry->parent!=NULL)
    {
        PathNode.push_front(*carry);
        if( count-- >0&& count != 1)
        {
            globalGameMap.AMap[carry->x][carry->y] = false; //标记最后2个节点不可达，实现围堵的效果
        }
        carry=carry->parent;
    }
    for(int i=0;i<64;i++)
        for(int j=0;j<32;j++)
        {
            SMap[i][j].isVisited = false;
            SMap[i][j].parent = NULL;
            SMap[i][j].cost = 999;
        }
}
/**
 * @brief Ghost的更新函数
 * @param Pac_x 玩家的x坐标
 * @param Pac_y 玩家的y坐标
 */
void Ghost::Update(int Pac_x, int Pac_y)
{
    carry = carry==1?0:1;
    rx = int((x+15)/30);
    ry = int((y+15)/30);
    Mrect.moveTo( x, y);

    if(Start_Delay > 0)   //启动时延未结束保持等待状态
        return;
    if(step <= 0)
    {
        A_Start(Pac_x, Pac_y);
        step = 100/Game_rate;
        mark = true;
    }
    else
        step--;
    if(x == NextNode.x*30 && y == NextNode.y*30 && !PathNode.empty())
    {
        NextNode = PathNode.front();
        PathNode.pop_front();
    }
    if(y > NextNode.y * 30)
    {
        y -= enemy_speed;
        flag = 1;
    }
    else if(y < NextNode.y * 30)
    {
        y += enemy_speed;
        flag = 2;
    }
    if(x > NextNode.x * 30)
    {
        x -= enemy_speed;
        flag = 3;
    }
    else if(x < NextNode.x * 30)
    {
        x += enemy_speed;
        flag = 4;
    }
    if(globalGameMap.AttackModel && live)
        flag = 0;
}

