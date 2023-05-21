#ifndef CONFIG_H
#define CONFIG_H
#include <QPixmap>
#include <gameinterface.h>
#include <QWidget>
#include <QPalette>

/*********游戏配置**********/
#define Game_width 2000     //画面宽度
#define Game_height 1200     //画面高度
#define Game_title  "Pacman"     //游戏标题
#define Game_rate 4         //刷新速率（单位：ms）一秒250帧
#define Player_life 200     //玩家血量设定
////图标
//#define img_path ":/material/sans.ico"
////背景音乐
//#define BackMusic ":/material/back_music.wav"
//背景图片
//#define back_path ":/material/back.png"
//玩家图片及判定范围大小
#define player_width 30
#define player_height 30
//玩家速度
#define player_speed 1
//敌人速度
#define enemy_speed 1
//玩家命数
#define initial_life 3
#endif // CONFIG_H
