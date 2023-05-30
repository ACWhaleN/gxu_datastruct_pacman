#ifndef STARTINTERFACE_H
#define STARTINTERFACE_H

#include "gameinterface.h"
#include <QMainWindow>
#include <QPushButton>
//避免移植出现乱码，声明编码方式
#pragma execution_character_set("utf-8")

class StartInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartInterface(QWidget *parent = nullptr);
    ~StartInterface();
    //初始化场景
    void initScene();
    //绘制函数
    void paintEvent(QPaintEvent *);
    //用于界面切换的游戏界面类
    GameInterface GameWindow;
    QPushButton* Start_button = new QPushButton("开始游戏");
    QPushButton* Quit_button = new QPushButton("退出游戏");
public slots:
    //界面跳转
    void change();
};

#endif // STARTINTERFACE_H
