#ifndef GHOST_H
#define GHOST_H

#include<QRect>
#include<QPixmap>
#include<queue>
using namespace std;

struct Node{
    int x, y;
    Node* parent = NULL;
    int cost = 999;
    bool isVisited = false;
};



class Ghost
{
public:
    Ghost();
    int carry = 0;
    int x, y;
    int rx, ry;
    QRect Mrect;
    int step = 0, flag = 2;
    bool live = true;
    //0:可被攻击
    //1-4:上下左右
    QPixmap ApCe[2][5];
    QPixmap ApDe[5];

    int move[4][2]={{ 0, -1},{ 0, 1},{ -1, 0},{ 1, 0}};
    //启动时延
    int Start_Delay = 0;
    //标记寻路状态以定期重置AMap
    bool mark = false;
    //状态更新;
    void Update(int player_x, int player_y);
private:
    Node SMap[64][32];
    Node NextNode;
    list<Node *> open_set;
    list<Node *> NextSearch;
    list<Node> PathNode;
    //A*寻路算法;
    void A_Start(int player_x, int player_y);
    //计算曼哈顿距离
    int heuristic(Node start, Node goal);
    int judgeX[4] = {0, 0, -1, 1};
    int judgeY[4] = {-1, 1, 0, 0};
};

#endif // GHOST_H
