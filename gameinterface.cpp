#include "gameinterface.h"
#include "config.h"
#include "player.h"
#include "GameMap.h"
#include "ghost.h"
#include "startinterface.h"
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QRect>
extern GameMap globalGameMap;

/**
 * @brief GameInterface类的构造函数
 * @param parent 父窗口指针
 */
GameInterface::GameInterface(QWidget *parent) :
    QMainWindow(parent)
{
    //初始化场景
    initScene();
    //开始游戏
    StartToPlay();
}

/**
 * @brief GameInterface类的析构函数
 */
GameInterface::~GameInterface()
{
    delete this;
}

/**
 * @brief 初始化游戏场景
 */
void GameInterface::initScene()
{
    //设置窗口的固定大小
    setFixedSize(Game_width, Game_height);
    //设置窗口标题
    setWindowTitle(Game_title);
    //设置图标
    setWindowIcon(QIcon(img_path));
    //窗体背景色
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
    //设置背景音乐
//    backmusic = new QSound(BackMusic,this);
    //设置退出按钮
    End_button->setParent(this);
    End_button->setFlat(true);
    End_button->setStyleSheet(
        "QPushButton{"                          // 正常状态样式
        "background-color: transparent;"        // 背景设为透明
        "color: white;"                         // 字体颜色
        "font: bold 45px;"                      // 字体: 加粗 大小
        "border:4px solid gray;"
        "border-radius:10px;"
        "}"
        "QPushButton:hover{border:4px solid white}");
    End_button->setFixedSize(350,60);
    End_button->setGeometry((Game_width-350)/2,Game_height/3*2,350,60);
    End_button->adjustSize();
    //将切换页面的槽函数点击事件进行连接
    QObject::connect(End_button,SIGNAL(clicked()),this,SLOT(GameOver()));
    //隐藏退出按钮
    End_button->hide();

    //设置分数结算显示
    ScoreText->setParent(this);
    ScoreText->setGeometry(1960,100,280,40);
    ScoreText->setEnabled(false);
    ScoreText->setStyleSheet(
        "QLineEdit{"                          // 正常状态样式
        "background-color: transparent;"        // 背景设为透明
        "color: white;"                         // 字体颜色
        "font: bold 45px;"                      // 字体: 加粗 大小
        "border:0px;"                       // 无边框
        "}");
    //敌人初始化
    for(int i=0;i<ghost_count;i++)
    {
        enemy[i].Set(0);
        enemy[i].Delay = 120/ Game_rate * i; //设置启动时延

    }
    //绘制函数(名称固定，不可修改)
    void paintEvent(QPaintEvent *);
    //配置计时器的刷新间隔
    m_Timer.setInterval(Game_rate);
}

/**
 * @brief 开始游戏
 */
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

/**
 * @brief 键盘按下事件处理函数
 * @param ev 键盘事件对象
 */
void GameInterface::keyPressEvent(QKeyEvent *ev)
{
    if(Game_step == 1)
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
        GameOver();
}

/**
 * @brief 键盘释放事件处理函数
 * @param ev 键盘事件对象
 */
void GameInterface::keyReleaseEvent(QKeyEvent *ev)
{
    //释放储存的按键（UD,LR中的值），可以及时“刹车”
    if(ev->key() == Qt::Key_W || ev->key() == Qt::Key_S)
        Pacman.UD = 0;
    if(ev->key() == Qt::Key_A || ev->key() == Qt::Key_D)
        Pacman.LR = 0;
}

/**
 * @brief 更新游戏中的各种数据
 */
void GameInterface::UpdateDetails()
{
    //刷新分数
    ScoreText->setText(QString::number(score));
    if(Game_step == 1)
    {
        Pacman.Update();    //玩家数据更新
        for(int i=0; i<ghost_count; i++)
        {
            if(enemy[i].Delay > 0)
                enemy[i].Delay--;
            enemy[i].Update(Pacman.x,Pacman.y);  //敌人数据更新
            if(enemy[i].Mrect.intersects(Pacman.player_rect) && !Pacman.invincible)
            {
                Pacman.life--;
                Pacman.invincible = true;
            }
        }
        // 编号相邻的敌人不走相同的路
        for(int i=1; i<ghost_count-1; i+=2)
        {
            if(enemy[i].mark)
            {
                enemy[i].mark = false;
                globalGameMap.reAMap();
            }
        }
    }
    if(Game_step == 2)
    {
        score = globalGameMap.BeanScore;
        ScoreText->setGeometry(Game_width/2+100,Game_height/3,350,60);
        End_button->show();
//        backmusic->stop();
        m_Timer.stop();

    }
}

/**
 * @brief 绘制游戏界面
 * @param event 绘制事件对象
 */
void GameInterface::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush yellow_brush( QColor("yellow") );       //把刷子设置为黄色
    painter.setBrush(yellow_brush);                //应用刷子
    //绘制
    globalGameMap.drawMap(painter);
    //开局倒计时的绘制
    if(Game_step == 0)
    {
        QFont font1("隶书",40,QFont::Bold);
        painter.setFont(font1);
        painter.setPen(Qt::white);
        //显示倒计时
        if(StartTime <= 200/Game_rate)
            painter.drawText(Game_width/2-100,Game_height/2-50,"Ready!");
        else
        {
            Game_step++;
            //播放音乐
//            backmusic->play();
        }
        StartTime++;
    }
    if(Game_step != 2)
    {
        QBrush yellow_brush( QColor("yellow") );       //把刷子设置为黄色
        painter.setBrush(yellow_brush);                //应用刷子
        // 绘制剩余命数
        if(Pacman.life > 0){
            painter.drawPie(1960,20,30,30,225*16,270*16);
        }
        if(Pacman.life > 1){
            painter.drawPie(2000,20,30,30,225*16,270*16);
        }
        if(Pacman.life > 2){
            painter.drawPie(2040,20,30,30,225*16,270*16);
        }
        QFont font2("微软雅黑",20,QFont::Bold);
        painter.setFont(font2);
        painter.setPen(Qt::white);
        painter.drawText(1960,90,"Score:");
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
            if(Pacman.UD|Pacman.LR && Pacman.step>=50/Game_rate) //在行动过程中才会发生切换
            {
                Pacman.flag = 1;
                Pacman.step = 0;
            }
            Pacman.step++;
        }
        else
        {
            painter.drawPie(Pacman.player_rect,0,361*16);
            if(Pacman.step>50/Game_rate)
            {
                Pacman.flag = 0;
                Pacman.step = 0;
            }
            Pacman.step++;
        }
        for (int i=0; i<ghost_count; i++)
            painter.drawPixmap(enemy[i].x,enemy[i].y,enemy[i].ApCe[enemy[i].carry][enemy[i].flag]);
        if(Pacman.life<=0)
            Game_step++;
    }
    else
    {
        QFont font3("微软雅黑",30,QFont::Bold);
        painter.setFont(font3);
        painter.setPen(Qt::white);
        painter.drawText((Game_width)/2-300,Game_height/3+50,"Your Score:");
    }
}


void GameInterface::GameOver()
{
    StartInterface *StartScene = new StartInterface;
    StartScene->show();
    this->close();
}
