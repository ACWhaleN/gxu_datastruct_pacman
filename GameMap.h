#include <QVector>
#include <QPainter>
//#define DIMENSION2 65
class GameMap {
public:
    const int width;
    const int height;
    QRect BeanRect;
    QVector<QVector<int>> mapData;

    GameMap(int width, int height) : width(width), height(height), mapData(width, QVector<int>(height)) {
        int i, j;
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

    void loadMapData();
    void drawMap(QPainter &painter);
    bool isCollision(int x, int y);
};






