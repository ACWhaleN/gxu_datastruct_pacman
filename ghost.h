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
    //颜色与停止上下左右
    int color = 0, step = 0, flag = 0;
    int move[4][2]={{ 0, -1},{ 0, 1},{ -1, 0},{ 1, 0}};
    //启动时延
    int Start_Delay = 0;
    //标记寻路状态以定期重置AMap
    bool mark = false;
    bool live = true;
    Node SMap[64][32];
    Node NextNode;
    list<Node *> open_set;
    list<Node *> NextSearch;
    list<Node> PathNode;
    //图片状态
    //0:可被攻击
    //1-4:上下左右
    QPixmap ApCe[2][5];
    QPixmap ApDe[5];
    //初始化
    void Set();
    //状态更新;
    void Update(int player_x, int player_y);
    //A*寻路算法;
    void A_Start(int player_x, int player_y);
    //计算曼哈顿距离判断优先级
    int heuristic(Node start, Node goal);
};

#endif // GHOST_H
