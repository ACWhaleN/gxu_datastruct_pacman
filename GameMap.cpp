#include"GameMap.h"


bool GameMap::isRoad(int x,int y){
    int countWalls=0;
    for(int i=0;i<4;i++){
        if(mapData[x + dx[i]][y + dy[i]] == 1)countWalls++;
    }
    if(countWalls>=3)return 1;
    else return 0;
}
/**
 * @brief GameMap class constructor.
 *
 * Initializes the game map with a given width and height, and sets up the map data.
 *
 * @param width Width of the game map.
 * @param height Height of the game map.
 */
GameMap::GameMap(int width, int height) : width(width), height(height), mapData(width, QVector<int>(height)), Visited(width, QVector<bool>(height)) {
    int i, j;
    for(i = 0; i < width; i++)for(j = 0; j < height; j++)mapData[i][j] = 1;

    generatePerfectMaze(3,3);
    for(i = 0; i < width; i++){
        j = 0;
        mapData[i][j] = 1;
        j = height-1;
        mapData[i][j] = 1;
    }
    for(i = 0; i < height; i++){
        j = 0;
        mapData[j][i] = 1;
        j = width-1;
        mapData[j][i] = 1;
    }

    for(i=0;i<width;i++)for(j=0;j<height;j++)if(mapData[i][j]==0){if(i%4==0&&j%4==0)mapData[i][j]=2;}
    BeanRect.setWidth(8);
    BeanRect.setHeight(8);
}
void GameMap::generatePerfectMaze(int x, int y){
        for(int k=0;k<10;k++)for(int g=0; g<10;g++)cout<<Visited[k][g]<<" ";
        int h;

        Visited[x][y] = true;
        vector<int> dirs = {0, 1, 2, 3};
        random_shuffle(dirs.begin(), dirs.end(), MyRand());
        for (int dir : dirs) {
            int nextX = x + dx[dir];
            int nextY = y + dy[dir];
            if (nextX > 0 && nextY > 0 && nextX < width-1 && nextY < height-1 && !Visited[nextX][nextY]&&isRoad(nextX,nextY)) {
                mapData[x + dx[dir]][y + dy[dir]] = 0; // break the wall
                generatePerfectMaze(nextX, nextY);
            }
        }
    }
GameMap::~GameMap(){}

void GameMap::drawMap(QPainter &painter) {

    //设置画笔形式
    //std::cout<<"\n\n\n";
    QBrush white_brush( QColor("white") );       //把刷子设置为白色
    QBrush green_brush( QColor("green") );

    for (int j = 0; j < height; ++j) {

        for (int i = 0; i < width; ++i) {
            int mapElement = mapData[i][j];
            //std::cout<<mapElement<<" ";
            //if(i==width-1)std::cout<<"\n";
            switch (mapElement) {
                case 0: // 空格
                    // 不绘制任何内容
                    break;
                case 1: // 墙壁
                painter.setPen(QPen(Qt::white,30));//设置画笔形式
                painter.setBrush(white_brush);                //应用刷子
                painter.drawPoint(i*30+30,j*30+30);
                    // 绘制墙壁
                    break;
                case 2: // 豆子
                painter.setPen(QPen(Qt::green,13));
                painter.setBrush(green_brush);
                BeanRect.moveTo(30*i+15,30*j+15);
                painter.drawPie(BeanRect,0,360*16);
                    // 绘制豆子
                    break;
            }
        }
    }
}


bool GameMap::isCollision(int x, int y) {

    // 如果地图元素是墙壁，则返回true，表示发生碰撞
    int tempX[4]={16,0,-16,0};
    int tempY[4]={0,16,0,-16};
    for(int k=0;k<4;k++){
        if (mapData[(x+tempX[k])/30][(y+tempY[k])/30] == 1) {
        return true;
    }}

    // 否则返回false，表示没有碰撞
    return false;
}
