//主框架，可以调用所有类的东西，把需要使用到多个类的方法写到这里面
//一直直走就能通关

#ifndef TOWER_H
#define TOWER_H

#include <QPainter>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include "position.h"
#include "one.h"
#include "Monster.h"
#include "map.h"
#include "suduku.h"
#include "mine.h"
#include <QMessageBox>
#include "dialogelf.h"
#include "dialogmerchant.h"
#include "dialogprincess.h"
#include "note.h"

#define HEIGHT 33
#define WIDTH 33

namespace Ui {
    class Tower;
}

class Tower : public QWidget
{
    Q_OBJECT
public:
    One one;
    Map map;
public:
    //最近一个战斗的怪物，只显示血量、攻击和防御
     int monsterLatest;
     int monsterLatestPainterX;
     int monsterLatestPainterY;
     int monsterLatestHp;
     int monsterLatestAttack;
     int monsterLatestDefense;

    //游戏初始化
    void gameInit();
    void gameDead();
    //键盘事件
     void keyPressEvent(QKeyEvent *event);
      //图像绘制
     void paintEvent(QPaintEvent *);

     //移动
     void move(int direction);//0为上，1为下，2为左，3为右
     void moveEventAttack(int layler,int x,int y);
     void moveEventAttackWithMonster(Monster *monster,Position p);

     bool isMonster(Position p);
     bool isMonster(int layler,int x,int y);
     int isWhatKindMonster(Position p);
     int isWhatKindMonster(int layler,int x,int y);


     //物品效果
     void treasure();//宝物汇总
     void net(Position p);
     void kettle(Position p);
     //是SLIME返1  BAT返2
     int isSlimeOrBat(Position p);
     void pourWater(int treasureNum);
     Monster* getMonster(int layler,int x,int y);
     void aloneElf();
     bool getYNtreasures();


     void moveEvent60(int layler,int x,int y);//根据移动的目标位置发送事件
     void monsterDie(Monster *monster,Position pos);


     void acttack(Monster *monster);//攻击

     //地图方格的起始位置偏移
     int map_XOffset = 300;
     int map_YOffset = 120;

     //事件
     bool eventList[50];
     void mapEvent();

     //地图固定效果
     //[170,180)矩阵骑士
     void existIsTruth();
     void weAreMatrix(Position p);
     void magicAttack(Position p);

     void npcEvent(int n);

     //上楼，为负数是下楼
     void floorChange(int num);

     //数独
     void mine();
     void openBlock(int x,int y);
     void mineFlag();
     int mines;
     bool gameEnd;

     void sudu();
     //判断楼梯是真是假
     void unReal(int i);
     int ans;



public:
    explicit Tower(QWidget *parent = nullptr);
    ~Tower();
private:
    Ui::Tower *ui;
    //7层扫雷地图  0为未曾翻开过  1为翻开了  2为插上了棋
    int mineFlagMap[9][9];
    DialogElf diaElf;
    DialogMerchant diaMer;
    DialogPrincess diaPri;
    int  merchantCost[5];
    bool haveCross;


signals:
    void oneuiSendData(One);
    void noteSendData(Monster *);
public slots:
   void oneRecvData(One one1);
   void oneRecvTreasure(int num);
   void recuoerate(int num);//精灵恢复血量
   void beDedicated(bool YN);
   void buy(int num);//商人事件
   void withPri(bool YN);
};


#endif // TOWER_H
