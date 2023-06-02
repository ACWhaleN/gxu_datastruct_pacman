#ifndef CONFIG_H
#define CONFIG_H
#include <QPixmap>
#include <QWidget>
#include <QPalette>

/*********游戏配置**********/
#define Game_width 2080      //画面宽度2080
#define Game_height  1080    //画面高度1080
#define Start_width 450     //画面宽度
#define Start_height 450     //画面高度
#define Game_title  "Pacman"     //游戏标题
#define Game_rate 4         //刷新速率（单位：ms）一秒50帧
#define Player_life 200     //玩家血量设定
//图标
#define img_path ":/material/Pacman.ico"
//背景音乐
#define BackMusic ":/material/backmusic.wav"
//玩家判定范围大小
#define player_width 28
#define player_height 28
//幽灵个数
#define ghost_count 4
//幽灵图片及判定范围大小
#define ghost_width 30
#define ghost_height 30
#define blue_up1_path ":/material/blue_up1.png"
#define blue_up2_path ":/material/blue_up2.png"
#define blue_left1_path ":/material/blue_left1.png"
#define blue_left2_path ":/material/blue_left2.png"
#define blue_down1_path ":/material/blue_down1.png"
#define blue_down2_path ":/material/blue_down2.png"
#define blue_right1_path ":/material/blue_right1.png"
#define blue_right2_path ":/material/blue_right2.png"
#define deadup_path ":/material/deadup.png"
#define deaddown_path ":/material/deaddown.png"
#define deadleft_path ":/material/deadleft.png"
#define deadright_path ":/material/deadright.png"
#define attackable1_path ":/material/attackable1.png"
#define attackable2_path ":/material/attackable2.png"
//豆子大小
#define beans_width 2
#define beans_height 2
//幽灵出生区域
#define EnStart_x 29
#define EnStart_y 14
#define EnStart_w 6
#define EnStart_h 4
//玩家出生区域
#define PacStart_x 31
#define PacStart_y 23
#define PacStart_w 3
#define PacStart_h 3

//玩家速度
#define player_speed 6
//敌人速度
#define enemy_speed 5
//玩家命数
#define initial_life 3
#endif // CONFIG_H
