#include"GameMap.h"

/**
 * @brief 判断给定坐标是否为通路
 * @param x x坐标
 * @param y y坐标
 * @return 是否为通路
 */
bool GameMap::isRoad(int x, int y) {
    int countWalls = 0;
    for (int i = 0; i < 4; i++) {
        if (mapData[x + dx[i]][y + dy[i]] == 1) {
            countWalls++;
        }
    }
    if (countWalls >= 3) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief 初始化地图
 * @param width 地图宽度
 * @param height 地图高度
 */
GameMap::GameMap(int width, int height) : width(width), height(height), mapData(width, QVector<int>(height)), Visited(width, QVector<bool>(height)) {
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            mapData[i][j] = 1;
        }
    }

    generatePerfectMaze(3, 3);

    for (i = 0; i < width; i++) {
        j = 0;
        mapData[i][j] = 1;
        j = height - 1;
        mapData[i][j] = 1;
    }

    for (i = 0; i < height; i++) {
        j = 0;
        mapData[j][i] = 1;
        j = width - 1;
        mapData[j][i] = 1;
    }

    mapData[32][19] = 0;

    breakWalls();

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (mapData[i][j] == 0) {
                mapData[i][j] = 2;
            }
        }
    }

    BeanRect.setWidth(8);
    BeanRect.setHeight(8);
}

/**
 * @brief DFS生成无环的完美迷宫
 * @param x 起始点的x坐标
 * @param y 起始点的y坐标
 */
void GameMap::generatePerfectMaze(int x, int y) {
    Visited[x][y] = true;
    vector<int> dirs = {0, 1, 2, 3};
    random_shuffle(dirs.begin(), dirs.end(), MyRand());
    /*调试用
     for (int i = 0; i < 4; i++) {
        cout << dirs[i] << " ";
    }
    cout << "\n\n";
    */
    for (int dir : dirs) {
        int nextX = x + dx[dir];
        int nextY = y + dy[dir];
        if (nextX > 0 && nextY > 0 && nextX < width - 1 && nextY < height - 1 && !Visited[nextX][nextY] && isRoad(nextX, nextY)) {
            mapData[x + dx[dir]][y + dy[dir]] = 0; // break the wall
            generatePerfectMaze(nextX, nextY);
        }
    }
}

/**
 * @brief 析构函数
 */
GameMap::~GameMap() {}

/**
 * @brief 打破墙壁，让完美迷宫变成有环图
 */
void GameMap::breakWalls() {
    int flag;
    for (int i = 1; i < width - 1; i++) {
        for (int j = 1; j < height - 1; j++) {
            flag = rand() % 100;
            if (flag % 3 == 0 && mapData[i][j] == 1) {
                mapData[i][j] = 2;
            }
        }
    }
}

/**
 * @brief 根据地图数据绘制墙壁和豆子
 * @param painter QPainter对象，用于绘制
 */
void GameMap::drawMap(QPainter &painter) {
    QBrush blue_brush(QColor("blue")); // 把刷子设置为白色
    QBrush green_brush(QColor("green"));

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            int mapElement = mapData[i][j];
            switch (mapElement) {
                case 0: // 空格
                    // 不绘制任何内容
                    break;
                case 1: // 墙壁
                    painter.setPen(QPen(Qt::blue, 30)); // 设置画笔形式
                    painter.setBrush(blue_brush);       // 应用刷子
                    painter.drawPoint(i * 30 + 30, j * 30 + 30);
                    // 绘制墙壁
                    break;
                case 2: // 豆子
                    painter.setPen(QPen(Qt::green, 13));
                    painter.setBrush(green_brush);
                    BeanRect.moveTo(30 * i + 30, 30 * j + 30);
                    painter.drawPie(BeanRect, 0, 360 * 16);
                    // 绘制豆子
                    break;
            }
        }
    }
}

/**
 * @brief 判断给定坐标是否碰撞墙壁
 * @param x x坐标
 * @param y y坐标
 * @return 是否碰撞墙壁
 */
bool GameMap::isCollision(int x, int y) {
    int tempX[4] = {10, 0, -10, 0};
    int tempY[4] = {0, 10, 0, -10};
    for (int k = 0; k < 4; k++) {
        if (mapData[(x + tempX[k]) / 30][(y + tempY[k]) / 30] == 1) {
            return true;
        }
    }
    return false;
}
