#ifndef MONSTER_H
#define MONSTER_H
//怪物
#include"one.h"

#define ICE 1
#define THUNDER 2
#define FIRE 3
#define MAGIC 4
#define IRON 5
#define WEAK 6

//运算符重载 *  1为冰霜 2雷 3火 4魔 5钢铁 6隐形
//         +  对应属性攻击力
class Monster
{
public:

    Monster(int monsterId,double point,int Agile,int HP,int Max_HP,int Attack,int Defense,int Attack_Type,
    int Attack_Element,int Element_Attack0,int Element_Attack1,int Element_Attack2,int Element_Attack3,int Element_Attack4,
    float Resistance0,float Resistance1,float Resistance2,float Resistance3,float Resistance4,
    float Attack_Type_Resistance0,float Attack_Type_Resistance1,float Attack_Type_Resistance2,int painterX,int painterY);
    Monster();


    int getMonsterId() const;
    void setMonsterId(int value);

    double getPoint() const;
    void setPoint(double value);

    int getAgile() const;
    void setAgile(int value);

    float getHP() const;
    void setHP(float value);

    float getMax_HP() const;
    void setMax_HP(float value);

    float getAttack() const;
    void setAttack(float value);

    float getDefense() const;
    void setDefense(float value);

    int getAttack_Type() const;
    void setAttack_Type(int value);

    int getAttack_Element() const;
    void setAttack_Element(int value);

    float getElement_Attack(int i) const;
    void setElement_Attack(int i,float value);

    float getResistance(int i) const;
    void setResistance(int i,float value);

    float getAttack_Type_Resistance(int i) const;
    void setAttack_Type_Resistance(int i,float value);

    int getPainterX() const;
    void setPainterX(int value);

    int getPainterY() const;
    void setPainterY(int value);

private:
    int monsterId;//怪物ID
    int painterX;//在对应图像的位置
    int painterY;
    double point;//攻击和被他攻击一次可获得的点数

    //战斗属性
    int Agile;//敏捷
    float HP;//血量
    float Max_HP;
    float Attack;//攻击
    float Defense;//防御

    int Attack_Type;//攻击类型 1为斩击，2为钝击，3为刺击
    int Attack_Element;//攻击元素0为无 1为冰，2为雷，3火，4魔,对应Element_Attack下标
    float Element_Attack[5];//属性攻击力
    float Resistance[5];//属性抗性  //Res[0]为物抗
    float Attack_Type_Resistance[4];//1斩击抗性 2钝击抗性 3穿刺抗性
    //冰火相互克制，雷无属性克制但是自身血量相对较少，攻击较高， 魔属性高物理抗性低


public:
    //给模板参数值赋予元素特性，替代运算符重载
    virtual void getElement(int kind,int num);

    virtual void attack(One &one);

//    void operator * (const int kind)
//    {
//        //运算符重载 *  1为冰霜 2雷 3火 4魔 5钢铁 6隐形
//        switch (kind)
//        {
//        case ICE:
//            Attack_Element = 1;//攻击元素为冰
//            Resistance[1] =1;//冰抗拉满
//            Resistance[3] =0;//火炕归零
//            break;
//        case THUNDER://雷属性修正 血量防御*0.7  攻击*1.25
//            Attack_Element = 2;//攻击元素为雷
//            Resistance[2] =2;//雷抗拉满

//            HP*=0.7;
//            Defense*=0.7;
//            Attack*=1.25;
//            break;
//        case FIRE:
//            Attack_Element = 3;//攻击元素为火
//            Resistance[3] =1;//火抗拉满
//            Resistance[1] =0;//冰炕归零
//            break;
//        case MAGIC://物抗、攻击抗性-0.25，属性全+0.35
//            Attack_Element = 4;
//            Resistance[0]-=0.25;
//            Attack_Type_Resistance[1]-=0.25;
//            Attack_Type_Resistance[2]-=0.25;
//            Attack_Type_Resistance[3]-=0.25;

//            for(int i=1;i<=4;i++)
//            {
//                Resistance[i] +=0.35;
//            }
//            break;
//        case IRON: //钢铁 血量防御*2 雷抗-2 魔抗-1 物抗、攻击抗性+0.35
//            Attack_Element = 0;
//            HP*=2;
//            Defense*=2;
//            Resistance[2]-=2;
//            Resistance[4]-=1;

//            Resistance[0]+=0.35;
//            Attack_Type_Resistance[1]+=0.35;
//            Attack_Type_Resistance[2]+=0.35;
//            Attack_Type_Resistance[3]+=0.35;

//            break;
//        case WEAK://点数、攻击、防御*0.5，全抗性=0.2  //隐形 小化
//            point*=0.5;
//            Attack*=0.5;
//            Defense*=0.5;
//            Attack_Type_Resistance[1]=0.2;
//            Attack_Type_Resistance[2]=0.2;
//            Attack_Type_Resistance[3]=0.2;
//            for(int i=0;i<=4;i++)
//            {
//                Resistance[i]=0.2;
//            }
//            break;

//        }
//    }

//    void operator + (const int num)
//    {
//        //运算符重载 +  +对应属性攻击力
//        Element_Attack[Attack_Element]+=num;
//    }

};

//[100,110)
class MonsterSlime :public Monster
{
public:
    MonsterSlime();
    //完整参数版
    MonsterSlime(int monsterId,double point,int Agile,int HP,int Max_HP,int Attack,int Defense,int Attack_Type,
    int Attack_Element,int Element_Attack0,int Element_Attack1,int Element_Attack2,int Element_Attack3,int Element_Attack4,
    float Resistance0,float Resistance1,float Resistance2,float Resistance3,float Resistance4,
    float Attack_Type_Resistance0,float Attack_Type_Resistance1,float Attack_Type_Resistance2,int painterX,int painterY);
    //简化参数版
    MonsterSlime(int monsterId,double point,int Attack_Type,int painterX,int painterY);
    //
    void slimeNet();
};

//[110,120)
class MonsterBat :public Monster
{
public:
    MonsterBat();
    //完整参数版
    MonsterBat(int monsterId,double point,int Agile,int HP,int Max_HP,int Attack,int Defense,int Attack_Type,
    int Attack_Element,int Element_Attack0,int Element_Attack1,int Element_Attack2,int Element_Attack3,int Element_Attack4,
    float Resistance0,float Resistance1,float Resistance2,float Resistance3,float Resistance4,
    float Attack_Type_Resistance0,float Attack_Type_Resistance1,float Attack_Type_Resistance2,int painterX,int painterY);
    //简化参数版
    MonsterBat(int monsterId,double point,int painterX,int painterY);
    void batNet();
    //
};

//[120,130)
class MonsterSkeleton : public Monster
{
public:
    MonsterSkeleton();
    //完整参数版
    MonsterSkeleton(int monsterId,double point,int Agile,int HP,int Max_HP,int Attack,int Defense,int Attack_Type,
    int Attack_Element,int Element_Attack0,int Element_Attack1,int Element_Attack2,int Element_Attack3,int Element_Attack4,
    float Resistance0,float Resistance1,float Resistance2,float Resistance3,float Resistance4,
    float Attack_Type_Resistance0,float Attack_Type_Resistance1,float Attack_Type_Resistance2,int painterX,int painterY);
    //简化参数版
    //with Sword
    MonsterSkeleton(int monsterId,double point,int Attack_Type,int painterX,int painterY);
    //no Sword
    MonsterSkeleton(int monsterId,double point,int painterX,int painterY);
};
//[130,140) 兽人，有个怒气值，满值100%，攻击力按百分比加成
class MonsterOrcish : public Monster
{
public:
    MonsterOrcish();
    //完整参数版
    MonsterOrcish(int monsterId,double point,int Agile,int HP,int Max_HP,int Attack,int Defense,int Attack_Type,
    int Attack_Element,int Element_Attack0,int Element_Attack1,int Element_Attack2,int Element_Attack3,int Element_Attack4,
    float Resistance0,float Resistance1,float Resistance2,float Resistance3,float Resistance4,
    float Attack_Type_Resistance0,float Attack_Type_Resistance1,float Attack_Type_Resistance2,int painterX,int painterY);
    //简化参数版
    //with Sword
    MonsterOrcish(int monsterId,double point,int Attack_Type,int painterX,int painterY);
    //no Sword
    MonsterOrcish(int monsterId,double point,int painterX,int painterY);
    void getAnger();
    double getAngerNum() const;
    void setAngerNum(double value);

private:
    double angerNum;
};

//[140,150)
class MonsterMagicer :public Monster
{
public:
    MonsterMagicer();
    //简化参数版
    MonsterMagicer(int monsterId,double point,int painterX,int painterY);
};




class MonsterElementStone : public Monster
{
public:
    MonsterElementStone();
    //完整参数版
    MonsterElementStone(int monsterId,double point,int Agile,int HP,int Max_HP,int Attack,int Defense,int Attack_Type,
    int Attack_Element,int Element_Attack0,int Element_Attack1,int Element_Attack2,int Element_Attack3,int Element_Attack4,
    float Resistance0,float Resistance1,float Resistance2,float Resistance3,float Resistance4,
    float Attack_Type_Resistance0,float Attack_Type_Resistance1,float Attack_Type_Resistance2,int painterX,int painterY);
    //简化参数版
    MonsterElementStone(int monsterId,double point,int painterX,int painterY);
    void getDefenseAdd();
    double getDefenseNum() const;
    void setDefenseNum(double value);

private:
    double defenseNum;
};


class MonsterCrusadeKnight :public Monster
{
public:
    MonsterCrusadeKnight();

    MonsterCrusadeKnight(int monsterId,double point,int painterX,int painterY);

    void attack(One &one) override;
};

class MonsterMatrixKnight :public Monster
{
public:
    MonsterMatrixKnight();

    MonsterMatrixKnight(int monsterId,double point,int painterX,int painterY);
    void iAmMatrix();
};


class MonsterSwordMan :public Monster
{
public:
    MonsterSwordMan();

    MonsterSwordMan(int monsterId,double point,int color,int painterX,int painterY);

    void attack(One &one) override;
};



#endif // MONSTER_H



