#include "Monster.h"



Monster::Monster(int monsterId, double point, int Agile, int HP, int Max_HP, int Attack, int Defense, int Attack_Type,
                 int Attack_Element, int Element_Attack0,int Element_Attack1,int Element_Attack2,int Element_Attack3,
                 int Element_Attack4, float Resistance0, float Resistance1,float Resistance2,float Resistance3,float Resistance4,
                 float Attack_Type_Resistance0, float Attack_Type_Resistance1,float Attack_Type_Resistance2,int painterX,int painterY)
{
    this->monsterId =monsterId;
    this->Agile= Agile;
    this->point =point;
    this->HP =HP;
    this->Max_HP =Max_HP;
    this->Attack=Attack;
    this->Defense=Defense;
    this->Attack_Type=Attack_Type;
    this->Attack_Element=Attack_Element;
    this->Element_Attack[0]=Element_Attack0;
    this->Element_Attack[1]=Element_Attack1;
    this->Element_Attack[2]=Element_Attack2;
    this->Element_Attack[3]=Element_Attack3;
    this->Element_Attack[4]=Element_Attack4;
    this->Resistance[0]=Resistance0;
    this->Resistance[1]=Resistance1;
    this->Resistance[2]=Resistance2;
    this->Resistance[3]=Resistance3;
    this->Resistance[4]=Resistance4;
    this->Attack_Type_Resistance[1] = Attack_Type_Resistance0;
    this->Attack_Type_Resistance[2] = Attack_Type_Resistance1;
    this->Attack_Type_Resistance[3] = Attack_Type_Resistance2;
    this->painterX = painterX;
    this->painterY = painterY;
}

Monster::Monster()
{
}

void Monster::attack(One &one)
{

    one.HP-=Attack * (1-one.Defense/(one.Defense+100)) * (1-one.Attack_Type_Resistance[Attack_Type]) * 0.5
            +Element_Attack[Attack_Element] * (1-one.Defense/(one.Defense+50)) * (1-one.Resistance[Attack_Element]) *0.5;
    one.getReward(point);
}



int Monster::getMonsterId() const
{
return monsterId;
}

void Monster::setMonsterId(int value)
{
monsterId = value;
}

double Monster::getPoint() const
{
return point;
}

void Monster::setPoint(double value)
{
point = value;
}

int Monster::getAgile() const
{
return Agile;
}

void Monster::setAgile(int value)
{
Agile = value;
}

float Monster::getHP() const
{
return HP;
}

void Monster::setHP(float value)
{
HP = value;
}

float Monster::getMax_HP() const
{
return Max_HP;
}

void Monster::setMax_HP(float value)
{
Max_HP = value;
}

float Monster::getAttack() const
{
return Attack;
}

void Monster::setAttack(float value)
{
Attack = value;
}

float Monster::getDefense() const
{
return Defense;
}

void Monster::setDefense(float value)
{
Defense = value;
}

int Monster::getAttack_Type() const
{
return Attack_Type;
}

void Monster::setAttack_Type(int value)
{
Attack_Type = value;
}

int Monster::getAttack_Element() const
{
return Attack_Element;
}

void Monster::setAttack_Element(int value)
{
Attack_Element = value;
}



//获得属性攻击力，01234 0攻击力，冰雷火魔
float Monster::getElement_Attack(int i) const
{
    return Element_Attack[i];
}
void Monster::setElement_Attack(int i,float value)
{
    Element_Attack[i] = value;
}
//获得属性抗性，01234 0防御力，冰雷火魔
float Monster::getResistance(int i) const
{
    return Resistance[i];
}
void Monster::setResistance(int i,float value)
{
    Resistance[i] = value;
}

float Monster::getAttack_Type_Resistance(int i) const
{
    return Attack_Type_Resistance[i];
}

void Monster::setAttack_Type_Resistance(int i,float value)
{
    Attack_Type_Resistance[i] = value;
}

int Monster::getPainterX() const
{
    return painterX;
}

void Monster::setPainterX(int value)
{
    painterX = value;
}

int Monster::getPainterY() const
{
    return painterY;
}

void Monster::setPainterY(int value)
{
    painterY = value;
}
//kind 为特性种类，num为所加的元素攻击力数值，如果kind为 5，6，num指定为0最好
void Monster::getElement(int kind,int num)
{
    if(kind>=5)
    {num=0;}
        //  1为冰霜 2雷 3火 4魔 5钢铁 6隐形
        switch (kind)
        {
        case ICE:
            Attack_Element = 1;//攻击元素为冰
            Resistance[1] =1;//冰抗拉满
            Resistance[3] =0;//火炕归零
            break;
        case THUNDER://雷属性修正 血量防御*0.7  攻击*1.25
            Agile+=5;
            Attack_Element = 2;//攻击元素为雷
            Resistance[2] =1;//雷抗拉满
            HP*=0.7;
            Defense*=0.7;
            Attack*=1.25;
            break;
        case FIRE:
            Attack_Element = 3;//攻击元素为火
            Resistance[3] =1;//火抗拉满
            Resistance[1] =0;//冰炕归零
            break;
        case MAGIC://物抗、攻击抗性-0.25，属性全+0.35
            Attack_Element = 4;
            Resistance[0]-=0.25;
            Attack_Type_Resistance[1]-=0.25;
            Attack_Type_Resistance[2]-=0.25;
            Attack_Type_Resistance[3]-=0.25;
            for(int i=1;i<=4;i++)
            {
                Resistance[i] +=0.35;
            }
            break;
        case IRON: //钢铁 血量防御*2 雷抗-2 魔抗-1 物抗、攻击抗性+0.35
            Attack_Element = 0;
            HP*=2;
            Defense*=2;
            Resistance[2]-=2;
            Resistance[4]-=1;
            Resistance[0]+=0.35;
            Attack_Type_Resistance[1]+=0.35;
            Attack_Type_Resistance[2]+=0.35;
            Attack_Type_Resistance[3]+=0.35;
            break;
        case WEAK://点数、攻击、防御*0.5，全抗性=0.2  //隐形 小化
            point*=0.5;
            Attack*=0.5;
            Defense*=0.5;
            Attack_Type_Resistance[1]=0.2;
            Attack_Type_Resistance[2]=0.2;
            Attack_Type_Resistance[3]=0.2;
            for(int i=0;i<=4;i++)
            {
                Resistance[i]=0.2;
            }
            break;
        }
         Element_Attack[Attack_Element]+=num;
}


//---------------------------------------------------MonsterSlime--------------------------------------------------

 MonsterSlime::MonsterSlime()
 {

 }

 MonsterSlime::MonsterSlime(int monsterId, double point, int Agile, int HP, int Max_HP, int Attack, int Defense,
                            int Attack_Type, int Attack_Element,
                            int Element_Attack0, int Element_Attack1, int Element_Attack2, int Element_Attack3,int Element_Attack4,
                            float Resistance0, float Resistance1, float Resistance2, float Resistance3, float Resistance4,
                            float Attack_Type_Resistance0, float Attack_Type_Resistance1, float Attack_Type_Resistance2,
                            int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(Agile);
     setHP(HP);
     setMax_HP(Max_HP);
     setAttack(Attack);
     setDefense(Defense);
     setAttack_Type(Attack_Type);
     setAttack_Element(Attack_Element);
     setElement_Attack(0,Element_Attack0);
     setElement_Attack(1,Element_Attack1);
     setElement_Attack(2,Element_Attack2);
     setElement_Attack(3,Element_Attack3);
     setElement_Attack(4,Element_Attack4);
     setResistance(0,Resistance0);
     setResistance(1,Resistance1);
     setResistance(2,Resistance2);
     setResistance(3,Resistance3);
     setResistance(4,Resistance4);
     setAttack_Type_Resistance(1,Attack_Type_Resistance0);
     setAttack_Type_Resistance(2,Attack_Type_Resistance1);
     setAttack_Type_Resistance(3,Attack_Type_Resistance2);
     setPainterX(painterX);
     setPainterY(painterY);
 }

 MonsterSlime::MonsterSlime(int monsterId, double point, int Attack_Type, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(1);
     setHP(200);
     setMax_HP(200);
     setAttack(30);
     setDefense(20);
     setAttack_Type(Attack_Type);
     setAttack_Element(0);
     setElement_Attack(0,30);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.35);
     setResistance(1,0.35);
     setResistance(2,0.35);
     setResistance(3,0.35);
     setResistance(4,0.35);
     setAttack_Type_Resistance(1,0.35);
     setAttack_Type_Resistance(2,0.65);
     setAttack_Type_Resistance(3,-0.25);
     setPainterX(painterX);
     setPainterY(painterY);
 }


 //---------------------------------------------------Monster骷髅--------------------------------------------------
 MonsterSkeleton::MonsterSkeleton()
 {

 }

 MonsterSkeleton::MonsterSkeleton(int monsterId, double point, int Agile, int HP, int Max_HP, int Attack, int Defense, int Attack_Type,
                                  int Attack_Element, int Element_Attack0, int Element_Attack1, int Element_Attack2, int Element_Attack3, int Element_Attack4,
                                  float Resistance0, float Resistance1, float Resistance2, float Resistance3, float Resistance4,
                                  float Attack_Type_Resistance0, float Attack_Type_Resistance1, float Attack_Type_Resistance2,
                                  int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(Agile);
     setHP(HP);
     setMax_HP(Max_HP);
     setAttack(Attack);
     setDefense(Defense);
     setAttack_Type(Attack_Type);
     setAttack_Element(Attack_Element);
     setElement_Attack(0,Element_Attack0);
     setElement_Attack(1,Element_Attack1);
     setElement_Attack(2,Element_Attack2);
     setElement_Attack(3,Element_Attack3);
     setElement_Attack(4,Element_Attack4);
     setResistance(0,Resistance0);
     setResistance(1,Resistance1);
     setResistance(2,Resistance2);
     setResistance(3,Resistance3);
     setResistance(4,Resistance4);
     setAttack_Type_Resistance(1,Attack_Type_Resistance0);
     setAttack_Type_Resistance(2,Attack_Type_Resistance1);
     setAttack_Type_Resistance(3,Attack_Type_Resistance2);
     setPainterX(painterX);
     setPainterY(painterY);
 }
 //不带剑的
 MonsterSkeleton::MonsterSkeleton(int monsterId, double point, int Attack_Type, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(2);
     setHP(300);
     setMax_HP(300);
     setAttack(50);
     setDefense(40);
     setAttack_Type(Attack_Type);
     setAttack_Element(0);
     setElement_Attack(0,50);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.35);
     setResistance(1,0.35);
     setResistance(2,0.35);
     setResistance(3,0.35);
     setResistance(4,0.35);
     setAttack_Type_Resistance(1,0.35);
     setAttack_Type_Resistance(2,-0.25);
     setAttack_Type_Resistance(3,0.65);
     setPainterX(painterX);
     setPainterY(painterY);
 }
 //拿剑的
 MonsterSkeleton::MonsterSkeleton(int monsterId, double point, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(3);
     setHP(400);
     setMax_HP(400);
     setAttack(60);
     setDefense(50);
     setAttack_Type(1);
     setAttack_Element(0);
     setElement_Attack(0,60);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.35);
     setResistance(1,0.35);
     setResistance(2,0.35);
     setResistance(3,0.35);
     setResistance(4,0.35);
     setAttack_Type_Resistance(1,0.35);
     setAttack_Type_Resistance(2,-0.25);
     setAttack_Type_Resistance(3,0.65);
     setPainterX(painterX);
     setPainterY(painterY);
 }
  //---------------------------------------------------Monster  bat--------------------------------------------------
 MonsterBat::MonsterBat()
 {

 }

 MonsterBat::MonsterBat(int monsterId, double point, int Agile, int HP, int Max_HP, int Attack, int Defense, int Attack_Type,
                        int Attack_Element, int Element_Attack0, int Element_Attack1, int Element_Attack2, int Element_Attack3, int Element_Attack4,
                        float Resistance0, float Resistance1, float Resistance2, float Resistance3, float Resistance4, float Attack_Type_Resistance0,
                        float Attack_Type_Resistance1, float Attack_Type_Resistance2, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(Agile);
     setHP(HP);
     setMax_HP(Max_HP);
     setAttack(Attack);
     setDefense(Defense);
     setAttack_Type(Attack_Type);
     setAttack_Element(Attack_Element);
     setElement_Attack(0,Element_Attack0);
     setElement_Attack(1,Element_Attack1);
     setElement_Attack(2,Element_Attack2);
     setElement_Attack(3,Element_Attack3);
     setElement_Attack(4,Element_Attack4);
     setResistance(0,Resistance0);
     setResistance(1,Resistance1);
     setResistance(2,Resistance2);
     setResistance(3,Resistance3);
     setResistance(4,Resistance4);
     setAttack_Type_Resistance(1,Attack_Type_Resistance0);
     setAttack_Type_Resistance(2,Attack_Type_Resistance1);
     setAttack_Type_Resistance(3,Attack_Type_Resistance2);
     setPainterX(painterX);
     setPainterY(painterY);
 }

 MonsterBat::MonsterBat(int monsterId, double point, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(2);
     setHP(300);
     setMax_HP(300);
     setAttack(40);
     setDefense(30);
     setAttack_Type(3);
     setAttack_Element(0);
     setElement_Attack(0,40);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.35);
     setResistance(1,0.35);
     setResistance(2,0.35);
     setResistance(3,0.35);
     setResistance(4,0.35);
     setAttack_Type_Resistance(1,0.25);
     setAttack_Type_Resistance(2,0.25);
     setAttack_Type_Resistance(3,0.25);
     setPainterX(painterX);
     setPainterY(painterY);
 }
 //---------------------------------------------------Monster  Orcish--------------------------------------------------
 MonsterOrcish::MonsterOrcish()
 {

 }

 MonsterOrcish::MonsterOrcish(int monsterId, double point, int Agile, int HP, int Max_HP, int Attack, int Defense, int Attack_Type,
                              int Attack_Element, int Element_Attack0, int Element_Attack1, int Element_Attack2, int Element_Attack3, int Element_Attack4,
                              float Resistance0, float Resistance1, float Resistance2, float Resistance3, float Resistance4,
                              float Attack_Type_Resistance0, float Attack_Type_Resistance1, float Attack_Type_Resistance2,
                              int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(Agile);
     setHP(HP);
     setMax_HP(Max_HP);
     setAttack(Attack);
     setDefense(Defense);
     setAttack_Type(Attack_Type);
     setAttack_Element(Attack_Element);
     setElement_Attack(0,Element_Attack0);
     setElement_Attack(1,Element_Attack1);
     setElement_Attack(2,Element_Attack2);
     setElement_Attack(3,Element_Attack3);
     setElement_Attack(4,Element_Attack4);
     setResistance(0,Resistance0);
     setResistance(1,Resistance1);
     setResistance(2,Resistance2);
     setResistance(3,Resistance3);
     setResistance(4,Resistance4);
     setAttack_Type_Resistance(1,Attack_Type_Resistance0);
     setAttack_Type_Resistance(2,Attack_Type_Resistance1);
     setAttack_Type_Resistance(3,Attack_Type_Resistance2);
     setPainterX(painterX);
     setPainterY(painterY);

     setAngerNum(0);//怒气值生成为0
 }
//有点怕火
 MonsterOrcish::MonsterOrcish(int monsterId, double point, int Attack_Type, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(6);
     setHP(400);
     setMax_HP(400);
     setAttack(80);
     setDefense(40);
     setAttack_Type(Attack_Type);
     setAttack_Element(0);
     setElement_Attack(0,80);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.35);
     setResistance(1,0.35);
     setResistance(2,0.35);
     setResistance(3,0.2);
     setResistance(4,0.35);
     setAttack_Type_Resistance(1,0.35);
     setAttack_Type_Resistance(2,0.35);
     setAttack_Type_Resistance(3,0.35);
     setPainterX(painterX);
     setPainterY(painterY);

     setAngerNum(0);
 }

 MonsterOrcish::MonsterOrcish(int monsterId, double point, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(6);
     setHP(550);
     setMax_HP(550);
     setAttack(100);
     setDefense(50);
     setAttack_Type(1);
     setAttack_Element(0);
     setElement_Attack(0,100);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.35);
     setResistance(1,0.35);
     setResistance(2,0.35);
     setResistance(3,0.2);
     setResistance(4,0.35);
     setAttack_Type_Resistance(1,0.35);
     setAttack_Type_Resistance(2,0.35);
     setAttack_Type_Resistance(3,0.35);
     setPainterX(painterX);
     setPainterY(painterY);

     setAngerNum(0);
 }

 void MonsterOrcish::getAnger()
 {
     angerNum =0.1;
     setAttack(getAttack() * (1+angerNum) );
 }

 double MonsterOrcish::getAngerNum() const
 {
     return angerNum;
 }

 void MonsterOrcish::setAngerNum(double value)
 {
     angerNum = value;
 }

  //---------------------------------------------------Monster  Magicer-----------------------------------------------------



 MonsterMagicer::MonsterMagicer()
 {

 }

 MonsterMagicer::MonsterMagicer(int monsterId, double point, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(2);
     setHP(400);
     setMax_HP(400);
     setAttack(60);
     setDefense(40);
     setAttack_Type(3);
     setAttack_Element(4);
     setElement_Attack(0,60);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,120);
     setResistance(0,0.65);
     setResistance(1,0.65);
     setResistance(2,0.65);
     setResistance(3,0.65);
     setResistance(4,0.65);
     setAttack_Type_Resistance(1,0.2);
     setAttack_Type_Resistance(2,0.2);
     setAttack_Type_Resistance(3,0.2);
     setPainterX(painterX);
     setPainterY(painterY);
 }




  //---------------------------------------------------Monster  ElementStone-----------------------------------------------------

 MonsterElementStone::MonsterElementStone()
 {

 }

 MonsterElementStone::MonsterElementStone(int monsterId, double point, int Agile, int HP, int Max_HP, int Attack, int Defense, int Attack_Type,
                                          int Attack_Element, int Element_Attack0, int Element_Attack1, int Element_Attack2, int Element_Attack3, int Element_Attack4,
                                          float Resistance0, float Resistance1, float Resistance2, float Resistance3, float Resistance4,
                                          float Attack_Type_Resistance0, float Attack_Type_Resistance1, float Attack_Type_Resistance2,
                                          int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(Agile);
     setHP(HP);
     setMax_HP(Max_HP);
     setAttack(Attack);
     setDefense(Defense);
     setAttack_Type(Attack_Type);
     setAttack_Element(Attack_Element);
     setElement_Attack(0,Element_Attack0);
     setElement_Attack(1,Element_Attack1);
     setElement_Attack(2,Element_Attack2);
     setElement_Attack(3,Element_Attack3);
     setElement_Attack(4,Element_Attack4);
     setResistance(0,Resistance0);
     setResistance(1,Resistance1);
     setResistance(2,Resistance2);
     setResistance(3,Resistance3);
     setResistance(4,Resistance4);
     setAttack_Type_Resistance(1,Attack_Type_Resistance0);
     setAttack_Type_Resistance(2,Attack_Type_Resistance1);
     setAttack_Type_Resistance(3,Attack_Type_Resistance2);
     setPainterX(painterX);
     setPainterY(painterY);

     setDefenseNum(0);
 }

 MonsterElementStone::MonsterElementStone(int monsterId, double point, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(2);
     setHP(700);
     setMax_HP(700);
     setAttack(60);
     setDefense(80);
     setAttack_Type(2);
     setAttack_Element(0);
     setElement_Attack(0,60);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.5);
     setResistance(1,0.5);
     setResistance(2,0.5);
     setResistance(3,0.5);
     setResistance(4,0.5);
     setAttack_Type_Resistance(1,0.5);
     setAttack_Type_Resistance(2,0.5);
     setAttack_Type_Resistance(3,0.5);
     setPainterX(painterX);
     setPainterY(painterY);

     setDefenseNum(0);
 }

 void MonsterElementStone::getDefenseAdd()
 {
     defenseNum=0.05;
     setDefense(getDefense() * (1+defenseNum) );
 }

 double MonsterElementStone::getDefenseNum() const
 {
     return defenseNum;
 }

 void MonsterElementStone::setDefenseNum(double value)
 {
     defenseNum = value;
 }





  //---------------------------------------------------MonsterCrusadeKnight-----------------------------------------------------




 MonsterCrusadeKnight::MonsterCrusadeKnight()
 {

 }

 MonsterCrusadeKnight::MonsterCrusadeKnight(int monsterId, double point, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(5);
     setHP(800);
     setMax_HP(800);
     setAttack(80);
     setDefense(80);
     setAttack_Type(3);
     setAttack_Element(0);
     setElement_Attack(0,80);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.35);
     setResistance(1,0.35);
     setResistance(2,0.35);
     setResistance(3,0.35);
     setResistance(4,0.35);
     setAttack_Type_Resistance(1,0.35);
     setAttack_Type_Resistance(2,0.35);
     setAttack_Type_Resistance(3,0.35);
     setPainterX(painterX);
     setPainterY(painterY);
 }
//无视一半护甲
 void MonsterCrusadeKnight::attack(One &one)
 {
     int defenseTemp = one.Defense/2;
     one.HP-=getAttack() * (1-defenseTemp/(defenseTemp+100)) * (1-one.Attack_Type_Resistance[getAttack_Type()]) * 0.5
             +getElement_Attack(getAttack_Element()) * (1-defenseTemp/(defenseTemp+50)) * (1-one.Resistance[getAttack_Element()]) *0.5;
     one.getReward(getPoint());
 }




  //---------------------------------------------------MonsterMatrixKnight-----------------------------------------------------
 MonsterMatrixKnight::MonsterMatrixKnight()
 {

 }

 MonsterMatrixKnight::MonsterMatrixKnight(int monsterId, double point, int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(5);
     setHP(1000);
     setMax_HP(1000);
     setAttack(100);
     setDefense(100);
     setAttack_Type(1);
     setAttack_Element(0);
     setElement_Attack(0,100);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.35);
     setResistance(1,0.35);
     setResistance(2,0.35);
     setResistance(3,0.35);
     setResistance(4,0.35);
     setAttack_Type_Resistance(1,0.35);
     setAttack_Type_Resistance(2,0.35);
     setAttack_Type_Resistance(3,0.35);
     setPainterX(painterX);
     setPainterY(painterY);
 }

//周围每有一个矩阵骑士就触发一次
 //血量、攻击、防御都会*1.25，多次触发会很猛
 void MonsterMatrixKnight::iAmMatrix()
 {
    setHP(getHP()*1.25);
    setAttack(getAttack()*1.25);
    setDefense(getDefense()*1.25);
 }


  //---------------------------------------------------MonsterSwordMan-----------------------------------------------------


 MonsterSwordMan::MonsterSwordMan()
 {

 }
 //color  冰雷火魔 1234 对应的抗性拉满
 MonsterSwordMan::MonsterSwordMan(int monsterId, double point, int color,int painterX, int painterY)
 {
     setMonsterId(monsterId);
     setPoint(point);
     setAgile(8);
     setHP(500);
     setMax_HP(500);
     setAttack(150);
     setDefense(20);
     setAttack_Type(1);
     setAttack_Element(0);
     setElement_Attack(0,150);
     setElement_Attack(1,0);
     setElement_Attack(2,0);
     setElement_Attack(3,0);
     setElement_Attack(4,0);
     setResistance(0,0.30);
     setResistance(1,0.30);
     setResistance(2,0.30);
     setResistance(3,0.30);
     setResistance(4,0.30);
     setResistance(color,1);//根据颜色衣服抗性拉满
     setAttack_Type_Resistance(1,0.3);
     setAttack_Type_Resistance(2,0.3);
     setAttack_Type_Resistance(3,0.3);
     setPainterX(painterX);
     setPainterY(painterY);
 }
//攻击两次
 void MonsterSwordMan::attack(One &one)
 {
     int defenseTemp = one.Defense;
     one.HP-=getAttack() * (1-defenseTemp/(defenseTemp+100)) * (1-one.Attack_Type_Resistance[getAttack_Type()]) * 0.5
             +getElement_Attack(getAttack_Element()) * (1-defenseTemp/(defenseTemp+50)) * (1-one.Resistance[getAttack_Element()]) *0.5;
     one.getReward(getPoint());

     one.HP-=getAttack() * (1-defenseTemp/(defenseTemp+100)) * (1-one.Attack_Type_Resistance[getAttack_Type()]) * 0.5
             +getElement_Attack(getAttack_Element()) * (1-defenseTemp/(defenseTemp+50)) * (1-one.Resistance[getAttack_Element()]) *0.5;
     one.getReward(getPoint());
 }
