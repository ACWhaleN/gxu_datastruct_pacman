#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "player.h"

#include<iostream>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QMainWindow>

using namespace std;

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
    //计数器
    QTimer m_Timer;
    //游戏进程
    int Game_step = 0;
    //开局延时变量
    int StartTime = 0;

};

#endif // GAMEINTERFACE_H
