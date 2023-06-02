#include <QVector>
#include <QPainter>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
/**
 * @brief 用于random_shuffle函数生成随机数
 */
class MyRand{
public:
    /**
     * @brief 重载函数调用运算符，生成介于 0 和 n-1 之间的随机整数
     * @param n 上界（不包含）
     * @return 生成的随机整数
     */
    int operator()(int n){
        return rand() % n;
    }
};

/**
 * @brief 游戏地图类
 */
class GameMap {
public:
    const int width; /**< 地图宽度 */
    const int height; /**< 地图高度 */
    int BeanScore = 0;/**< 吃豆子所获分数 */
    bool AttackModel = false; /**< 玩家特殊模式 */
    QRect BeanRect; /**< 豆子所占区域的矩形 */
    QRect powerPelletsRect; /**< 大力丸所占区域的矩形 */
    QVector<QVector<int>> mapData; /**< 地图的二维数组 */
    QVector<QVector<bool>> Visited; /**< 用于DFS判断是否已访问 */
    QVector<QVector<bool>> AMap; /**< 用于AMap寻路标记 （false为不可达） */
    /**
         * @brief 构造函数
         * @param width 地图宽度
         * @param height 地图高度
         */
    GameMap(int width, int height);

    /**
         * @brief 析构函数
         */
    ~GameMap();

    /**
         * @brief 判断给定坐标是否为通路
         * @param x x坐标
         * @param y y坐标
         * @return 是否为通路
         */
    bool isRoad(int x, int y);

    /**
         * @brief DFS生成无环的完美迷宫
         * @param x 起始点的x坐标
         * @param y 起始点的y坐标
         */
    void generatePerfectMaze(int x, int y);

    /**
         * @brief 根据地图数据绘制墙壁和豆子
         * @param painter QPainter对象，用于绘制
         */
    void drawMap(QPainter &painter);

    /**
         * @brief 判断给定坐标是否碰撞墙壁
         * @param x x坐标
         * @param y y坐标
         * @return 是否碰撞墙壁
         */
    bool isCollision(int x, int y);

    /**
         * @brief 打破墙壁，让完美迷宫变成有环图
         */
    void breakWalls();

    /**
    * @brief 重置AMap，为新一轮寻路做准备
    */
    void reAMap();

    /**
    * @brief 刷新生成新地图
    */
    void UpdateMap();

    /**
    * @brief 大力丸！小小的pacman震撼！
    */
    void PowerPellets();


private:
    int dx[4] = {-1, 0, 1, 0}; /**< x坐标的步进方向 */
    int dy[4] = {0, 1, 0, -1}; /**< y坐标的步进方向 */

};
