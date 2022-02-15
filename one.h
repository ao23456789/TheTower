#ifndef ONE_H
#define ONE_H
#include "position.h"
#include <QDebug>


#define NET 90
#define KETTLE 91
#define NOTE 92
#define CROSS 93
#define COIN 90



class One
{
public:
    One();
public:

    void setPosition(Position position)
    {
        this->position = position;
    }
    Position getPosition()
    {
        return position;
    }



    //位置属性
    Position position;// 猪脚当前位置
    int One_Direction;//主角面朝方向 0上，1下，2左，3右

    int treasure;//所装备的东西
    int treasures[5][2];

    //所持有钥匙数量
    int key[4];//0黄钥匙 1蓝钥匙  2红钥匙 3绿钥匙

    //人物属性
    //满级50，每级
    int LV;//等级
    int lvPoint;//等级点数
    double point;//点数，既是货币，也是经验

    //战斗属性
    int Agile;//敏捷  1-9雷电系的敏捷高，钢铁系的敏捷低
    float HP;//血量
    float Max_HP;//最大血量
    float Attack;//攻击
    float Defense;//防御
    int Attack_Type;//攻击类型 1为斩击，2为钝击，3为刺击
    int Attack_Element;//攻击元素 1为冰，2为雷，3火，4魔

    float Attack_Type_Resistance[4];//1斩击抗性2钝击抗性3穿刺抗性
    float Element_Attack[5];//属性攻击力 无冰雷火魔
    float Resistance[5];//属性抗性


    //杂项属性
    double exBuff;//经验Buff
    bool haveCoin;
    bool backAttack;//从背后攻击
    int whatsYourEnd;//1鲨鹿 2宽恕 3购物 4跑路 5变精灵 6杀精灵
    bool isElf;//是否变精灵
    bool withPrincess;//是否跟着个公主

    void getReward(double num);//每次攻击获得奖励
    void initOne();//主角初始化
    bool getFragment();



};

#endif // ONE_H
