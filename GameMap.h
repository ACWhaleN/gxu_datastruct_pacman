#include <QVector>
#include <QPainter>
#include <bits/stdc++.h>
using namespace std;
class MyRand{
    public:
        int operator()(int n){
            srand(time(NULL));
            return rand() % n;
        }
};

class GameMap {
public:
    const int width;
    const int height;
    QRect BeanRect;
    QVector<QVector<int>> mapData;
    QVector<QVector<bool>> Visited;

    GameMap(int width, int height);
    ~GameMap();
    bool isRoad(int x,int y);
    void generatePerfectMaze(int x, int y);
    void loadMapData();
    void drawMap(QPainter &painter);
    bool isCollision(int x, int y);

private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

};






