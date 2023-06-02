#include "startinterface.h"
#include "config.h"

#include<QPainter>
#include<QApplication>
/**
 * @brief StartInterface类的构造函数
 * @param parent 父窗口指针
 */
StartInterface::StartInterface(QWidget *parent) :
    QMainWindow(parent)
{
    //初始化场景
    initScene();
}
/**
 * @brief 析构函数
 */
StartInterface::~StartInterface()
{
    delete this;
}
/**
 * @brief 界面初始化设置
 */
void StartInterface::initScene()
{
    //设置窗口的固定大小
    setFixedSize(Start_width, Start_height);
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
    //设置窗口标题
    setWindowTitle(Game_title);
    //设置图标
    setWindowIcon(QIcon(img_path));
    //按钮样式设置
    //设当前窗体为控件父窗体
    Start_button->setParent(this);
    Start_button->setFlat(true);
    Start_button->setStyleSheet(
                "QPushButton{"                          // 正常状态样式
                "background-color: transparent;"        // 背景设为透明
                "color: white;"                         // 字体颜色
                "font: bold 45px;"                      // 字体: 加粗 大小
                "border:4px solid gray;"
                "border-radius:10px;"
                "}"
               "QPushButton:hover{border:4px solid white}");
    Start_button->setFixedSize(350,60);
    Start_button->setGeometry((Start_width-350)/2,Start_height/2-80,350,60);
    Start_button->adjustSize();
    //将切换页面的槽函数点击事件进行连接
    QObject::connect(Start_button,SIGNAL(clicked()),this,SLOT(change()));
    //设当前窗体为控件父窗体
    Quit_button->setParent(this);
    Quit_button->setFlat(true);
    Quit_button->setStyleSheet(
                "QPushButton{"                          // 正常状态样式
                "background-color: transparent;"        // 背景设为透明
                "color: white;"                         // 字体颜色
                "font: bold 50px;"                      // 字体: 加粗 大小
                "border:4px solid gray;"
                "border-radius:10px;"
                "}"
               "QPushButton:hover{border:4px solid white}");
    Quit_button->setFixedSize(350,60);
    Quit_button->setGeometry((Start_width-350)/2,Start_height/2+20,350,60);
    Quit_button->adjustSize();
    //按下按钮退出页面
    QObject::connect(Quit_button,&QPushButton::clicked,this,&QWidget::close);
//    绘制函数(名称固定，不可修改)
    void paintEvent(QPaintEvent *);
}

/**
 * @brief 界面切换槽函数
 */
void StartInterface::change()
{
    GameWindow.show();
    this->close();
}
