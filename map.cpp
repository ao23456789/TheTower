#include <map.h>
#include <QDebug>
#define Ice 1
//可以将数据保存在文件里，下次打开再读取文件

Map::Map()
{
    //初始化地图
    initMap();
    //初始化怪兽
    initMonster();

}

Map::~Map()
{
    delete [] *monsterBat;
    delete [] *monsterSlime;
    delete [] *monsterSkeleton;
    delete [] *monsterOrcish;
    delete [] *monsterMagicer;
    delete [] *monsterElementStone;
    delete [] *monsterCrusadeKnight;
    delete [] *monsterMatrixKnight;
    delete [] *monsterNpc;
    delete [] *Boss;
    delete [] *monsterSwordMan;
}

int Map::getS_Map(int layler, int x, int y)
{
    return s_Map[layler][x][y];
}

int Map::getS_Map(Position p)
{
    return s_Map[p.layler][p.x][p.y];
}
void Map::setS_Map(int layler, int x, int y,int value)
{
    s_Map[layler][x][y] = value;
}

void Map::setS_Map(Position p, int value)
{
    s_Map[p.layler][p.x][p.y] = value;
}


int Map::getT_Map(int layler, int x, int y)
{
    return t_Map[layler][x][y];
}
int Map::getT_Map(Position p)
{
    return t_Map[p.layler][p.x][p.y];
}
void Map::setT_Map(int layler, int x, int y,int value)
{
    t_Map[layler][x][y] = value;
}
void Map::setT_Map(Position p, int value)
{
    t_Map[p.layler][p.x][p.y] = value;
}




void Map::initMonster()
{
    /*


//红色双手剑士的意思是喜欢穿红色衣服的双手剑士，和其他的没有什么区别
//其实是有区别的，对应衣服对应抗性要高一些




 Monster(int monsterId,double point,int Agile,int HP,int Max_HP,int Attack,int Defense,int Attack_Type,
int Attack_Element,int Element_Attack0,int Element_Attack1,int Element_Attack2,int Element_Attack3,int Element_Attack4,
float Resistance0,float Resistance1,float Resistance2,float Resistance3,float Resistance4,
float Resistance_Slash,float Resistance_Bludgeon,float Resistance_Puncture);


怪物ID,点数,敏捷,血量,最大血量,攻击,防御,
攻击类型 1为斩击，2为钝击，3为刺击,
攻击元素0为无 1为冰，2为雷，3火，4魔,
属性攻击力0,1,2,3,4,
属性抗性0,1,2,3,4,  0物抗
斩击抗性,钝击抗性,穿刺抗性
绘制图位置X,绘制图位置Y,
*/
//怪物图


    //0冰霜史莱姆     怕火，冰免疫                                          无属性=攻击力
    //1,9,7
     monsterSlime[0] = new MonsterSlime(100, 0.4, 1, 200, 200, 30,20, 2,1,  30,30,0,0,0,
                                   0.2,1,0.35,-0.2,0.35,0.2, 0.7,-0.2 ,1,0);
     //1雷电史莱姆  雷属性修正 血量防御*0.7  攻击*1.25  脆，攻击高，
     //1,9,8
     monsterSlime[1] = new MonsterSlime(101, 0.6, 10, 200*0.7, 200*0.7, 30*1.25,20*0.7, 2,2,  30*1.25,0,30,0,0,
                                   0.2,0.35,1,0.35,0.35,0.2, 0.7,-0.2,5,0);
     //2火焰史莱姆    怕冰，火免
     //1,10,8
     monsterSlime[2] = new MonsterSlime(102, 0.4, 1, 200, 200, 30,20, 2,3,  30,0,0,30,0,
                                   0.2,-0.2,0.35,1,0.35,0.2, 0.7,-0.2,0,0);
     //3魔法史莱姆     抗属性，怕物理
     //1,10,9
     monsterSlime[3] = new MonsterSlime(103, 0.4, 1, 200, 200, 30,20, 2,4,  30,0,0,0,30,
                                   0.1,0.75,0.75,0.75,0.75,0.1, 0.6,-0.35,3,0);
     //4钢铁史莱姆 钢铁修正 血量防御*2 攻击*0.75  最怕雷，其次魔，其次属性，物理抗性高，血量很厚
     //1,10,7
     monsterSlime[4] = new MonsterSlime(104, 0.6, 0, 200*2, 200*2, 30*0.75,20*2, 2,0,  30*2,0,0,0,0,
                                   0.8,0.1,-2,0.1,-1,0.8,0.8,0.8,6,0);
     //5史莱姆王 没有弱点
     //7,7,9
     monsterSlime[5] = new MonsterSlime(105, 1.5, 2, 1000, 1000, 100,100, 2,0,100,0,0,0,0,
                                   0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,7,0);
     //2,9,4  钢
     monsterSlime[6] = new MonsterSlime(106, 0.6, 0, 200*2, 200*2, 30*0.75,20*2, 2,0,  30*2,0,0,0,0,
                                   0.8,0.1,-2,0.1,-1,0.8,0.8,0.8,6,0);
     // 0,10,5 冰
     monsterSlime[7] = new MonsterSlime(107, 0.4, 1, 200, 200, 30,20, 2,1,  30,30,0,0,0,
                                   0.2,1,0.35,-0.2,0.35,0.2, 0.7,-0.2,1,0);
     // 0,10,7 火
     monsterSlime[8] = new MonsterSlime(108, 0.4, 1, 200, 200, 30,20, 2,3,  30,0,0,30,0,
                                   0.2,-0.2,0.35,1,0.35,0.2, 0.7,-0.2,0,0);
     //2,8,3  钢
     monsterSlime[9] = new MonsterSlime(109, 0.6, 0, 200*2, 200*2, 30*0.75,20*2, 2,0,  30*2,0,0,0,0,
                                   0.8,0.1,-2,0.1,-1,0.8,0.8,0.8,6,0);



//[110-120)蝙蝠
     monsterBat[0] = new MonsterBat(110,0.4,8,0);//1,8,7
     monsterBat[0]->getElement(WEAK,0);//弱化版
     monsterBat[1] = new MonsterBat(111,0.4,8,0);//门口两个小蝙蝠 1,8,8
     monsterBat[1]->getElement(WEAK,0);

     monsterBat[2] = new MonsterBat(112,0.6,0,2);//火 1，9，10
     monsterBat[2]->getElement(FIRE,40);

     monsterBat[3] = new MonsterBat(113,0.6,1,2);//冰 1，9，9
     monsterBat[3]->getElement(ICE,40);

     monsterBat[4] = new MonsterBat(114,0.6,4,2);//雷 1，8，9
     monsterBat[4]->getElement(THUNDER,40);

     monsterBat[5] = new MonsterBat(115,0.6,5,2);//钢 1，8，10
     monsterBat[5]->getElement(IRON,0);

     monsterBat[6] = new MonsterBat(116,0.6,5,2);//钢 2，6，3
     monsterBat[6]->getElement(IRON,0);

     monsterBat[7] = new MonsterBat(117,0.6,5,2);//钢 2，9，6
     monsterBat[7]->getElement(IRON,0);

     monsterBat[8] = new MonsterBat(118,0.6,4,2);//雷 4，8，3
     monsterBat[8]->getElement(THUNDER,40);

     monsterBat[9] = new MonsterBat(119,0.6,4,2);//雷 4，8，4
     monsterBat[9]->getElement(THUNDER,40);



//[120-130)骷髅 只有两种，拿剑盾的和没拿的  怕钝击，抗刺击 属性抗性一般
    //   此坐标是数组坐标，怪物坐标XY为绘制图坐标，先横后竖
    monsterSkeleton[0] = new MonsterSkeleton(120,0.3,2,7,2);//不拿的1,2,3
    monsterSkeleton[2] = new MonsterSkeleton(122,0.4,2,7,2);//1,2,4
    monsterSkeleton[3] = new MonsterSkeleton(123,0.4,2,7,2);//1,2,5
    monsterSkeleton[6] = new MonsterSkeleton(126,0.4,2,7,2);//2,2,3
    monsterSkeleton[7] = new MonsterSkeleton(127,0.4,2,7,2);//2,9,10

    monsterSkeleton[1] = new MonsterSkeleton(121,0.4,1,4);//拿剑，两者属性不同，构造函数不同 1,3,4
    monsterSkeleton[4] = new MonsterSkeleton(124,0.4,1,4);//2,4,3
    monsterSkeleton[5] = new MonsterSkeleton(125,0.4,1,4);//2,9,8
    monsterSkeleton[8] = new MonsterSkeleton(128,0.4,2,1,4);//7,10,1
    monsterSkeleton[9] = new MonsterSkeleton(129,0.4,2,1,4);//7,1,11



//[130,140) 兽人 拿剑的和没拿的，和骷髅类似
    monsterOrcish[0] = new MonsterOrcish(130,0.5,2,8,4);//没拿 2,6,5
    monsterOrcish[2] = new MonsterOrcish(132,0.5,2,8,4);//2,7,6
    monsterOrcish[4] = new MonsterOrcish(134,0.5,2,8,4);//7,11,3
    monsterOrcish[5] = new MonsterOrcish(135,0.5,2,8,4);//7,9,3

    monsterOrcish[1] = new MonsterOrcish(131,0.6,1,6);   //拿了2,4,5
    monsterOrcish[3] = new MonsterOrcish(133,0.6,1,6);   //2,7,8
    monsterOrcish[6] = new MonsterOrcish(136,0.6,1,6);  //7,11,5
    monsterOrcish[7] = new MonsterOrcish(137,0.6,1,6);  //7,9,5
    monsterOrcish[8] = new MonsterOrcish(138,0.6,1,6);   //8,10,4
    monsterOrcish[9] = new MonsterOrcish(139,0.6,1,6);   //8,10,2



//[140,150)法师
    monsterMagicer[0] = new MonsterMagicer(140,1.5,3,8);//4,2,3
    monsterMagicer[0]->getElement(THUNDER,150);
    monsterMagicer[1] = new MonsterMagicer(141,1.5,3,8);//4,3,2
    monsterMagicer[1]->getElement(THUNDER,150);
    monsterMagicer[2] = new MonsterMagicer(142,1.5,3,8);//4,3,4
    monsterMagicer[2]->getElement(THUNDER,150);
    monsterMagicer[3] = new MonsterMagicer(143,1.5,3,8);//4,4,3
    monsterMagicer[3]->getElement(THUNDER,150);

    monsterMagicer[4] = new MonsterMagicer(144,1.5,0,8);//7,11,7
    monsterMagicer[4]->getElement(FIRE,150);
    monsterMagicer[5] = new MonsterMagicer(145,1.5,0,8);//7,7,1
    monsterMagicer[5]->getElement(FIRE,150);
    monsterMagicer[6] = new MonsterMagicer(146,1.5,0,8);//7,1,7
    monsterMagicer[6]->getElement(FIRE,150);
    monsterMagicer[7] = new MonsterMagicer(147,1.5,0,8);//7,1,9
    monsterMagicer[7]->getElement(FIRE,150);

    monsterMagicer[8] = new MonsterMagicer(148,1.5,1,8);//3,3,2
    monsterMagicer[8]->getElement(ICE,150);
    monsterMagicer[9] = new MonsterMagicer(149,1.5,1,8);//3,2,1
    monsterMagicer[9]->getElement(ICE,150);


//[150,160)//石头人
    monsterElementStone[0] = new MonsterElementStone(150,2,1,12);//2,4,7
    monsterElementStone[0]->getElement(IRON,60);
    monsterElementStone[1] = new MonsterElementStone(151,2,1,12);//2,2,5
    monsterElementStone[1]->getElement(IRON,60);

    monsterElementStone[2] = new MonsterElementStone(152,2,7,10);//4,4,7
    monsterElementStone[2]->getElement(THUNDER,60);
    monsterElementStone[3] = new MonsterElementStone(153,2,7,10);//2,2,5
    monsterElementStone[3]->getElement(THUNDER,60);

    monsterElementStone[4] = new MonsterElementStone(154,2,8,10);//7,5,1
    monsterElementStone[4]->getElement(FIRE,60);
    monsterElementStone[5] = new MonsterElementStone(155,2,8,10);//7,5,9
    monsterElementStone[5]->getElement(FIRE,60);
    monsterElementStone[6] = new MonsterElementStone(156,2,8,10);//7,1,5
    monsterElementStone[6]->getElement(FIRE,60);
    monsterElementStone[7] = new MonsterElementStone(157,2,8,10);//7,1,7
    monsterElementStone[7]->getElement(FIRE,60);

    monsterElementStone[8] = new MonsterElementStone(158,2,5,10);//3,10,2
    monsterElementStone[8]->getElement(ICE,60);
    monsterElementStone[9] = new MonsterElementStone(159,2,5,10);//3,3,1
    monsterElementStone[9]->getElement(ICE,60);


//[160,170)//十字脸骑士
    monsterCrusadeKnight[0] = new MonsterCrusadeKnight(160,2,5,12);//2,5,8
    monsterCrusadeKnight[0]->getElement(IRON,0);
    monsterCrusadeKnight[1] = new MonsterCrusadeKnight(161,2,5,12);//2,7,10
    monsterCrusadeKnight[1]->getElement(IRON,0);

    monsterCrusadeKnight[2] = new MonsterCrusadeKnight(162,2,2,12);//7,9,7
    monsterCrusadeKnight[2]->getElement(FIRE,80);
    monsterCrusadeKnight[3] = new MonsterCrusadeKnight(163,2,2,12);//7,5,7
    monsterCrusadeKnight[3]->getElement(FIRE,80);

    monsterCrusadeKnight[4] = new MonsterCrusadeKnight(164,2,3,12);//7,8,8
    monsterCrusadeKnight[4]->getElement(ICE,80);
    monsterCrusadeKnight[5] = new MonsterCrusadeKnight(165,2,3,12);//3,11,2
    monsterCrusadeKnight[5]->getElement(ICE,80);
    monsterCrusadeKnight[6] = new MonsterCrusadeKnight(166,2,3,12);//3,10,1
    monsterCrusadeKnight[6]->getElement(ICE,80);

    monsterCrusadeKnight[7] = new MonsterCrusadeKnight(167,2,5,12);//8,8,2
    monsterCrusadeKnight[7]->getElement(IRON,80);
    monsterCrusadeKnight[8] = new MonsterCrusadeKnight(168,2,2,12);//8,5,3
    monsterCrusadeKnight[8]->getElement(FIRE,80);
    monsterCrusadeKnight[9] = new MonsterCrusadeKnight(169,2,3,12);//8,4,1
    monsterCrusadeKnight[9]->getElement(ICE,80);


//[170,180)//矩阵骑士
    monsterMatrixKnight[0] = new MonsterMatrixKnight(170,3,4,14);//2,2,7
    monsterMatrixKnight[0]->getElement(IRON,0);
    monsterMatrixKnight[1] = new MonsterMatrixKnight(171,3,4,14);//2,5,10
    monsterMatrixKnight[1]->getElement(IRON,0);

    monsterMatrixKnight[2] = new MonsterMatrixKnight(172,3,0,14);//7,2,3
    monsterMatrixKnight[2]->getElement(FIRE,100);
    monsterMatrixKnight[3] = new MonsterMatrixKnight(173,3,0,14);//7,3,3
    monsterMatrixKnight[3]->getElement(FIRE,100);

    monsterMatrixKnight[4] = new MonsterMatrixKnight(174,3,1,14);
    monsterMatrixKnight[4]->getElement(ICE,100);
    monsterMatrixKnight[5] = new MonsterMatrixKnight(175,3,3,14);
    monsterMatrixKnight[5]->getElement(THUNDER,0);
    monsterMatrixKnight[6] = new MonsterMatrixKnight(176,3,0,14);
    monsterMatrixKnight[6]->getElement(FIRE,100);
    monsterMatrixKnight[7] = new MonsterMatrixKnight(177,3,2,14);
    monsterMatrixKnight[7]->getElement(MAGIC,150);
    monsterMatrixKnight[8] = new MonsterMatrixKnight(178,3,4,14);
    monsterMatrixKnight[8]->getElement(IRON,0);
    monsterMatrixKnight[9] = new MonsterMatrixKnight(179,3,4,14);
    monsterMatrixKnight[9]->getElement(IRON,0);





//Npc
     monsterNpc[0] = new Monster(180, 5, 3, 1000, 1000,20,50, 2,3,10,0,0,0,0,
                                 0.2,0.35,0.35,0.35,0.35,0.2, 0.2,0.2,27,24);//商人
     monsterNpc[1] = new Monster(181, 5, 3, 1000, 1000,20,50, 2,0,10,0,0,0,0,
                                 0.2,0.35,0.35,0.35,0.35,0.2, 0.2,0.2,27,24);
     monsterNpc[2] = new Monster(182, 5, 3, 1000, 1000,20,50, 2,1,10,0,0,0,0,
                                 0.2,0.35,0.35,0.35,0.35,0.2, 0.2,0.2,27,24);
//Boss
    Boss[0] = new Monster(190,4,7,5000,5000,350,350,1,3,350,0,0,300,0,0.6,0.1,0.2,1,0.3,0.5,0.5,0.5,4,18);//龙
    Boss[1] = new Monster(191,4,7,5000,5000,300,300,2,1,300,350,0,0,0,0.6,1,0.1,-0.5,0.1,0.3,0.3,0.3,0,18);//海怪
    Boss[2] = new Monster(192,5,8,4500,4500,250,250,1,0,250,0,0,0,0,0.8,0.35,-1.5,0.35,0.35,0.7,0.7,0.7,5,14);//黑骑士
    Boss[3] = new Monster(193,5,9,4000,4000,200,200,3,4,200,0,0,0,250,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,6,16);//吸血鬼
    Boss[4] = new Monster(194,10,9,9999,9999,500,500,3,3,500,500,500,500,500,0.65,0,0.65,0.65,0.65,0.65,0.65,0.65,6,14);//魔王

//[300,310)双手剑士
     monsterSwordMan[0] = new MonsterSwordMan(300,5,2,9,12);//4,2,2
     monsterSwordMan[1] = new MonsterSwordMan(301,5,2,9,12);//4,2,4
     monsterSwordMan[9] = new MonsterSwordMan(309,5,2,9,12);//8,7,3

     monsterSwordMan[2] = new MonsterSwordMan(302,5,3,6,12);//7,7,4
     monsterSwordMan[3] = new MonsterSwordMan(303,5,3,6,12);//7,5,4
     monsterSwordMan[4] = new MonsterSwordMan(304,5,3,6,12);//7,3,9

     monsterSwordMan[5] = new MonsterSwordMan(305,5,1,7,12);//3,9,7
     monsterSwordMan[6] = new MonsterSwordMan(306,5,1,7,12);//3,9,8
     monsterSwordMan[7] = new MonsterSwordMan(307,5,1,7,12);//3,9,9
     monsterSwordMan[8] = new MonsterSwordMan(308,5,1,7,12);//8,7,1



}
//npc
//54 2层红色商人
void Map::initMap()
{

}


bool Map::isMonster(int layler,int x,int y)
{
    if(s_Map[layler][x][y]>=100 && s_Map[layler][x][y]<200)
    {
        return true;
    }
    return false;
}

bool Map::isAbleWalk(int layler,int x,int y)
{
    if(t_Map[layler][x][y]>=259 && t_Map[layler][x][y]<=285)//字母
    {
        return true;
    }
    if(t_Map[layler][x][y]>=230 && t_Map[layler][x][y]<=239)//扫雷数字
    {
        return true;
    }
    if(t_Map[layler][x][y]>=241 && t_Map[layler][x][y]<=249)//魔法阵
    {
        return true;
    }
    if(t_Map[layler][x][y]>=250 && t_Map[layler][x][y]<=258)//黑海
    {
        return true;
    }


    switch (t_Map[layler][x][y])
    {
    case 11://草地
        return true;
    case 14://密道
        return true;
    case 13://石地
        return true;  
    case 17://雪地
        return true; 
    case 25://雷图地板
        return true;
    case 30://火图地板
        return true;
    case 220://红感叹号图标
        return true;
    case 221://=符号
        return true;
    case 222://上楼梯图标
        return true;
    case 223://向下指图标
        return true;
    case 224://1
        return true;
    case 225://9
        return true;

    default:
        return false;
    }
}

void Map::find1(int &layler,int &x, int &y)
{
    for(int i=0;i<13;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(s_Map[layler][i][j] == 61)
            {
                x=i;
                y=j;
            }
        }
    }
}

void Map::find2(int &layler, int &x, int &y)
{

    for(int i=0;i<13;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(s_Map[layler][i][j] == 62)
            {
                x=i;
                y=j;
            }
        }
    }
}



