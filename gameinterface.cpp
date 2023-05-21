#include "gameinterface.h"
#include "config.h"
#include "player.h"
#include "GameMap.h"

#include <QTimer>

#include <QKeyEvent>

extern GameMap globalGameMap;

GameInterface::GameInterface(QWidget *parent) :
    QMainWindow(parent)
{
    //初始化场景
    initScene();
    //开始游戏
    StartToPlay();
}

GameInterface::~GameInterface()
{
    delete this;
}

void GameInterface::initScene()
{
    //设置窗口的固定大小
    setFixedSize(Game_width, Game_height);
    //设置窗口标题
    setWindowTitle(Game_title);
    //设置图标
    //    setWindowIcon(QIcon(img_path));
    //窗体背景色
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
    //绘制函数(名称固定，不可修改)
    void paintEvent(QPaintEvent *);
    //配置计时器的刷新间隔
    m_Timer.setInterval(Game_rate);
}

void GameInterface::StartToPlay()
{
    //定时器启动
    m_Timer.start();

    //监听对象坐标并绘制
    connect(&m_Timer,&QTimer::timeout,[=](){
        //更新各种参数
        UpdateDetails();
        //绘制图像
        update();
    });

}
//键盘操作
void GameInterface::keyPressEvent(QKeyEvent *ev)
{
    if(Game_step != 0)
    {
        //左右移动键盘读取
        if(ev->key() == Qt::Key_W)
        {
            Pacman.UD = -1;
            Pacman.LR = 0;
            Pacman.state = 1;
        }
        else if(ev->key() == Qt::Key_S)
        {
            Pacman.UD = 1;
            Pacman.LR = 0;
            Pacman.state = 2;
        }
        if(ev->key() == Qt::Key_A)
        {
            Pacman.UD = 0;
            Pacman.LR = -1;
            Pacman.state = 3;
        }
        else if(ev->key() == Qt::Key_D)
        {
            Pacman.UD = 0;
            Pacman.LR = 1;
            Pacman.state = 4;
        }
    }
    //按空格返回开始界面
    if(Pacman.life<=0&&ev->key() == Qt::Key_Space)
        this->close();
    //按ESC结束游戏
    if(ev->key() == Qt::Key_Escape)
        this->close();

}
void GameInterface::keyReleaseEvent(QKeyEvent *ev)
{
    //释放储存的按键（UD,LR中的值），可以及时“刹车”
    if(ev->key() == Qt::Key_W || ev->key() == Qt::Key_S)
        Pacman.UD = 0;
    if(ev->key() == Qt::Key_A || ev->key() == Qt::Key_D)
        Pacman.LR = 0;
}
void GameInterface::UpdateDetails()
{
    Pacman.Update();    //玩家数据更新
}

void GameInterface::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //绘制
    if(Pacman.life>0)
    {
//        GameMap.MapCreate(GameMap.SpotMatrix);
        globalGameMap.drawMap(painter);
    }

    if(Pacman.life>0)
    {
        painter.setPen(QPen(Qt::yellow,2));//设置画笔形式
        QBrush yellow_brush( QColor("yellow") );       //把刷子设置为黄色
        painter.setBrush(yellow_brush);                //应用刷子
        if(Pacman.flag == 0)
        {
            switch (Pacman.state)
            {
            case 1:painter.drawPie(Pacman.player_rect,135*16,270*16);break; //朝上
            case 2:painter.drawPie(Pacman.player_rect,315*16,270*16);break; //朝下
            case 3:painter.drawPie(Pacman.player_rect,225*16,270*16);break; //朝左
            case 4:painter.drawPie(Pacman.player_rect,45*16,270*16);break;  //朝右
            default:painter.drawPie(Pacman.player_rect,0,360*16);
            }
            if(Pacman.UD|Pacman.LR && Pacman.step>250/Game_rate) //在行动过程中才会发生切换
            {
                Pacman.flag = 1;
                Pacman.step = 0;
            }
            Pacman.step++;
        }
        else
        {
            painter.drawPie(Pacman.player_rect,0,360*16);
            if(Pacman.step>250/Game_rate)
            {
                Pacman.flag = 0;
                Pacman.step = 0;
            }
            Pacman.step++;
        }
    }
    //开局倒计时的绘制
    if(Game_step == 0)
    {
        QFont font1("隶书",40,QFont::Bold);
        painter.setFont(font1);
        painter.setPen(Qt::white);
        //显示倒计时
        if(StartTime <= 1000/Game_rate)
            painter.drawText(Game_width/3,Game_height/2,"Ready！");
        else
            Game_step++;
        StartTime++;
    }
}



player::player()
{
    //出生坐标
    x = (Game_width - player_width)/2;
    y = (Game_height - player_height)/2;
    UD=LR = 0;  //初始为静止状态
    speed = player_speed;      //速度设定
    life = initial_life;     //血量设定
    flag = step = 0;
    state = 0;
    //受击体积设定
    player_rect.setWidth(player_width);
    player_rect.setHeight(player_height);
    player_rect.moveTo(x,y);
}

void player::Update()
{
    int NewY=y+speed*UD;  //上下
    int NewX=x+speed*LR;  //左右
    printf("%d %d\n",x,y);
    if (!globalGameMap.isCollision(NewX, NewY)) {
            // 如果没有碰撞，更新位置
        cout<<"x:  "<<NewX/30<<" y:  "<<NewY/30<<endl;
            x = NewX;
            y = NewY;
        }
    int tempX[4]={6,0,-6,0};
    int tempY[4]={0,6,0,-6};
    for(int k=0;k<4;k++)
        if (globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30] == 2)
            globalGameMap.mapData[(x+tempX[k])/30][(y+tempY[k])/30]=0;
    player_rect.moveTo(x,y);
}

