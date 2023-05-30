#include "ghost.h"
#include "config.h"
#include "GameMap.h"
#include<list>
extern GameMap globalGameMap;
using namespace std;
Ghost::Ghost()
{
}

void Ghost::Set(int color)
{
    switch(color)
    {
    case 0:
        ApCe[0][0].load(blue_up1_path);
        ApCe[1][0].load(blue_up2_path);
        ApCe[0][1].load(blue_up1_path);
        ApCe[1][1].load(blue_up2_path);
        ApCe[0][2].load(blue_down1_path);
        ApCe[1][2].load(blue_down2_path);
        ApCe[0][3].load(blue_left1_path);
        ApCe[1][3].load(blue_left2_path);
        ApCe[0][4].load(blue_right1_path);
        ApCe[1][4].load(blue_right2_path);
//        ApCe[0][5].load(blue_up1_path);
//        ApCe[1][5].load(blue_up2_path);
        break;
    case 2:
    default:
        break;
    }
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

int Ghost::heuristic(Node start, Node goal)
{
    return abs(start.y - goal.y)+abs(start.x - goal.x);
}

void Ghost::A_Start(int Pac_x, int Pac_y)
{
    int player_x = int((Pac_x+15)/30),player_y = int((Pac_y+15)/30);
    Node *carry = NULL, tmp, start, goal;
    goal = SMap[player_x][player_y];
    start = SMap[rx][rx];
    SMap[rx][ry].cost = 0;
    open_set.push_back(&SMap[rx][ry]);
    cout<<"goal"<<player_x<<" "<<player_y<<endl;;
    do
    {
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
                    if(globalGameMap.mapData[tmp.x][tmp.y]!=1 && !SMap[tmp.x][tmp.y].isVisited)
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
    NextSearch.clear();
    //录入生成的路径
    while(open_set.empty() && (carry->x != rx || carry->y != ry))
    {
        PathNode.push_front(*carry);
        cout<<"path:"<<carry->x<<" "<<carry->y<<endl;
        carry=carry->parent;
    }
    cout<<"Done"<<endl;
    PathNode.push_back(SMap[player_x][player_y]);
    for(int i=0;i<64;i++)
        for(int j=0;j<32;j++)
        {
            SMap[i][j].isVisited = false;
            SMap[i][j].parent = NULL;
            SMap[i][j].cost = 999;
        }
}

void Ghost::Update(int Pac_x, int Pac_y)
{
    carry = carry==1?0:1;
    rx = int((x+15)/30);
    ry = int((y+15)/30);
    Mrect.moveTo( x, y);
    cout<<"enemy:"<<rx<<" "<<ry<<" "<<globalGameMap.mapData[rx][ry]<<endl;
    cout<<"next:"<<NextNode.x<<" "<<NextNode.y<<" "<<globalGameMap.mapData[rx][ry]<<endl;
    if(step == 0)
    {
        A_Start(Pac_x, Pac_y);
        step = 100/Game_rate;
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
    if(y == NextNode.y * 30 && x == NextNode.x * 30)
    {
        flag = 0;
    }
    if(judge())
    {
        cout<<"Jam!"<<endl;
        x = rx * 30;
        y = ry * 30;
    }
}

bool Ghost::judge()
{
    int tempX[4] = {ghost_width-2, 0, 2, 0};
    int tempY[4] = {0, ghost_height-2, 0, 2};
    for (int k = 0; k < 4; k++) {
        if (globalGameMap.mapData[int((x + tempX[k]) / 30)][int((y + tempY[k]) / 30)] == 1) {
            return true;
        }
    }
    return false;
}
