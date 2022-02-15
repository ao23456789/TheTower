#ifndef ONE_UI_H
#define ONE_UI_H
#include <QKeyEvent>
#include "tower.h"
#include <QDialog>
#include "one.h"
#include <QPainter>

#define oneui_Xoffset 420
#define oneui_Yoffset 66

namespace Ui {
class One_ui;
}

class One_ui : public QDialog
{
    Q_OBJECT

public:
    explicit One_ui(QWidget *parent = nullptr);
    ~One_ui();
    QString str0;



    void setTreasures(int num[5][2]);
    void buttonIsAble();


    //键盘事件
     void keyPressEvent(QKeyEvent *event);
     //图像绘制
    void paintEvent(QPaintEvent *);
private:
    Ui::One_ui *ui;
    Tower *tower;
    One oneTemp;
    float hp,attack,defense;
    int lv,lvPoint;
    double point;
    int agile;
    float attackTypeResistance[4];//1斩击抗性2钝击抗性3穿刺抗性
    float elementAttack[5];//属性攻击力 无冰雷火魔
    float resistance[5];//属性抗性


    int treasures[5][2];
    int treasuresUi;

signals:
    void oneSendData(One);
    void oneSendTreasure(int);

public slots:
   void oneuiRecvData(One one);

private slots:
   void on_buttonLv_clicked();
   void on_buttonAttcak_clicked();
   void on_buttonDefense_clicked();
   void on_buttonMaxHp_clicked();
   void on_buttonAgile_clicked();
   void on_buttonAttackTypeResistance0_clicked();
   void on_buttonAttackTypeResistance1_clicked();
   void on_buttonAttackTypeResistance2_clicked();
   void on_buttonAttack0_clicked();
   void on_buttonAttack1_clicked();
   void on_buttonAttack2_clicked();
   void on_buttonAttack3_clicked();
   void on_buttonResistance0_clicked();
   void on_buttonResistance1_clicked();
   void on_buttonResistance2_clicked();
   void on_buttonResistance3_clicked();
   void on_buttonSure_clicked();
};

#endif // ONE_UI_H
