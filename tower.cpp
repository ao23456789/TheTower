#include "tower.h"
#include "ui_tower.h"
#include "one_ui.h"

#include "map.h"
#include "map.cpp"



Tower::Tower(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tower)
{
    ui->setupUi(this);
    //消除右上角默认❓标志
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    flags |=Qt::WindowMinimizeButtonHint;//添加最小化按钮
    setWindowFlags(flags);

    setWindowTitle(QObject::tr("魔塔"));
    setFixedSize(1100,800);
    gameInit();//初始化游戏

}

Tower::~Tower()
{
    delete ui;
}

void Tower::oneRecvData(One one1)
{
    one.treasure = one1.treasure;
    one.Max_HP = one1.HP;
    one.Attack = one1.Attack;
    one.Defense = one1.Defense;
    one.LV = one1.LV;
    one.lvPoint = one1.lvPoint;
    one.point = one1.point;
    one.Agile = one1.Agile;

    for(int i =0;i<5;i++)
    {
      one.Element_Attack[i] = one1.Element_Attack[i];
      one.Resistance[i] = one1.Resistance[i];
    }

    one.Attack_Type_Resistance[1] =one1.Attack_Type_Resistance[1];
    one.Attack_Type_Resistance[2] =one1.Attack_Type_Resistance[2];
    one.Attack_Type_Resistance[3] =one1.Attack_Type_Resistance[3];
}

void Tower::oneRecvTreasure(int num)
{
    one.treasure = num+90;
}


void Tower::gameInit()
{

    haveCross = false;

    //商人的价格
    merchantCost[0] = 100;
    merchantCost[1] = 200;
    merchantCost[2] = 300;
    merchantCost[3] = 400;
    merchantCost[4] = 10000;


    for(int i=0;i<50;i++)
    {
        eventList[i] =0;
    }//事件图初始化

    //扫雷标记地图初始化
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
           mineFlagMap[i][j] = 9;//没有9值，代表刚开始显示原地图值
        }
    }

    one.initOne();//角色初始化
    map.initMonster();//怪物数据初始化、

    for(int k=0;k<11;k++)
    {
        for(int i =0;i<=12;i++)
        {
            for(int j=0;j<=12;j++)
            {
                Position p(k,i,j);
                switch(isWhatKindMonster(p))
                {
                case MATRIXKNIGHT :
                    weAreMatrix(p);
                    break;
                }
            }
        }
    }


}

void Tower::gameDead()
{
    QMessageBox::about(this, "游戏结束", "死亡未必是终点，但一定是种解脱");
    this->close();
}


//键盘输入
void Tower::keyPressEvent(QKeyEvent *event)
{
    if(!one.isElf)//变精灵之后怎么按都没用
    {
        //按键移动，判断目标位置为可通行草地之后移动
        switch (event->key())
        {
        case Qt::Key_Up :
            one.One_Direction = 0;
                    move(0);
            break;
        case Qt::Key_Down :
            one.One_Direction = 1;

                    move(1);
            break;
        case Qt::Key_Left :
            one.One_Direction = 2;
                    move(2);
            break;
        case Qt::Key_Right :
            one.One_Direction = 3;
                    move(3);
            break;
        case Qt::Key_Z://切换攻击类型
                one.Attack_Type++;
                if(one.Attack_Type>3)
                {
                    one.Attack_Type-=3;
                }
            break;
        case Qt::Key_X://切换元素种类
                one.Attack_Element++;
                if(one.Attack_Element>4)
                {
                    one.Attack_Element-=5;
                }
            break;
        case Qt::Key_V://翻开格子
            if(one.position.layler == 6
                    && one.position.x<=9 && one.position.x>=1
                    && one.position.y<=9 && one.position.y>=1)//只在扫雷界面内有效
            {
                openBlock(one.position.x,one.position.y);
            }
            break;
        case Qt::Key_B://插上标记
            if(one.position.layler == 6
                    && one.position.x<=9 && one.position.x>=1
                    && one.position.y<=9 && one.position.y>=1)//只在扫雷界面内有效
            {
                mineFlag();

            }
            break;
        case Qt::Key_F:
            treasure();
            break;
        case Qt::Key_C://打开主角UI
                One_ui *oneui = new One_ui;
                oneui->show();
                connect(this,SIGNAL(oneuiSendData(One)),oneui,SLOT(oneuiRecvData(One)));
                connect(oneui,SIGNAL(oneSendData(One)),this,SLOT(oneRecvData(One)));
                connect(oneui,SIGNAL(oneSendTreasure(int)),this,SLOT(oneRecvTreasure(int)));
                emit oneuiSendData(one);
            break;
        }
    }
    else
    {
        if(event->key() == Qt::Key_C)
        {
            QMessageBox::about(this, "深陷塔内", "艾尔夫的欺骗让某个人身缚诅咒，翅膀只是摆设，没有手脚的身体几乎无法走动，你的血液却在体内川流不息，"
                                             "这是精灵的能力和诅咒，你连死亡的选择都没有，在一个温暖的良夜，你悔恨着自己的愚蠢，又暗自期待着下一个勇者的到来。");
            this->close();
        }

    }

}

//绘制图像
void Tower::paintEvent(QPaintEvent *)
{
    QPixmap jpg;//素材图
    QPixmap character;//主角素材
    QPixmap monster;
    QPixmap doorAndKey;
    QPixmap attack_Type;
    QPixmap attackElementType;
    QPixmap mine;
    QPixmap treasure;


        //加载图片
        jpg.load("://res/tower.jpg");
        character.load("://res/Character.jpg");
        monster.load("://res/moster.jpg");
        doorAndKey.load("://res/door&key.jpg");
        attack_Type.load("://res/attack_type.jpg");
        mine.load("://res/mine.bmp");
        attackElementType.load("://res/attackElementType.bmp");
        treasure.load("://res/treasure.bmp");

        QPainter painter(this);//要绘制的对象

        //inline void QPainter::drawPixmap(int x, int y, const QPixmap &pm,  int sx, int sy, int sw, int sh)
        //在该对象的x,y位置处绘制pm图像上的从sx,sy点开始的长sw宽sh的矩形


//绘制UI

            //黄钥匙
            painter.drawPixmap( map_XOffset-60 , map_YOffset , doorAndKey, 7 * 33, 0, HEIGHT,WIDTH);
            //黄钥匙数量
            if(one.key[0]>10)
            {
                painter.drawPixmap( map_XOffset-30-33 , map_YOffset , jpg,  33, 26 * 33, HEIGHT,WIDTH);
            }
            painter.drawPixmap( map_XOffset-30 , map_YOffset , jpg, one.key[0]%10 * 33, 26 * 33, HEIGHT,WIDTH);

            //红钥匙
            painter.drawPixmap( map_XOffset-60 , map_YOffset+30 , doorAndKey, 5 * 33, 0, HEIGHT,WIDTH);
            //红钥匙数量
            painter.drawPixmap( map_XOffset-30 , map_YOffset+30 , jpg, one.key[2] * 33, 26 * 33,HEIGHT,WIDTH);
            //蓝钥匙
            painter.drawPixmap( map_XOffset-60 , map_YOffset+60 , doorAndKey, 6 * 33, 0, HEIGHT,WIDTH);
            //蓝钥匙数量
            painter.drawPixmap( map_XOffset-30 , map_YOffset +60, jpg, one.key[1] * 33, 26 * 33,HEIGHT,WIDTH);
            //绿钥匙
            painter.drawPixmap( map_XOffset-60 , map_YOffset +90, doorAndKey, 8 * 33, 0, HEIGHT,WIDTH);
            //绿钥匙数量
            painter.drawPixmap( map_XOffset-30 , map_YOffset +90 , jpg, one.key[3] * 33, 26 * 33,HEIGHT,WIDTH);


            //当前楼层
            if(one.position.layler<10)
            {
                painter.drawPixmap( map_XOffset+33 , map_YOffset-33 , jpg, one.position.layler * 33, 26 * 33,HEIGHT,WIDTH);
            }
            else
            {
                painter.drawPixmap( map_XOffset+33 , map_YOffset-33 , jpg, 3*33, 29*33, HEIGHT,WIDTH);
            }


            //当前血量
            int Hp[5]={0};
            int temp=one.HP;
            int i =4;
            while(temp>0)
            {
                Hp[i] = temp%10;
                temp/=10;
                i--;
            }
            for(int j =0;j<5;j++)
            {
                painter.drawPixmap( 729+j*33, 153 , jpg, Hp[j]* 33, 26 * 33, HEIGHT,WIDTH);
            }
            //最大血量
            int maxHp[5] = {0};
            temp = one.Max_HP;
            i =4;
            while(temp>0)
            {
                maxHp[i] = temp%10;
                temp/=10;
                i--;
            }
            for(int j =0;j<5;j++)
            {
                painter.drawPixmap( 729+j*33, 153+33*2 , jpg, maxHp[j]* 33, 26 * 33,HEIGHT,WIDTH);
            }
            //攻击力防御力
            int Acc[3] = {0},Den[3] = {0};
            int temp1=one.Attack,temp2=one.Defense;
            int i1=2;
            while(temp1>0)
            {
                Acc[i1] = temp1%10;
                temp1/=10;
                i1--;
            }
            i1=2;
            while(temp2>0)
            {
                Den[i1] = temp2%10;
                temp2/=10;
                i1--;
            }
            for(int j =0;j<3;j++)
            {
                painter.drawPixmap( 729+j*33, 219+33*2 , jpg, Acc[j]* 33, 26 * 33, HEIGHT,WIDTH);
                painter.drawPixmap( 729+j*33, 219+33*4 , jpg, Den[j]* 33, 26 * 33, HEIGHT,WIDTH);
            }


//绘制攻击类型
            for (int i=1;i<=3;i++)
            {
                if(one.Attack_Type == i)
                {
                    painter.drawPixmap( 696 +i*33, 219+33*5 , attack_Type,  (i-1)*33,  33, HEIGHT,WIDTH); //选中状态
                }
                else
                {
                     painter.drawPixmap( 696 +i*33, 219+33*5 , attack_Type,  (i-1)*33,  0, HEIGHT,WIDTH);//未选中态
                }
            }
//绘制元素种类
            painter.drawPixmap( 729 , 219+33*6 , attackElementType, one.Attack_Element*33, 1*33,HEIGHT,WIDTH);
//绘制当前物品
            if(one.treasure>=90  && one.treasure<94)
            {
                painter.drawPixmap( 762 , 219+33*6 , treasure,( one.treasure - 90) *33, 0,HEIGHT,WIDTH);
            }
            else
            {
                switch (one.treasures[4][0])//水壶
                {
                case 0:
                    painter.drawPixmap( 762  , 219+33*6 , treasure, 7*33, 0, HEIGHT,WIDTH);
                    break;
                case 1://拥有
                    painter.drawPixmap( 762  , 219+33*6 , treasure, 6*33, 0, HEIGHT,WIDTH);
                    break;
                case 2://水
                    painter.drawPixmap( 762  , 219+33*6 , treasure, 5*33, 0, HEIGHT,WIDTH);
                    break;
                case 3://火
                    painter.drawPixmap( 762  , 219+33*6 , treasure, 4*33, 0, HEIGHT,WIDTH);
                    break;
                case 4://毒
                    painter.drawPixmap( 762  , 219+33*6 , treasure, 5*33, 33, HEIGHT,WIDTH);
                    break;
                }
            }



//绘制地形图
        for(int i= 0;i<13;i++)
        {
            for(int j = 0;j<13 ; j++)
            {
                switch (map.getT_Map(one.position.layler,i,j))
                {
                case 1://海水1
                    painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , jpg, 2*33, 0, HEIGHT,WIDTH);
                    break;
                case 2://海水2
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 3*33,0 , HEIGHT,WIDTH);
                    break;
                case 3://岩浆1
                    painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , jpg, 2 * 33, 16 * 33, HEIGHT,WIDTH);
                    break;
                case 4://岩浆2
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 3 * 33, 16 * 33, HEIGHT,WIDTH);
                    break;
                case 5://星星1
                    painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , jpg, 0 * 33, 16 * 33, HEIGHT,WIDTH);
                    break;
                case 6://星星2
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 1 * 33, 16 * 33, HEIGHT,WIDTH);
                    break;

                case 7://毒谭
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 2 * 33, 1 * 33, HEIGHT,WIDTH);
                    break;
                case 8://水谭
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 7*33, 1*33, HEIGHT,WIDTH);
                    break;
                case 9://火谭
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 9 * 33, 10 * 33, HEIGHT,WIDTH);
                    break;



                case 10://边缘紫墙
                    painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , jpg, 1 * 33, 3 * 33, HEIGHT,WIDTH);
                    break;
                case 11://可通行草地
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 33, 0, HEIGHT,WIDTH);
                    break;
                case 12://黑色墙壁
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 1*33, 2*33, HEIGHT,WIDTH);
                    break;
                case 13://石块地板
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,  0 , 0, HEIGHT,WIDTH);
                    break;
                case 14://可通行密道
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 33, 12*33, HEIGHT,WIDTH);
                    break;
                case 15://森林
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 11*33, 19*33, HEIGHT,WIDTH);
                    break;
                case 16://石块
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 5*33, 2*33, HEIGHT,WIDTH);
                    break;
                case 17://雪地
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 6*33, 9*33, HEIGHT,WIDTH);
                    break;
                case 18://雪墙
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 8*33, 0*33, HEIGHT,WIDTH);
                    break;

                case 20://冰树
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 8*33, 1*33, HEIGHT,WIDTH);
                    break;

                case 25://雷图地板
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 4*33, 12*33, HEIGHT,WIDTH);
                    break;
                case 26://雷图墙壁
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 7*33, 16*33, HEIGHT,WIDTH);
                    break;
                case 30://火图地板
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 1*33, 5*33, HEIGHT,WIDTH);
                    break;
                case 31://火图墙壁
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 4*33, 16*33, HEIGHT,WIDTH);
                    break;
                case 32://火山左上
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 18*33, 0*33, HEIGHT,WIDTH);
                    break;
                case 33://火山右上
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 19*33, 0*33, HEIGHT,WIDTH);
                    break;
                case 34://火山左下
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 18*33, 1*33, HEIGHT,WIDTH);
                    break;
                case 35://火山右下
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 19*33, 1*33, HEIGHT,WIDTH);
                    break;
                case 36://数独机关
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 19*33, 13*33, HEIGHT,WIDTH);
                    break;


                    //大树1
                case 200:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 10*33, 0*33, HEIGHT,WIDTH);
                    break;
                case 201:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 11*33, 0*33, HEIGHT,WIDTH);
                    break;
                case 202:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 10*33, 1*33, HEIGHT,WIDTH);
                    break;
                case 203:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 11*33, 1*33, HEIGHT,WIDTH);
                    break;
                    //大树2
                case 204:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 18*33, 8*33, HEIGHT,WIDTH);
                    break;
                case 205:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 18*33, 9*33, HEIGHT,WIDTH);
                    break;


                case 220://红感叹号
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 6*33, 23*33, HEIGHT,WIDTH);
                    break;
                case 221://=
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 9*33, 25*33, HEIGHT,WIDTH);
                    break;
                case 222://上楼图标
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,16 * 33,20 * 33, HEIGHT,WIDTH);
                    break;
                case 223://向下指
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,3 * 33,22 * 33, HEIGHT,WIDTH);
                    break;
                case 224://1
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,1 * 33,26 * 33, HEIGHT,WIDTH);
                    break;
                case 225://9
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,9 * 33,26 * 33, HEIGHT,WIDTH);
                    break;

                    //城堡
                case 226:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,12 * 33,0 * 33, HEIGHT,WIDTH);
                    break;
                case 227:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,13 * 33,0 * 33, HEIGHT,WIDTH);
                    break;
                case 228:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,12 * 33,1 * 33, HEIGHT,WIDTH);
                    break;
                case 229:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,13 * 33,1 * 33, HEIGHT,WIDTH);
                    break;


                //魔法阵
                case 241://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 14*33, 2*33, HEIGHT,WIDTH);
                    break;
                case 242://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 15*33, 2*33, HEIGHT,WIDTH);
                    break;
                case 243://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,16 * 33,2 * 33, HEIGHT,WIDTH);
                    break;
                case 244://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 14*33, 3*33, HEIGHT,WIDTH);
                    break;
                case 245://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 15*33, 3*33, HEIGHT,WIDTH);
                    break;
                case 246://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,16 * 33,3 * 33, HEIGHT,WIDTH);
                    break;
                case 247://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 14*33, 4*33, HEIGHT,WIDTH);
                    break;
                case 248:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 15*33, 4*33, HEIGHT,WIDTH);
                    break;
                case 249:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,16 * 33,4 * 33, HEIGHT,WIDTH);
                    break;

                 //黑海
                case 250://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 6*33, 11*33, HEIGHT,WIDTH);
                    break;
                case 251://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 7*33, 11*33, HEIGHT,WIDTH);
                    break;
                case 252://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,8 * 33,11 * 33, HEIGHT,WIDTH);
                    break;
                case 253://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 6*33, 12*33, HEIGHT,WIDTH);
                    break;
                case 254://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 7*33, 12*33, HEIGHT,WIDTH);
                    break;
                case 255://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,8 * 33,12 * 33, HEIGHT,WIDTH);
                    break;
                case 256://
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 6*33, 13*33, HEIGHT,WIDTH);
                    break;
                case 257:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 7*33, 13*33, HEIGHT,WIDTH);
                    break;
                case 258:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,8 * 33,13 * 33, HEIGHT,WIDTH);
                    break;



                case 259://棋子
                    painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , mine, 0 * 33, 0* 33, HEIGHT,WIDTH);
                    break;
                case 260://A
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 0*33, 27*33, HEIGHT,WIDTH);
                    break;
                case 261://B
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 1*33, 27*33, HEIGHT,WIDTH);
                    break;
                case 262://C
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,2 * 33,27 * 33, HEIGHT,WIDTH);
                    break;
                case 263://D
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 3*33, 27*33, HEIGHT,WIDTH);
                    break;
                case 264://E
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 4*33, 27*33, HEIGHT,WIDTH);
                    break;
                case 265://F
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,5 * 33,27 * 33, HEIGHT,WIDTH);
                    break;
                case 266://G
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 6*33, 27*33, HEIGHT,WIDTH);
                    break;
                case 267://H
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 7*33, 27*33, HEIGHT,WIDTH);
                    break;
                case 268://I
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,8 * 33,27 * 33, HEIGHT,WIDTH);
                    break;
                case 269://J
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,9 * 33,27 * 33, HEIGHT,WIDTH);
                    break;

                case 270://K
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 0*33, 28*33, HEIGHT,WIDTH);
                    break;
                case 271://L
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 1*33, 28*33, HEIGHT,WIDTH);
                    break;
                case 272://M
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,2 * 33,28 * 33, HEIGHT,WIDTH);
                    break;
                case 273://N
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 3*33, 28*33, HEIGHT,WIDTH);
                    break;
                case 274://O
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 4*33, 28*33, HEIGHT,WIDTH);
                    break;
                case 275://P
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,5 * 33,28 * 33, HEIGHT,WIDTH);
                    break;
                case 276://Q
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 6*33, 28*33, HEIGHT,WIDTH);
                    break;
                case 277://R
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 7*33, 28*33, HEIGHT,WIDTH);
                    break;
                case 278://S
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,8 * 33,28 * 33, HEIGHT,WIDTH);
                    break;
                case 279://T
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,9 * 33,28 * 33, HEIGHT,WIDTH);
                    break;

                case 280://U
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 0*33, 29*33, HEIGHT,WIDTH);
                    break;
                case 281://V
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,1 * 33,29 * 33, HEIGHT,WIDTH);
                    break;
                case 282://W
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 2*33, 29*33, HEIGHT,WIDTH);
                    break;
                case 283://X
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 3*33, 29*33, HEIGHT,WIDTH);
                    break;
                case 284://Y
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,4 * 33,29 * 33, HEIGHT,WIDTH);
                    break;
                case 285://Z
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,5 * 33,29 * 33, HEIGHT,WIDTH);
                    break;


                case 22:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,18 * 33,2 * 33, HEIGHT,WIDTH);
                    break;
                case 23:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,18 * 33,3 * 33, HEIGHT,WIDTH);
                    break;
                case 24:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,18 * 33,4 * 33, HEIGHT,WIDTH);
                    break;
                case 27:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,19 * 33,2 * 33, HEIGHT,WIDTH);
                    break;
                case 28:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,19 * 33,3 * 33, HEIGHT,WIDTH);
                    break;
                case 29:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,19 * 33,4 * 33, HEIGHT,WIDTH);
                    break;


                case 37:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,14 * 33,17 * 33, HEIGHT,WIDTH);
                    break;
                case 38:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,15 * 33,17 * 33, HEIGHT,WIDTH);
                    break;
                case 39:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,16 * 33,17 * 33, HEIGHT,WIDTH);
                    break;
                case 59:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,14 * 33,18 * 33, HEIGHT,WIDTH);
                    break;
                case 60:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,15 * 33,18 * 33, HEIGHT,WIDTH);
                    break;
                case 61:
                    painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,16 * 33,18 * 33, HEIGHT,WIDTH);
                    break;





                }
            }
        }
 //绘制第七层扫雷
             if(one.position.layler == 6)
             {
                 for(int i=1;i<=9;i++)
                 {
                     for(int j=1;j<=9;j++)
                     {
                         if(mineFlagMap[i-1][j-1] == 0)
                         {
                             painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , mine,  33, 0* 33, HEIGHT,WIDTH);
                         }
                         else if(mineFlagMap[i-1][j-1] == 2)
                         {
                             painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , mine, 0 * 33, 0* 33, HEIGHT,WIDTH);
                         }
                         else
                         {
                             if(map.getT_Map(6,i,j) == 230)
                             {
                                 painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , mine, 3 * 33, 0* 33, HEIGHT,WIDTH);
                             }
                             else if(map.getT_Map(6,i,j) == 239)
                             {
                                 painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , mine, 2 * 33, 0* 33, HEIGHT,WIDTH);
                             }
                             else
                             {
                                 painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , jpg, (map.getT_Map(6,i,j)-230 )* 33, 26* 33, HEIGHT,WIDTH);
                             }
                         }
                     }
                 }
             }
//绘制主角
        //先暂时用上面四张图，后面加定时器再用另外四张
             if(!one.isElf)//变精灵之后不绘制
             {
                 switch (one.One_Direction) {
                     case 0 :
                         painter.drawPixmap( one.position.y * 33 + map_XOffset , one.position.x * 33 +map_YOffset , character, 2 * 33, 0 , HEIGHT,WIDTH);
                         break;
                     case 1:
                         painter.drawPixmap( one.position.y * 33 + map_XOffset , one.position.x * 33 +map_YOffset , character, 3 * 33, 0, HEIGHT,WIDTH);
                         break;
                     case 2:
                         painter.drawPixmap( one.position.y * 33 + map_XOffset , one.position.x * 33 +map_YOffset , character, 0, 0, HEIGHT,WIDTH);
                         break;
                     case 3:
                         painter.drawPixmap( one.position.y * 33 + map_XOffset , one.position.x * 33 +map_YOffset , character, 1*33, 0, HEIGHT,WIDTH);
                         break;
                 }
             }

//绘制/钥匙/血瓶/除NPC之外的物品
            for(int i= 0;i<13;i++)
            {
                for(int j = 0;j<13 ; j++)
                {
                    switch (map.getS_Map(one.position.layler,i,j))
                    {
                    case 63://黄钥匙
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , doorAndKey, 7 * 33, 0, HEIGHT,WIDTH);
                        break;
                    case 64://蓝钥匙
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , doorAndKey, 6 * 33, 0, HEIGHT,WIDTH);
                        break;
                    case 65://红钥匙
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , doorAndKey, 5 * 33, 0, HEIGHT,WIDTH);
                        break;
                    case 66://绿钥匙
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , doorAndKey, 8 * 33, 0, HEIGHT,WIDTH);
                        break;

                    case 67://红血瓶
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 10 * 33,22 * 33,  HEIGHT,WIDTH);
                        break;
                    case 68://蓝血瓶
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 11 * 33,22 * 33,  HEIGHT,WIDTH);
                        break;
                    case 69://黄血瓶
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 12 * 33,22 * 33,  HEIGHT,WIDTH);
                        break;
                    case 70://绿血瓶
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 13 * 33,22 * 33,  HEIGHT,WIDTH);
                        break;

                    case 71://蓝宝石 冰
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 16 * 33,22 * 33,  HEIGHT,WIDTH);
                        break;
                    case 72://红宝石 火
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 15 * 33,22 * 33,  HEIGHT,WIDTH);
                        break;
                    case 73://黄宝石 雷
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 17 * 33,22 * 33,  HEIGHT,WIDTH);
                        break;
                    case 74://白宝石 魔
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 19 * 33,22 * 33,  HEIGHT,WIDTH);
                        break;

                    case 75:
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 14 * 33,23 * 33,  HEIGHT,WIDTH);
                        break;
                    case 76:
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 19 * 33,23 * 33,  HEIGHT,WIDTH);
                        break;


                    case 81://黄门
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , doorAndKey, 3 * 33, 0, HEIGHT,WIDTH);
                        break;
                    case 82://蓝门
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , doorAndKey, 2 * 33, 0, HEIGHT,WIDTH);
                        break;
                    case 83://红门
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , doorAndKey, 1 * 33, 0, HEIGHT,WIDTH);
                        break;
                    case 84://绿门
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , doorAndKey, 4 * 33, 0, HEIGHT,WIDTH);
                        break;
                    case 85://条件铁门
                        painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,  0 , 20 *33, HEIGHT,WIDTH);
                        break;
                    case 86://条件门
                        painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg, 4*33 , 20 *33, HEIGHT,WIDTH);
                        break;
                    //上下楼
                    case 50://扫雷通关出现的楼梯
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 16 * 33,20 * 33,  HEIGHT,WIDTH);
                        break;
                    case 51:
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 16 * 33,20 * 33,  HEIGHT,WIDTH);
                        break;
                    case 52:
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 16 * 33,19 * 33,  HEIGHT,WIDTH);
                        break;


                    case 181://NPC精灵
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 23 * 33,24 * 33,  HEIGHT,WIDTH);
                        break;
                    case 180://NPC商人
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 27 * 33,24 * 33,  HEIGHT,WIDTH);
                        break;
                    case 182://NPC公主
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 20 * 33,24 * 33,  HEIGHT,WIDTH);
                        break;
                    case 183://勇者变的精灵
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 22 * 33,24 * 33,  HEIGHT,WIDTH);
                        break;


                    case 190://龙
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  monster, 4 * 33,18 * 33,  HEIGHT,WIDTH);
                        break;
                    case 191://海怪
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  monster, 0 * 33,18 * 33,  HEIGHT,WIDTH);
                        break;
                    case 192:
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  monster, 5 * 33,14 * 33,  HEIGHT,WIDTH);
                        break;
                    case 193:
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  monster, 6 * 33,16 * 33,  HEIGHT,WIDTH);
                        break;
                    case 194:
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  monster, 6 * 33,14 * 33,  HEIGHT,WIDTH);
                        break;


//[90,95)宝物
                    case 90://图鉴
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 0 * 33,21 * 33,  HEIGHT,WIDTH);
                        break;
                    case 91://十字架
                         painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 4 * 33,21 * 33,  HEIGHT,WIDTH);
                        break;
                    case 92://硬币
                         painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 5 * 33,21 * 33,  HEIGHT,WIDTH);
                        break;
                    case 93://net
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 3 * 33,21 * 33,  HEIGHT,WIDTH);
                        break;
                    case 94://水壶
                          painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  jpg, 19 * 33,29 * 33,  HEIGHT,WIDTH);
                        break;



//[95,100)通过5条件
                    case 95://火
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  treasure, 0* 33,1 * 33,  HEIGHT,WIDTH);
                        break;
                    case 96://冰
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  treasure, 1 * 33,1 * 33,  HEIGHT,WIDTH);
                        break;
                    case 97://雷
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  treasure, 2 * 33,1 * 33,  HEIGHT,WIDTH);
                        break;
                    case 98://魔
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  treasure, 3 * 33,1 * 33,  HEIGHT,WIDTH);
                        break;
                    case 99://铁
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,  treasure, 4 * 33,1 * 33,  HEIGHT,WIDTH);
                        break;


                    case 77://直通10层的楼梯
                        painter.drawPixmap( j*33+  map_XOffset, i*33 + map_YOffset , jpg,18 * 33,19 * 33, HEIGHT,WIDTH);
                        break;
                    }
                }
            }
//绘制跟着你的公主
            if(one.withPrincess)
            {
                if(map.isAbleWalk(one.position.layler,one.position.x+1,one.position.y))//下
                {
                    painter.drawPixmap( one.position.y * 33 + map_XOffset , (one.position.x+1)*33 +map_YOffset ,  jpg, 20 * 33,24 * 33,  HEIGHT,WIDTH);
                }
                else if(map.isAbleWalk(one.position.layler,one.position.x-1,one.position.y))//上
                {
                    painter.drawPixmap( one.position.y * 33 + map_XOffset , (one.position.x-1)*33 +map_YOffset ,  jpg, 20 * 33,24 * 33,  HEIGHT,WIDTH);
                }
                else if(map.isAbleWalk(one.position.layler,one.position.x,one.position.y-1))
                {
                    painter.drawPixmap( (one.position.y-1) * 33 + map_XOffset , (one.position.x)*33 +map_YOffset ,  jpg, 20 * 33,24 * 33,  HEIGHT,WIDTH);
                }
                else if(map.isAbleWalk(one.position.layler,one.position.x,one.position.y+1))
                {
                    painter.drawPixmap( (one.position.y+1) * 33 + map_XOffset , (one.position.x)*33 +map_YOffset ,  jpg, 20 * 33,24 * 33,  HEIGHT,WIDTH);
                }
            }

//绘制怪物
            for(int i= 0;i<13;i++)
            {
                for(int j = 0;j<13 ; j++)
                {
                    int numId = map.getS_Map(one.position.layler,i,j);
                    //绘制史莱姆
                    if(numId >=SLIME && numId < SLIME+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterSlime[numId - SLIME]->getPainterX()*33,
                            map.monsterSlime[numId - SLIME]->getPainterY()*33,  HEIGHT, WIDTH);
                    }
                    //绘制蝙蝠
                    else if(numId >= BAT && numId <  BAT+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterBat[numId -BAT]->getPainterX()*33,
                            map.monsterBat[numId -BAT]->getPainterY()*33, HEIGHT, WIDTH);
                    }
                    //绘制骷髅
                    else if(numId >=SKELETON && numId <  SKELETON+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterSkeleton[numId -SKELETON]->getPainterX()*33,
                            map.monsterSkeleton[numId -SKELETON]->getPainterY()*33,  HEIGHT, WIDTH);
                    }
                    else if(numId >=ORCISH && numId <  ORCISH+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterOrcish[numId -ORCISH]->getPainterX()*33,
                            map.monsterOrcish[numId -ORCISH]->getPainterY()*33, HEIGHT, WIDTH);
                    }
                    else if(numId >=MAGICER && numId <  MAGICER+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterMagicer[numId -MAGICER]->getPainterX()*33,
                            map.monsterMagicer[numId -MAGICER]->getPainterY()*33, HEIGHT, WIDTH);
                    }

                    else if(numId >=ELEMENTSTONE && numId <  ELEMENTSTONE+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterElementStone[numId -ELEMENTSTONE]->getPainterX()*33,
                            map.monsterElementStone[numId -ELEMENTSTONE]->getPainterY()*33,  HEIGHT, WIDTH);
                    }

                    else if(numId >=CRUSADEKNIGHT && numId <  CRUSADEKNIGHT+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterCrusadeKnight[numId -CRUSADEKNIGHT]->getPainterX()*33,
                            map.monsterCrusadeKnight[numId -CRUSADEKNIGHT]->getPainterY()*33,  HEIGHT, WIDTH);
                    }
                    else if(numId >=MATRIXKNIGHT && numId <  MATRIXKNIGHT+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterMatrixKnight[numId -MATRIXKNIGHT]->getPainterX()*33,
                            map.monsterMatrixKnight[numId -MATRIXKNIGHT]->getPainterY()*33,  HEIGHT, WIDTH);
                    }
                    else if(numId >=SWORDMAN && numId <  SWORDMAN+10)
                    {
                        painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset ,
                            monster,map.monsterSwordMan[numId -SWORDMAN]->getPainterX()*33,
                            map.monsterSwordMan[numId -SWORDMAN]->getPainterY()*33,  HEIGHT, WIDTH);
                    }
                }
            }


//绘制最近的战斗怪物UI
            if((monsterLatest >= 100 && monsterLatest <200)
                    ||(monsterLatest >= 300 && monsterLatest <310))
            {
                //头像
                if(monsterLatest<190 && monsterLatest>=180)
                {
                    switch (monsterLatest)
                    {
                    case 180://2层红色商人
                        painter.drawPixmap( 267, 384 , jpg,  27 * 33,24 * 33*2,  HEIGHT,WIDTH);
                        break;
                    case 182://公主
                        painter.drawPixmap( 267, 384 , jpg,  20 * 33,24 * 33*2,  HEIGHT,WIDTH);
                        break;
                    }
                }
                else
                {
                    painter.drawPixmap( 267, 384 , monster,  monsterLatestPainterX * 33,monsterLatestPainterY * 33,  HEIGHT,WIDTH);
                }

                //怪物血量
                int  monsterLatestHp_1[5] = {0};//存放需要绘制的五位数字
                int  monsterLatestTemp = monsterLatestHp;
                int  monsterLatest_i = 4;
                if(monsterLatestTemp > 0)
                {
                    while(monsterLatestTemp > 0)
                    {
                        monsterLatestHp_1[monsterLatest_i] = monsterLatestTemp%10;
                        monsterLatestTemp/=10;
                        monsterLatest_i--;
                    }
                    for(int j =0;j<5;j++)
                    {
                        painter.drawPixmap( 267+j*33-33*4, 417 , jpg, monsterLatestHp_1[j]* 33, 26 * 33, HEIGHT,WIDTH);
                    }
                }
                else
                {
                    painter.drawPixmap( 267, 417 , jpg, 0, 26 * 33, HEIGHT,WIDTH);
                }
                //怪物攻击力防御力
                int monsterLatestAtt[3]={0};//最高999
                int monsterLatestDen[3]={0};
                int monsterLatestTemp_1 = monsterLatestAttack;
                int monsterLatestTemp_2 = monsterLatestDefense;
                int monsterLatest_i1=2;

                while(monsterLatestTemp_1>0)//攻击力
                {
                    monsterLatestAtt[monsterLatest_i1] = monsterLatestTemp_1%10;
                    monsterLatestTemp_1/=10;
                    monsterLatest_i1--;
                }
                monsterLatest_i1=2;
                while(monsterLatestTemp_2>0)//防御力
                {
                    monsterLatestDen[monsterLatest_i1] = monsterLatestTemp_2%10;
                    monsterLatestTemp_2/=10;
                    monsterLatest_i1--;
                }
                for(int j =0;j<3;j++)
                {
                    painter.drawPixmap( 267+j*33-33*2, 450 , jpg, monsterLatestAtt[j]* 33, 26 * 33, HEIGHT,WIDTH);
                    painter.drawPixmap( 267+j*33-33*2, 450+33 , jpg, monsterLatestDen[j]* 33, 26 * 33, HEIGHT,WIDTH);
                }
            }

//绘制第六层数独
            if(one.position.layler == 5)
            {
                int numPater=0;
                for(int i=1;i<=9;i++)
                {
                    for(int j=1;j<=9;j++)
                    {
                        if((map.getS_Map(5,i,j)-200) != 0)
                        {
                            painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , jpg,(map.getS_Map(5,i,j)-200)* 33, 26* 33, HEIGHT,WIDTH);
                        }
                        else
                        {
                            if(numPater == 20)//第20个0为红色感叹号
                            {
                                painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , jpg, 6* 33, 23* 33, HEIGHT,WIDTH);
                            }
                            else
                            {
                                painter.drawPixmap( j * 33 + map_XOffset , i*33 +map_YOffset , jpg, 9* 33, 23* 33, HEIGHT,WIDTH);
                            }
                            numPater++;
                        }
                    }
                }
            }
        update();
}

void Tower::npcEvent(int n)
{
    switch (n)
    {
    case 181://精灵NPC
        diaElf.show();
        if(one.point>=100)
        {
            diaElf.setIsEnoughPoint(true);
        }
        else
        {
            diaElf.setIsEnoughPoint(false);
        }

        connect(&diaElf,SIGNAL(sendRecuoerate(int)),this,SLOT(recuoerate(int)));
        connect(&diaElf,SIGNAL(dedication(bool)),this,SLOT(beDedicated(bool)));
        break;

    case 180://商人
        diaMer.show();

        if(one.point >= merchantCost[diaMer.getEventNum()])
        {
            diaMer.setIsEnoughPoint(true);
        }
        else
        {
            diaMer.setIsEnoughPoint(false);
        }
        connect(&diaMer,SIGNAL(sendBuy(int)),this,SLOT(buy(int)));
        break;

    case 182:
        diaPri.show();
        connect(&diaPri,SIGNAL(sendWithPr(bool)),this,SLOT(withPri(bool)));

    }
}
//移动，根据目标位置触发不同事件
//上下左右0123
void Tower::move(int direction)
{
    //死亡判定
    if(one.HP <= 0)
    {
        gameDead();
    }

    switch (direction)
    {
        case 0:
        {
            Position p(one.position.layler,one.position.x-1,one.position.y);
            if(isMonster(p))
            {
                 moveEventAttack(one.position.layler,one.position.x-1,one.position.y);
            }
            else
            {
                moveEvent60(one.position.layler,one.position.x-1,one.position.y);
            }
            break;
        }

            case 1 :
        {
            //从背后攻击2倍攻击力
            Position p(one.position.layler,one.position.x+1,one.position.y);
            one.backAttack = true;
            if(isMonster(p))
            {
                moveEventAttack(one.position.layler,one.position.x+1,one.position.y);
            }
            else
            {
                moveEvent60(one.position.layler,one.position.x+1,one.position.y);
            }
            break;
        }
            case 2 :
        {
             Position p(one.position.layler,one.position.x,one.position.y-1);
            if(isMonster(p))
            {
                moveEventAttack(one.position.layler,one.position.x,one.position.y-1);
            }
            else
             {
                 moveEvent60(one.position.layler,one.position.x,one.position.y-1);
             }
             break;
        }
            case 3 :
        {
            Position p(one.position.layler,one.position.x,one.position.y+1);
            if(isMonster(p))
            {
                moveEventAttack(one.position.layler,one.position.x,one.position.y+1);
            }
            else
            {
                moveEvent60(one.position.layler,one.position.x,one.position.y+1);
            }
            break;
        }
    }

    if(haveCross)
    {
        one.Max_HP++;
        one.HP++;
    }
    existIsTruth();
    mapEvent();
    update();
}
//攻击和NPC
void Tower::moveEventAttack(int layler, int x, int y)
{
    int numId = map.getS_Map(layler,x,y);
    Position p(layler,x,y);

    if(numId >=SLIME && numId<SLIME+10 )//目标大于100小于110为史莱姆
    {
        moveEventAttackWithMonster(map.monsterSlime[numId-SLIME],p);
    }

    else if(numId >=BAT && numId <BAT+10 )
    {
        moveEventAttackWithMonster(map.monsterBat[numId-BAT],p);
    }

    else if(numId >=SKELETON && numId <SKELETON+10 )
    {
        moveEventAttackWithMonster(map.monsterSkeleton[numId-SKELETON],p);
    }
    else if(numId >=ORCISH && numId <ORCISH+10 )
    {
        moveEventAttackWithMonster(map.monsterOrcish[numId-ORCISH],p);
        map.monsterOrcish[numId - ORCISH]->getAnger();//这个逼更愤怒了
        qDebug()<< "这个比的攻击力提升了"<<map.monsterOrcish[numId - ORCISH]->getAttack();
    }
    else if(numId >=MAGICER && numId <MAGICER+10 )
    {
        moveEventAttackWithMonster(map.monsterMagicer[numId-MAGICER],p);
    }


    else if(numId >=ELEMENTSTONE && numId <ELEMENTSTONE+10)
    {
        moveEventAttackWithMonster(map.monsterElementStone[numId-ELEMENTSTONE],p);
        map.monsterElementStone[numId - ELEMENTSTONE]->getDefenseAdd();//更坚挺了
        qDebug()<<"防御力："<<map.monsterElementStone[numId - ELEMENTSTONE]->getDefense();
    }
    else if(numId >=CRUSADEKNIGHT && numId <CRUSADEKNIGHT+10)
    {
        moveEventAttackWithMonster(map.monsterCrusadeKnight[numId-CRUSADEKNIGHT],p);
    }
    else if(numId >=MATRIXKNIGHT && numId <MATRIXKNIGHT+10)
    {
        moveEventAttackWithMonster(map.monsterMatrixKnight[numId-MATRIXKNIGHT],p);
    }

    else if(numId >=SWORDMAN && numId <SWORDMAN+10)
    {
        moveEventAttackWithMonster(map.monsterSwordMan[numId-SWORDMAN],p);
    }
    else if(numId >=BOSS && numId <BOSS+10)
    {
        moveEventAttackWithMonster(map.Boss[numId-BOSS],p);
    }

//[180,200)为NPC
        else if(numId >=NPC && numId < NPC+10)
        {
            //从背后
            if(one.backAttack && one.One_Direction==1)
            {

                moveEventAttackWithMonster(map.monsterNpc[numId-NPC],p);
            }
            else//为NPC事件
            {
                npcEvent(numId);
            }
        }
}

void Tower::moveEventAttackWithMonster(Monster *monster,Position p)
{
        if(one.backAttack)
        {one.Attack*=2;}
        if(one.Agile >= monster->getAgile())//敏捷比较
        {//先手攻击
            acttack(monster);
            monsterDie(monster,p);
            if(monster->getHP() <= 0)//如果直接秒杀则不用再受伤害
              {
                  if(one.backAttack)
                  {
                      one.Attack/=2;
                      one.backAttack=false;
                  }
                  return;
              }
              else
              {
                monster->attack(one);
              }
         }

        else
        {//后手攻击
            monster->attack(one);
            acttack(monster);
            monsterDie(monster,p);
        }
        if(one.backAttack)
        {
            one.Attack/=2;
            one.backAttack=false;
        }

}
//默认[100,200)  [300,350)是怪物
bool Tower::isMonster(Position p)
{
    if((map.getS_Map(p.layler,p.x,p.y) < 200 && map.getS_Map(p.layler,p.x,p.y) >= 100)
 || (map.getS_Map(p.layler,p.x,p.y) >= 300 &&  map.getS_Map(p.layler,p.x,p.y) < 350))
    {
        return true;
    }
    return false;
}

bool Tower::isMonster(int layler, int x, int y)
{
    if((map.getS_Map(layler,x,y) < 200 && map.getS_Map(layler,x,y) >= 100)
 || (map.getS_Map(layler,x,y) >= 300 &&  map.getS_Map(layler,x,y) < 310))
    {
        return true;
    }
    return false;
}

int Tower::isWhatKindMonster(Position p)
{
    if(map.getS_Map(p.layler,p.x,p.y) >=170 && map.getS_Map(p.layler,p.x,p.y) <180)//矩阵骑士
    {
        return MATRIXKNIGHT;
    }
    else if (map.getS_Map(p.layler,p.x,p.y) >=100 && map.getS_Map(p.layler,p.x,p.y) <110)
    {
        return SLIME;
    }
    else if (map.getS_Map(p.layler,p.x,p.y) >=110 && map.getS_Map(p.layler,p.x,p.y) <120)
    {
        return BAT;
    }
    else if (map.getS_Map(p.layler,p.x,p.y) >=120 && map.getS_Map(p.layler,p.x,p.y) <130)
    {
        return SKELETON;
    }
    else if (map.getS_Map(p.layler,p.x,p.y) >=130 && map.getS_Map(p.layler,p.x,p.y) <140)
    {
        return ORCISH;
    }
    else if (map.getS_Map(p.layler,p.x,p.y) >=140 && map.getS_Map(p.layler,p.x,p.y) <150)
    {
        return MAGICER;
    }
    else if (map.getS_Map(p.layler,p.x,p.y) >=150 && map.getS_Map(p.layler,p.x,p.y) <160)
    {
        return ELEMENTSTONE;
    }
    else if (map.getS_Map(p.layler,p.x,p.y) >=160 && map.getS_Map(p.layler,p.x,p.y) <170)
    {
        return CRUSADEKNIGHT;
    }
    else if (map.getS_Map(p.layler,p.x,p.y) >=300 && map.getS_Map(p.layler,p.x,p.y) <310)
    {
        return SWORDMAN;
    }
    return 0;
}

int Tower::isWhatKindMonster(int layler, int x, int y)
{
    if(map.getS_Map(layler,x,y) >=170 && map.getS_Map(layler,x,y) <180)//矩阵骑士
    {
        return MATRIXKNIGHT;
    }
    else if (map.getS_Map(layler,x,y) >=100 && map.getS_Map(layler,x,y) <110)
    {
        return SLIME;
    }
    else if (map.getS_Map(layler,x,y) >=110 && map.getS_Map(layler,x,y) <120)
    {
        return BAT;
    }
    else if (map.getS_Map(layler,x,y) >=120 && map.getS_Map(layler,x,y) <130)
    {
        return SKELETON;
    }
    else if (map.getS_Map(layler,x,y) >=130 && map.getS_Map(layler,x,y) <140)
    {
        return ORCISH;
    }
    else if (map.getS_Map(layler,x,y) >=140 && map.getS_Map(layler,x,y) <150)
    {
        return MAGICER;
    }
    else if (map.getS_Map(layler,x,y) >=150 && map.getS_Map(layler,x,y) <160)
    {
        return ELEMENTSTONE;
    }
    else if (map.getS_Map(layler,x,y) >=160 && map.getS_Map(layler,x,y) <170)
    {
        return CRUSADEKNIGHT;
    }
    else if (map.getS_Map(layler,x,y) >=300 && map.getS_Map(layler,x,y) <310)
    {
        return SWORDMAN;
    }
    else if (map.getS_Map(layler,x,y) >=180 && map.getS_Map(layler,x,y) <190)
    {
        return NPC;
    }
    else if (map.getS_Map(layler,x,y) >=190 && map.getS_Map(layler,x,y) <200)
    {
        return BOSS;
    }
    return 0;
}

void Tower::treasure()
{
    if(one.treasure!=91)
    {
        haveCross = false;
    }
    if(one.treasure!=92)
    {
        one.haveCoin = false;
    }

    switch (one.treasure)
    {

    case 90://图鉴
    {
        Monster *monsterTemp = nullptr;
        if(one.treasures[0][0])
        {
            switch (one.One_Direction)
            {
                case 0:
                {
                    monsterTemp =  getMonster(one.position.layler,one.position.x-1,one.position.y);
                    break;
                }
                case 1:
                {
                    monsterTemp =  getMonster(one.position.layler,one.position.x+1,one.position.y);
                    break;
                }
                case 2 :
                {
                    monsterTemp =  getMonster(one.position.layler,one.position.x,one.position.y-1);
                    break;
                }
                case 3 :
                {
                    monsterTemp =  getMonster(one.position.layler,one.position.x,one.position.y+1);
                    break;
                }
            }
        }
        if(monsterTemp != nullptr)
        {
            Note *note = new Note();
            note->show();
            connect(this,SIGNAL(noteSendData(Monster *)),note,SLOT(noteRecvData(Monster *)));
            emit noteSendData(monsterTemp);
        }
    }
        break;
    case 91://十字架
        haveCross =true;
        break;
    case 92://硬币
        one.haveCoin =true;
        break;

    case 93://net
        if(one.treasures[3][0])
        {
            switch (one.One_Direction)
            {
                case 0:
                {
                    Position p(one.position.layler,one.position.x-1,one.position.y);
                    net(p);
                    break;
                }
                case 1:
                {
                    Position p(one.position.layler,one.position.x+1,one.position.y);
                    net(p);
                    break;
                }
                case 2 :
                {
                    Position p(one.position.layler,one.position.x,one.position.y-1);
                    net(p);
                    break;
                }
                case 3 :
                {
                    Position p(one.position.layler,one.position.x,one.position.y+1);
                    net(p);
                    break;
                }
            }
        }
        break;
    case 94://kettle
        if(one.treasures[4][0])
        {
            switch (one.One_Direction)
            {
                case 0:
                {
                    Position p(one.position.layler,one.position.x-1,one.position.y);
                    kettle(p);
                    break;
                }
                case 1:
                {
                    Position p(one.position.layler,one.position.x+1,one.position.y);
                    kettle(p);
                    break;
                }
                case 2 :
                {
                    Position p(one.position.layler,one.position.x,one.position.y-1);
                    kettle(p);
                    break;
                }
                case 3 :
                {
                    Position p(one.position.layler,one.position.x,one.position.y+1);
                    kettle(p);
                    break;
                }
            }
            break;
        }
    }
}

void Tower::net(Position( p))
{
    if(isSlimeOrBat(p) == 1)//抓史莱姆所有元素攻击力 10%
    {
        map.setS_Map(p,0);
        for(int i=1;i<5;i++)
        {
            one.Element_Attack[i] +=  one.Element_Attack[i]*0.1;
        }

    }
    else if(isSlimeOrBat(p) == 2)//抓蝙蝠攻防+10%
    {
         map.setS_Map(p,0);

         one.Attack+=  one.Attack*0.1;

         one.Defense+= one.Defense*0.1;
    }
   else
    {
        qDebug()<<"net 只能对蝙蝠和史莱姆使用";
    }
}

void Tower::kettle(Position p)
{
    switch (map.getT_Map(p))
    {
    case 7:
        one.treasures[4][0]= 4;//毒,多次
        break;
    case 8:
        one.treasures[4][0] = 2;
        map.setT_Map(p,17);
        break;
    case 9:
        one.treasures[4][0]= 3;//火
        map.setT_Map(p,30);
        break;
    default:
        pourWater(one.treasures[4][0]);
        break;

    }

}

int Tower::isSlimeOrBat(Position p)
{
    if(map.getS_Map(p) >= SLIME  && map.getS_Map(p) < SLIME+10 )
    {
        return 1;
    }
    else if(map.getS_Map(p) >= BAT  && map.getS_Map(p) < BAT+10)
    {
        return 2;
    }
    else
        return 0;
}

void Tower::pourWater(int treasureNum)
{
    switch (treasureNum)
    {
    case 2://水

        //当前页面所有水熟悉怪物冰+100
        for(int i=0;i<13;i++)
        {
            for(int j=0;j<13;j++)
            {
                if(getMonster(one.position.layler,i,j) != nullptr)
                {
                    if(getMonster(one.position.layler,i,j)->getAttack_Element() == ICE)
                    {
                        getMonster(one.position.layler,i,j)->setElement_Attack(ICE,getMonster(one.position.layler,i,j)->getElement_Attack(ICE)+100);//冰攻击力+100
                    }
                    else
                    {
                        //其他冰抗性-1
                        getMonster(one.position.layler,i,j)->setResistance(ICE,getMonster(one.position.layler,i,j)->getResistance(ICE)-1);
                    }
                }
            }
        }
        //主角冰攻+50，冰抗+0.3
        one.Element_Attack[ICE]+=50;
        one.Resistance[ICE]+=0.3;
        one.treasures[4][0] = 1;//设置瓶子为初始状态
        break;
    case 3://火
        for(int i=0;i<13;i++)
        {
            for(int j=0;j<13;j++)
            {
                if(getMonster(one.position.layler,i,j) != nullptr)
                {
                    if(getMonster(one.position.layler,i,j)->getAttack_Element() == FIRE)
                    {
                        //火攻+100
                        getMonster(one.position.layler,i,j)->setElement_Attack(FIRE,getMonster(one.position.layler,i,j)->getElement_Attack(FIRE)+100);
                    }
                    else
                    {
                        //其他怪物 火抗-1
                        getMonster(one.position.layler,i,j)->setResistance(FIRE,getMonster(one.position.layler,i,j)->getResistance(FIRE)-1);
                    }
                }
            }
        }
        one.Element_Attack[FIRE]+=50;
        one.Resistance[FIRE]+=0.3;
         one.treasures[4][0] = 1;
        break;
    case 4://毒
        for(int i=0;i<13;i++)
        {
            for(int j=0;j<13;j++)
            {
                if( isMonster(one.position.layler,i,j))
                {
                    int num = (getMonster(one.position.layler,i,j)->getHP()-100)>0 ? (getMonster(one.position.layler,i,j)->getHP()-100):0;
                    getMonster(one.position.layler,i,j)->setHP(num);
                    if(num == 0)//系内
                    {map.setS_Map(one.position.layler,i,j,0);}
                }
            }
        }
        one.HP-=100;
        one.Max_HP-=100;//最大血量也在减//可多次使  用
        break;
    }
}
//不找NPC
Monster *Tower::getMonster(int layler,int x,int y)
{
    if( isMonster(layler,x,y))
    {
        int num =map.getS_Map(layler,x,y);
        qDebug()<<num;
        switch (isWhatKindMonster(layler,x,y))
        {
        case SLIME:
            return map.monsterSlime[num - SLIME];
        case BAT:
            return map.monsterBat[num - BAT];
        case SKELETON:
            return map.monsterSkeleton[num - SKELETON];
        case ORCISH:
            return map.monsterOrcish[num - ORCISH];
        case MAGICER:
            return map.monsterMagicer[num - MAGICER];
        case ELEMENTSTONE:
            return map.monsterElementStone[num - ELEMENTSTONE];
        case CRUSADEKNIGHT:
            return map.monsterCrusadeKnight[num -CRUSADEKNIGHT];
        case MATRIXKNIGHT:
            return map.monsterMatrixKnight[num -MATRIXKNIGHT];
        case SWORDMAN:
            return map.monsterSwordMan[num - SWORDMAN];
        case NPC:
            return map.monsterNpc[num - NPC];
        case BOSS:
            return map.Boss[num - BOSS];
        default:
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}



void Tower::moveEvent60(int layler, int x, int y)
{
    switch (map.getS_Map(layler,x,y))
    {
    case 61:
    case 62:
    case 0://无事件发生正常移动
       if(map.isAbleWalk(layler,x,y))
       {
        switch (one.One_Direction)
        {
        case 0:
            one.position.x-=1;
            break;
        case 1:
            one.position.x+=1;
            break;
        case 2:
            one.position.y-=1;
            break;
        case 3:
            one.position.y+=1;
            break;
        }
       }
          break;
    case 63://目标位置是黄钥匙
          map.setS_Map(layler,x,y,0);//目标位置钥匙消失
          one.key[0]++;//主角身上黄钥匙+1
          break;          
    case 64://目标位置是蓝钥匙
        map.setS_Map(layler,x,y,0);
        one.key[1]++;
        break;
    case 65://目标位置是红钥匙
        map.setS_Map(layler,x,y,0);
        one.key[2]++;
        break;
    case 66://目标位置是绿钥匙
        map.setS_Map(layler,x,y,0);
        one.key[3]++;
        break;

    case 67://目标位置是红血瓶
       map.setS_Map(layler,x,y,0);//目标位置血瓶消失
        one.Max_HP+=200;
        break;
    case 68://目标位置是蓝血瓶
        map.setS_Map(layler,x,y,0);
        one.Resistance[1]+=0.05;
        one.Resistance[2]+=0.05;
        one.Resistance[3]+=0.05;
        one.Resistance[4]+=0.05;
        break;
    case 69://目标位置是黄血瓶
        map.setS_Map(layler,x,y,0);
        one.Element_Attack[1]+=5;
        one.Element_Attack[2]+=5;
        one.Element_Attack[3]+=5;
        one.Element_Attack[4]+=5;
        break;
    case 70://目标位置是绿血瓶
        one.Attack+=10;
        one.Defense+=10;
        map.setS_Map(layler,x,y,0);
        break;

    case 71://目标位置是蓝宝石
        map.setS_Map(layler,x,y,0);
        one.Element_Attack[1]+=15;
        break;
    case 72://目标位置是红宝石
        map.setS_Map(layler,x,y,0);
        one.Element_Attack[3]+=15;
        break;
    case 73://目标位置是黄宝石
        map.setS_Map(layler,x,y,0);
        one.Element_Attack[2]+=15;
        break;
    case 74://目标位置是白宝石
        map.setS_Map(layler,x,y,0);
        one.Element_Attack[4]+=15;
        break;

    case 75:
        map.setS_Map(layler,x,y,0);
        one.Attack+=100;
        break;
    case 76:
        map.setS_Map(layler,x,y,0);
        one.Defense+=100;
        break;
    case 77://直接通10层
        one.position.layler =10;
        one.position.x =11;
        one.position.y =6;
        one.whatsYourEnd =6;
        break;

    case 81://目标是黄门
        if(one.key[0]>=1)
        {
           one.key[0]--;
           map.setS_Map(layler,x,y,0);
        }
        break;
    case 82://目标是蓝门
        if(one.key[1]>=1)
        {
           one.key[1]--;
           map.setS_Map(layler,x,y,0);
        }
        break;
    case 83://目标是红门
        if(one.key[2]>=1)
        {
           one.key[2]--;
           map.setS_Map(layler,x,y,0);
        }
        break;
    case 84://目标是绿门
        if(one.key[3]>=1)
        {
           one.key[3]--;
           map.setS_Map(layler,x,y,0);
        }
        break;

//90-99
    case 90:
        one.treasures[0][0] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 91:
        one.treasures[1][0] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 92:
        one.treasures[2][0] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 93:
        one.treasures[3][0] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 94:
        one.treasures[4][0] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 95://火
        one.treasures[0][1] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 96:
        one.treasures[1][1] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 97:
        one.treasures[2][1] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 98:
        one.treasures[3][1] =1;
        map.setS_Map(layler,x,y,0);
        break;
    case 99:
        one.treasures[4][1] =1;
        map.setS_Map(layler,x,y,0);
        break;



    case 40://假墙
        map.setS_Map(layler,x,y,0);
        map.setT_Map(layler,x,y,14);//设置为可通行地
        break;
    case 41:
      map.setS_Map(layler,x,y,40);
      break;
    case 42://深度假墙 需要撞三次
      map.setS_Map(layler,x,y,41);
      break;    
    case 47://深度假墙 需要撞4次
      map.setS_Map(layler,x,y,42);
      break;
    case 48://深度假墙 需要撞5次
      map.setS_Map(layler,x,y,47);
      break;

    case 43://假墙，打开后是下一层 51
        map.setS_Map(layler,x,y,51);
        break;
    case 44:
      map.setS_Map(layler,x,y,43);
      break;
    case 45://深度假墙 需要撞三次
      map.setS_Map(layler,x,y,44);
      break;



    case 46://数独开始
        sudu();
        break;
    case 49://扫雷开始
        mine();
        break;
    case 50://扫雷通关楼梯
        floorChange(1);
        if(!eventList[5])
        {
             eventList[6] =true;
        }

        break;
    case 51://下一层
        floorChange(1);
        break;
    case 52://上一层
        floorChange(-1);
        break;

    case 57:
        map.setS_Map(layler,x,y,91);
        map.setT_Map(layler,x,y,14);//设置为可通行地
        break;

//第八层转换楼梯
    case 53:
        sudu();
        break;
    case 54:
        mine();
        break;
    case 55:
        floorChange(1);
        break;
    case 56:
        floorChange(-1);
        break;



//判断楼梯真假——————————————————————————————————————————————————————————————
    case 210:
        unReal(0);
        break;
    case 211:
        unReal(1);
        break;
    case 212:
        unReal(2);
        break;
    case 213:
        unReal(3);
        break;
    case 214:
        unReal(4);
        break;
    case 215:
        unReal(5);
        break;
    case 216:
        unReal(6);
        break;
    case 217:
        unReal(7);
        break;
    case 218:
        unReal(8);
        break;
//—————————————————————————————————————————————————————————————————————————————
    case 254://黑海中央
        one.position.layler = 10;
        one.position.x = 11;
        one.position.y = 6;
        break;
    case 245:
        if(one.getFragment())
        {
            switch (one.whatsYourEnd)
            {
            case 1:
                    one.position.x = 9;
                    one.position.y = 10;
                break;
            case 2:
            case 3:
                one.position.x = 10;
                one.position.y = 5;
                break;
            case 4:
                //进入结局二图
                one.position.layler = 10;
                one.position.x = 11;
                one.position.y = 6;
                break;
            }
        }
        else
        {
            one.position.x +=3;
        }
        break;


    case 58://进入结局一图 见魔王
        one.position.layler = 9;
        one.position.x = 11;
        one.position.y = 6;
        break;
    case 59://逃出生天
        switch (one.whatsYourEnd) //1鲨鹿 2宽恕 3购物 4跑路
        {
        case 2:
            QMessageBox::about(this, "你逃了出来", "你和公主从塔里逃了出来，但第二天公主就不见了踪影，你知道她要继续她那被暂停了的人生了，"
                                              "但你却不敢多停留，待到远处回头望，魔塔矗立依旧。");
        case 3:
            QMessageBox::about(this, "你逃了出来", "芒力迟迟不见你出来，早已独自跑了路，塔里的经历压得你喘不过气，没有追兵"
                                              "但你却不敢多停留，待到远处回头望，魔塔矗立依旧。");
            break;
        case 4:
            QMessageBox::about(this, "你路过了此地", "你是一个勇者，更是一个经验丰富的旅人，你完全知晓如何保持过路者和当地人的之间的关系平衡，你行色匆匆，无心"
                                               "此处美景，些许纷扰过后，一切又归平静，魔塔矗立依旧，仿佛你未曾来过。");
            break;
        case 6:
            QMessageBox::about(this, "你解除了诅咒", "顺着精灵身后的楼梯，你就这么莫名其妙的走了出来。你感觉到你改变了什么影响着此地的东西，"
                                               "现在魔塔只是一座普通的建筑了，你没做停留，继续你那被暂停的人生了。");
            break;

        }
        this->close();
        break;
    }
}

void Tower::monsterDie(Monster *monster,Position pos)
{
    if(monster->getHP() <= 0)
    {
        map.setS_Map(pos.layler,pos.x,pos.y,0);//目标位置置0 怪物消失
        monsterLatest = 0;
    }
    else
    {
        //设置最近战斗的怪物的血量攻击和防御
        monsterLatest = map.getS_Map(pos.layler,pos.x,pos.y);
        monsterLatestPainterX = monster->getPainterX();
        monsterLatestPainterY = monster->getPainterY();
        monsterLatestHp = monster->getHP();
        monsterLatestAttack = monster->getAttack();
        monsterLatestDefense = monster->getDefense();
    }
}

void Tower::acttack(Monster *monster)
{
    //单属性攻击
            monster->setHP( monster->getHP()-(one.Attack*(1-monster->getDefense()/(monster->getDefense() + 100))*(1-monster->getAttack_Type_Resistance(one.Attack_Type)) * 0.5
          + one.Element_Attack[one.Attack_Element] * (1-monster->getDefense()/(monster->getDefense()+50)) *(1-monster->getResistance(one.Attack_Element)) * 0.5));
            one.getReward(monster->getPoint());//攻击获得一次奖励
}

//地图事件
void Tower::mapEvent()
{
    if(eventList[6])//事件5 、6扫雷通关楼梯事件
    {
            //奖励出现
            map.setS_Map(6,3,11,99);//宽恕  五个条件之一
            map.setS_Map(6,4,11,70);
            map.setS_Map(6,5,11,70);
            map.setS_Map(6,6,11,71);
            map.setS_Map(6,7,11,72);
            map.setS_Map(6,8,11,73);
            map.setS_Map(6,8,11,74);
            //祭坛封死
            map.setT_Map(6,11,2,12);
            map.setT_Map(6,9,10,12);

            eventList[5] = true;
            eventList[6] = false;
            QMessageBox::about(this, "脑海里的声音", "解救之道，就在其中");
    }


    switch (one.position.layler)//楼层事件
    {
    case 1://事件0 二层红商人死亡
        if(!eventList[0])
        {
            if(  map.getS_Map(1,2,10) == 0 ||  eventList[14]) //1,2,10
            {
                map.setS_Map(1,5,7,0);//铁门消失
                map.setS_Map(1,2,8,72);
                map.setS_Map(1,2,7,72);
                map.setS_Map(1,3,8,67);
                map.setS_Map(1,3,7,67);
                map.setS_Map(1,4,7,65);
                map.setS_Map(1,4,8,65);
                eventList[0] = 1;//表示已经触发
                eventList[14] = false;

            }
        }


        if(!eventList[13])
        {
            if(map.getS_Map(1,4,10) == 0)//开黄门,精灵对话分支1
            {
                diaElf.setEventNum(1);
                eventList[13]=true;
            }
        }


        if(!eventList[18])//精灵二段对话
        {
            if(map.getS_Map(1,2,10) == 0)
            {
                diaElf.setEventNum(2);
                eventList[18] = 1;
            }
        }

        if(!eventList[19])//五个通关集齐
        {
            if(diaElf.getEventNum() == 2 && getYNtreasures())
            {
                diaElf.setEventNum(3);
                eventList[19] =true;
            }
        }

        if(!eventList[1])//事件1 二层四个骷髅死亡   //事件2 数独进入正确的门，回来后获得奖励 eventList[2]
        {
            if(map.getS_Map(1,2,3) == 0 && map.getS_Map(1,3,4) == 0 &&
                    map.getS_Map(1,2,5) == 0 && map.getS_Map(1,2,4) == 0)
            {
                map.setS_Map(1,7,5,0);//铁门消失
                eventList[1] = 1;
            }
        }


        if(!eventList[23])
        {
            if(map.getS_Map(1,6,11) == 0)
            {
                map.setS_Map(1,6,12,77);//精灵后面的墙变成上楼的楼梯，直通结局
            }
        }
        break;
    case 2:
        if(!eventList[12])//所有门开完  开门
        {
            eventList[12] = 1;
            for(int i=0;i<=12;i++)
            {
                for(int j=0;j<=12;j++)
                {
                    if(map.getS_Map(2,i,j) == 81)
                        eventList[12] = 0;
                }
            }
        }
        else
        {
            map.setT_Map(2,2,9,13);
            map.setT_Map(2,3,10,13);
        }

        if(!eventList[17])
        {
          if(map.getS_Map(2,1,11) == 0)
          {
              map.setS_Map(2,2,10,95);
              eventList[17] = 1;
          }

        }
        break;
    case 3:
        if(!eventList[11])//冰层的埋伏
        {
            if(one.position.x == 11 && one.position.y == 8)
            {
                map.setS_Map(3,9,7,305);
                map.setS_Map(3,9,8,306);
                map.setS_Map(3,9,9,307);
                map.setS_Map(3,8,8,164);
                one.One_Direction = 0;
                eventList[11] = true;
            }
        }

        if(!eventList[16])
        {
            if(map.getS_Map(3,6,1) == 0 )//公主系内,冰通关出现
            {
                map.setS_Map(3,6,3,96);
                eventList[16] =true;
            }
        }

        if(!eventList[15] && eventList[3])//15 选了鲨鹿，并把雷图清空
        {
            eventList[15]=1;
            for(int i=0;i<13;i++)
            {
                for(int j=0;j<13;j++)
                {
                    if(isMonster(4,i,j))
                    {
                        eventList[10]=1;
                        eventList[15]=0;
                    }
                }
            }
        }

        if(eventList[10])
        {
            map.setS_Map(4,3,3,97);//雷通关出现
            eventList[10] = false;
        }

        if(!eventList[20])//拿到壶公主进入1
        {
            if(one.treasures[4][0] == 1)
            {
                diaPri.setEventNum(1);
                eventList[20] = true;
            }
        }
        if(!eventList[21])//拿到网公主进入2
        {
            if(one.treasures[3][0] == 1 && eventList[20])
            {
                diaPri.setEventNum(2);
                eventList[21] = true;
            }
        }
        if(!eventList[22])//拿到四个元素公主进入3
        {
            if(one.treasures[0][1] == 1 && eventList[21]
                    &&one.treasures[2][1] == 1 && one.treasures[3][1] == 1 && one.treasures[4][1] == 1)
            {
                diaPri.setEventNum(3);

                eventList[22] = true;

            }
        }
        break;
    case 4:
        if(!eventList[3] && !eventList[4])//事件3杀戮和事件4宽恕 雷层二选一
        {
            if(one.position.x == 6 && one.position.y == 4)
            {
                eventList[3] = 1;
                map.setT_Map(4,6,7,26);
                map.setT_Map(4,11,8,26);//封右边两堵墙
                map.setS_Map(4,6,7,0);
                one.whatsYourEnd = 1;
                qDebug()<<"whatsYourEnd = 1";

                map.setS_Map(4,6,5,0);//开门
            }
            else if(one.position.x == 6 && one.position.y == 8)
            {
                 eventList[4] = 1;
                 map.setT_Map(4,6,5,26);
                 map.setT_Map(4,11,4,26);//封左边两堵墙
                 map.setS_Map(4,6,5,0);
                 one.whatsYourEnd = 2;
                 map.setS_Map(3,6,2,97);//雷通关出现在公主旁边
                 qDebug()<<"whatsYourEnd = 2";
                 map.setS_Map(4,6,7,0);//开门
            }
        }

        if(!eventList[9])
        {
            eventList[9] = true;
            for(int i=0;i<13;i++)
            {
                for(int j=0;j<13;j++)
                {
                    if(isMonster(4,i,j))
                    {
                        eventList[9] =false;
                    }
                }
            }
            if(eventList[9])
            {
                map.setS_Map(4,2,2,73);
                map.setS_Map(4,2,3,73);
                map.setS_Map(4,2,4,73);
                map.setS_Map(4,3,2,69);
                map.setS_Map(4,3,3,69);
                map.setS_Map(4,3,4,69);
                map.setS_Map(4,4,2,63);
                map.setS_Map(4,4,3,63);
                map.setS_Map(4,4,4,63);

                map.setS_Map(4,8,3,70);
                map.setS_Map(4,8,4,63);
                map.setS_Map(4,9,3,63);
                map.setS_Map(4,9,4,93);
            }
        }
        break;

    case 9:
        if(!eventList[7])
        {
            if(map.getS_Map(9,6,6) == 0)
            {
                QMessageBox::about(this, "血洗魔塔","当你初踏入塔时，一种不知名的欲望就在你的心里生根发芽，战斗的鲜血将其引燃，不知觉你已杀红了眼，剑挥舞向每一个看得见的生物，哪怕是魔王"
                                                 "也未能幸免。出塔后不久，魔塔就在身后轰然崩塌，清澈的水面倒映着残骸也倒映着你，你看看水中的自己，你确定你还是你吗？" );
                this->close();
            }
        }

        break;
    }


}

void Tower::existIsTruth()
{
   for(int i =0;i<=12;i++)
   {
       for(int j=0;j<=12;j++)
       {
           Position p(one.position.layler,i,j);
           switch(isWhatKindMonster(p))
           {
           case MAGICER :
               magicAttack(p);//路过就是100血
               break;
           }
       }
   }
}

void Tower::weAreMatrix(Position p)
{
    p.x-=1;
    if(isWhatKindMonster(p) == MATRIXKNIGHT)
    {
      map.monsterMatrixKnight[map.getS_Map(p) - MATRIXKNIGHT]->iAmMatrix();
    }
    p.x+=2;
    if(isWhatKindMonster(p) == MATRIXKNIGHT)
    {
      map.monsterMatrixKnight[map.getS_Map(p) - MATRIXKNIGHT]->iAmMatrix();
    }
    p.x-=1;p.y-=1;
    if(isWhatKindMonster(p) == MATRIXKNIGHT)
    {
      map.monsterMatrixKnight[map.getS_Map(p) - MATRIXKNIGHT]->iAmMatrix();
    }
    p.y+=2;
    if(isWhatKindMonster(p) == MATRIXKNIGHT)
    {
      map.monsterMatrixKnight[map.getS_Map(p) - MATRIXKNIGHT]->iAmMatrix();
    }
}

void Tower::magicAttack(Position p)
{
    int eType = map.monsterMagicer[map.getS_Map(p) - MAGICER]->getAttack_Element();
    p.x-=1;
    if(p == one.position)
    {
      one.HP-=100*(1-one.Resistance[eType]);
    }
    p.x+=2;
    if(p == one.position)
    {
      one.HP-=100*(1-one.Resistance[eType]);
    }
    p.x-=1;p.y-=1;
    if(p == one.position)
    {
      one.HP-=100*(1-one.Resistance[eType]);
    }
    p.y+=2;
    if(p == one.position)
    {
      one.HP-=100*(1-one.Resistance[eType]);
    }
}

//上下楼
void Tower::floorChange(int num)
{
    one.position.layler += num;
    if(num >= 0)
    {
        map.find1(one.position.layler,one.position.x,one.position.y);//x,y赋值到 上楼默认位置
    }
    else
    {
        map.find2(one.position.layler,one.position.x,one.position.y);//x,y赋值到 下楼默认位置
    }
}

void Tower::mine()
{
    //标记地图初始化
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
           mineFlagMap[i][j] = 0;
        }
    }
    Mine mine;
    mines = 10;//地雷数
    gameEnd = false; 
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            map.setT_Map(6,i,j,mine.getMineNumberMap(i-1,j-1)+230);//[230,238]为扫雷的数字值
        }
    }
   map.setT_Map(6,11,3,281);
   map.setT_Map(6,11,4,221);
   map.setT_Map(6,11,5,274);
   map.setT_Map(6,11,6,275);
   map.setT_Map(6,11,7,264);
   map.setT_Map(6,11,8,273);//v=open

   map.setT_Map(6,4,11,261);
   map.setT_Map(6,5,11,221);
   map.setT_Map(6,6,11,259);
}

void Tower::openBlock(int x,int y)
//8 6
{//0为未曾翻开过  1为翻开了  2为插上了棋
    if(mineFlagMap[x-1][y-1] == 0)
    {
        mineFlagMap[x-1][y-1]=1;
        if(map.getT_Map(6,x,y) == 230)//翻到空格子
        {
            int x1,x2,y1,y2;
            x1 = (x-1 <= 1)? 1 : x-1;
            x2 = (x+1 >= 9)? 9 : x+1;
            y1 = (y-1 <= 1)? 1 : y-1;
            y2 = (y+1 >= 9)? 9 : y+1;

            for(int i=x1;i<=x2;i++)
            {
                for(int j=y1;j<=y2;j++)
                {
                    openBlock(i,j);
                }
            }
        }
        //翻到地雷
        else if(map.getT_Map(6,x,y) == 239)
        {
            one.position.x = 11;
            one.position.y = 3;
            map.setT_Map(6,8,11,12);
            map.setS_Map(6,8,11,48);
        }

    }
}

void Tower::mineFlag()
{

    if(mineFlagMap[one.position.x-1][one.position.y-1] == 0 && mines>=1)
    {
        mineFlagMap[one.position.x-1][one.position.y-1] = 2;
        mines--;
    }
    else if(mineFlagMap[one.position.x-1][one.position.y-1] == 2)
    {
        mineFlagMap[one.position.x-1][one.position.y-1] = 0;
        mines++;
    }

    if(mines==0)
    {
        bool YN=true;
        for(int i=1;i<=9;i++)
        {
            for(int j=1;j<=9;j++)
            {
                if(mineFlagMap[i-1][j-1] == 2 && map.getT_Map(6,i,j) != 239)
                {
                    YN =false;
                }
            }
        }
        if(YN)
        {
            map.setS_Map(6,1,11,50);
            map.setT_Map(6,8,11,11);
            map.setS_Map(6,8,11,0);
        }
    }
}

void Tower::sudu()
{
    Suduku sudu;
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            map.setS_Map(5,i,j,sudu.getSuduMapPlay(i,j)+200);
        }
    }
    ans=sudu.getAns();

    map.setT_Map(5,11,3,220);//红感叹号
    map.setT_Map(5,11,4,221);//=
    map.setT_Map(5,11,5,222);//上楼梯
    map.setT_Map(5,3,11,224);//1
    map.setT_Map(5,4,11,223);//到
    map.setT_Map(5,5,11,225);//9
    //挡路的墙消失，九个楼梯出现
    map.setT_Map(5,9,11,11);
    map.setS_Map(5,9,11,0);
    for(int i=1;i<=9;i++)
    {
        map.setT_Map(5,i,10,222);
    }
    qDebug()<<sudu .getAns();

}

void Tower::unReal(int i)
{
    if(ans == (i+1))
    {
        floorChange(1);
        if(!eventList[2])
        {
            //奖励出现
            map.setS_Map(5,2,11,70);
            map.setS_Map(5,3,11,70);
            map.setS_Map(5,4,11,70);
            map.setS_Map(5,5,11,70);
            map.setS_Map(5,6,11,63);
            map.setS_Map(5,7,11,64);
            map.setS_Map(5,8,11,65);
            //假楼梯消失
            for(int j=1;j<=9;j++)
            {
                if(j!= i+1)
                {
                     map.setS_Map(5,j,10,0);
                     map.setT_Map(5,j,10,12);
                }
            }
            //祭坛封死
            map.setT_Map(5,11,2,12);

            eventList[2] = true;
        }

    }
    else//假楼梯下楼，楼梯封住
    {
        floorChange(-1);
        map.setT_Map(5,9,11,12);
        map.setS_Map(5,9,11,48);
    }
}
//Npc互动事件
void Tower::recuoerate(int num)
{
    if(one.HP!=one.Max_HP)
    {
        one.point-=100;
        one.HP = one.Max_HP;
    }
}

void Tower::beDedicated(bool YN)
{
    if(YN)
    {
        for(int i=0;i<5;i++)
        {
            one.treasures[i][1] = 0;
        }
        one.whatsYourEnd = 5;

        diaElf.setEventNum(4);
        aloneElf();
    }
    else
    {
        one.isElf = true;
    }
}
void Tower::aloneElf()
{
    map.setS_Map(1,6,10,183);//精灵左边一步主角变的精灵出现
    map.setS_Map(1,6,11,0);//精灵消失
}

bool Tower::getYNtreasures()
{
    bool YN=true;
    for (int i=0;i<5;i++)
    {
        if(one.treasures[i][1] ==0)
        {
            YN = false;
        }
    }
    return YN;

}

void Tower::buy(int num)
{

    switch (num)
    {
    case 1://100一把红钥匙
        if(one.point>=100)
        {
            one.point-=100;
            one.key[2]++;
            diaMer.setEventNum(1);
        }
        break;
    case 2://200一个红血瓶
        if(one.point>=200)
        {
            one.point-=200;
            one.Max_HP+=200;
            diaMer.setEventNum(2);
        }
        break;
    case 3://300一个红宝石
        if(one.point>=300)
        {
            one.point-=300;
            one.Element_Attack[3]+=15;
            diaMer.setEventNum(3);
        }
        break;
    case 4://400开门
        if(one.point>=400 && eventList[14] == false)
        {
            one.point-=400;
            eventList[14] = 1;
            diaMer.setEventNum(4);
        }
        break;
    case 5:
        if( one.key[3]==0)
        {
            diaMer.setEventNum(6);
        }
        else if(one.point>=10000 )
        {
            one.point-=10000;
            one.whatsYourEnd = 3;//购物结局
            one.key[3]++;
            diaMer.setEventNum(5);
        }
        break;
    }
}

void Tower::withPri(bool YN)
{
    if(YN)
    {
        for(int i=0;i<5;i++)
        {
            one.treasures[i][1] = 0;
        }
        one.key[3]=1;
        map.setS_Map(3,6,1,87);
        one.withPrincess =true;
    }

}
