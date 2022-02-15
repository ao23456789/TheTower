#include "one.h"

One::One()
{

}


/*
不带属性： 攻击方攻击力*（1-防守方防御力/防守方防御力+100）  *（1-防守方攻击类型抗性）*0.5
 +  攻击方攻击力*（1-防守方防御力/防守方防御力+50）*（1-防守方攻击类型抗性的平均值）*0.5

带属性：  攻击方攻击力*（1-防守方防御力/防守方防御力+100） *0.5*（1-防守方攻击类型抗性）*0.5
 + 攻击方属性攻击力*（1-防守方防御力/防守方防御力+50）*（1-防守方对应属性抗性）*0.5
*/


void One::initOne()
{

    haveCoin = false;//没有持有硬币
    treasure = 0;//默认没装备东西
    for(int i=0;i<5;i++)//清零
    {
        for(int j=0;j<2;j++)
        {
            treasures[i][j] = 0;
        }
    }

    whatsYourEnd = 4;//默认跑路

    One_Direction =0;//默认方向向上
    position.layler = 0;//默认出生时为第一层
    position.x = 11;//6,10,11
    position.y = 6;
    LV=1;
    lvPoint =0;
    point = 0;



    isElf = false;
    withPrincess = false;



    //战斗属性
    HP=500;
    Max_HP=500;
    Attack=20;
    Defense=20;
    Agile =5;

    Attack_Type=1;//攻击类型 1为斩击，2为钝击，3为刺击
    Attack_Element=0;
    Attack_Type_Resistance[0] = 0;
    Attack_Type_Resistance[1] = 0.2;
    Attack_Type_Resistance[2] = 0.2;
    Attack_Type_Resistance[3] = 0.2;


    Element_Attack[0]=Attack/3;//无属性为攻击力的三分之一
    Element_Attack[1]=0;//冰属性攻击力
    Element_Attack[2]=0;//雷属性攻击
    Element_Attack[3]=0;//火属性攻击力
    Element_Attack[4]=0;//魔属性攻击力

    Resistance[0] = (Attack_Type_Resistance[1]+Attack_Type_Resistance[2]+Attack_Type_Resistance[3])/3;//面对无属性的攻击，抗性为斩击+刺击+钝击/3
    Resistance[1] = 0.2;//冰属性抗性
    Resistance[2] = 0.2;//雷属性抗性
    Resistance[3] = 0.2;//火属性抗性
    Resistance[4] = 0.2;//魔属性抗性

    for(int &i : key)
    {i=0;}//钥匙清零


    //-----------------调试用，记得删


    //-------------------------------



}
//是否满足五个条件
bool One::getFragment()
{
    bool res = true;
    for(int i=0;i<5;i++)
    {
        if( treasures[i][1] == 0)
            res = false;
    }
    return res;
}

//获得经验
void One::getReward(double num)
{
    exBuff = (300-LV)/30;
    exBuff = exBuff>10?10:exBuff;
    exBuff = exBuff<1?1:exBuff;
    //1-9之间20级是收益正负分界线
    if(!haveCoin)//有硬币点数*2
    {
        point+= num * exBuff;//经验随等级增加而减少
    }
    else
    {
        point+= num * exBuff * 2;
    }

}


