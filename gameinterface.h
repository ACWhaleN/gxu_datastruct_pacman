#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "player.h"
#include "ghost.h"
#include "config.h"
#include <iostream>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QSound>

//避免移植出现乱码，声明编码方式
#pragma execution_character_set("utf-8")
class GameInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameInterface(QWidget *parent = nullptr);
    ~GameInterface();
    //函数
    //开始
    void StartToPlay();
    //初始化场景
    void initScene();
    //绘制函数(名称固定，不可修改)
    void paintEvent(QPaintEvent *);
    //更新各种参数
    void UpdateDetails();
    //键盘操作
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

public:
    //玩家
    player Pacman;
    //幽灵
    Ghost enemy[ghost_count];
    //计数器
    QTimer m_Timer;
    //游戏进程
    int Game_step = 0;
    //开局延时变量
    int StartTime = 0;
    int carry = 0;
    //特殊模式延时
    int AKDelay = 3000/Game_rate;
    //总分数
    int score = 0;
    //击杀幽灵分数
    int attackscore = 0;
    QPushButton* End_button = new QPushButton("返回开始界面");
    QLineEdit* ScoreText = new QLineEdit();
    //背景音乐
    QSound *backmusic;
public slots:
    //结束
    void GameOver();
};

#endif // GAMEINTERFACE_H
