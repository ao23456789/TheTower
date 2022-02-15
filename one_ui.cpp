#include "one_ui.h"
#include "ui_one_ui.h"


One_ui::One_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::One_ui)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);//设置右上角没有？
    setWindowTitle(QObject::tr("角色属性"));
}


One_ui::~One_ui()
{
    delete ui;
}

void One_ui::setTreasures(int num[5][2])
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<2;j++)
        {
             treasures[i][j]=num[i][j];
        }
    }

}

void One_ui::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_C://在属性界面再按C则关闭属性界面
        this->close();
        break;
    case Qt::Key_W :
        treasuresUi = treasuresUi-1 > 0?treasuresUi-1:0;
        update();
        break;
    case Qt::Key_S :
        treasuresUi = treasuresUi+1 > 4? 4:treasuresUi+1;
        update();
        break;
    case Qt::Key_F :
        if(treasures[treasuresUi][0])
        {
             emit oneSendTreasure(treasuresUi);
            this->close();//F one所装备的物品变成所选择的
        }
        break;
    }
}


void One_ui::paintEvent(QPaintEvent *)
{
      QPixmap treasure;
      treasure.load("://res/treasure.bmp");
      QPainter painter(this);//要绘制的对象

      for(int i=0;i<5;i++)
      {
          if(treasures[i][1] == 0)
          {
              painter.drawPixmap( oneui_Xoffset + 33 , oneui_Yoffset + i*33 , treasure, 5 * 33, 33, HEIGHT,WIDTH);//黑
          }
          else
          {
              painter.drawPixmap( oneui_Xoffset + 33 , oneui_Yoffset + i*33, treasure, i * 33, 33, HEIGHT,WIDTH);
          }
      }

      if(treasures[0][0] == 0)
      {
          painter.drawPixmap( oneui_Xoffset  , oneui_Yoffset  , treasure, 7 * 33, 0, HEIGHT,WIDTH);
      }
      else
      {
          painter.drawPixmap( oneui_Xoffset  , oneui_Yoffset  , treasure, 7 * 33, 0, HEIGHT,WIDTH);
      }



      for(int i=0;i<4;i++)//水壶比较特殊，把后两个独立绘制
      {
          for(int j=0;j<2;j++)
          {
              if(treasures[i][j] == 0)
              {
                  painter.drawPixmap( oneui_Xoffset + j *33 , oneui_Yoffset + i*33 , treasure, 7*33, 0, HEIGHT,WIDTH);
              }
              else
              {
                  painter.drawPixmap( oneui_Xoffset + j *33 , oneui_Yoffset + i*33 , treasure, i*33, j*33, HEIGHT,WIDTH);
              }
          }
      }

      if(treasures[4][1] == 0)
      {
          painter.drawPixmap( oneui_Xoffset + 33 , oneui_Yoffset + 4*33 , treasure, 7*33, 0, HEIGHT,WIDTH);
      }
      else
      {
          painter.drawPixmap( oneui_Xoffset + 33 , oneui_Yoffset + 4*33 , treasure, 4*33, 33, HEIGHT,WIDTH);
      }

      switch (treasures[4][0])//水壶
      {
      case 0:
          painter.drawPixmap( oneui_Xoffset  , oneui_Yoffset + 4*33 , treasure, 7*33, 0, HEIGHT,WIDTH);
          break;
      case 1://拥有
          painter.drawPixmap( oneui_Xoffset  , oneui_Yoffset + 4*33 , treasure, 6*33, 0, HEIGHT,WIDTH);
          break;
      case 2://水
          painter.drawPixmap( oneui_Xoffset  , oneui_Yoffset + 4*33 , treasure, 5*33, 0, HEIGHT,WIDTH);
          break;
      case 3://火
          painter.drawPixmap( oneui_Xoffset  , oneui_Yoffset + 4*33 , treasure, 4*33, 0, HEIGHT,WIDTH);
          break;
      case 4://毒
          painter.drawPixmap( oneui_Xoffset  , oneui_Yoffset + 4*33 , treasure, 5*33, 33, HEIGHT,WIDTH);
          break;
      }
      painter.drawPixmap( oneui_Xoffset, oneui_Yoffset + treasuresUi * 33 , treasure, 7*33, 33, HEIGHT,WIDTH);

}










void One_ui::buttonIsAble()
{
    if(lvPoint == 0)
    {
        ui->buttonAttcak->setEnabled(0);
        ui->buttonDefense->setEnabled(0);
        ui->buttonMaxHp->setEnabled(0);
        ui->buttonAgile->setEnabled(0);
        ui->buttonAttack0->setEnabled(0);
        ui->buttonAttack1->setEnabled(0);
        ui->buttonAttack2->setEnabled(0);
        ui->buttonAttack3->setEnabled(0);
        ui->buttonResistance0->setEnabled(0);
        ui->buttonResistance1->setEnabled(0);
        ui->buttonResistance2->setEnabled(0);
        ui->buttonResistance3->setEnabled(0);
        ui->buttonAttackTypeResistance0->setEnabled(0);
        ui->buttonAttackTypeResistance1->setEnabled(0);
        ui->buttonAttackTypeResistance2->setEnabled(0);
    }
    else
    {
        ui->buttonAttcak->setEnabled(1);
        ui->buttonDefense->setEnabled(1);
        ui->buttonMaxHp->setEnabled(1);
        ui->buttonAgile->setEnabled(1);
        ui->buttonAttack0->setEnabled(1);
        ui->buttonAttack1->setEnabled(1);
        ui->buttonAttack2->setEnabled(1);
        ui->buttonAttack3->setEnabled(1);
        ui->buttonResistance0->setEnabled(1);
        ui->buttonResistance1->setEnabled(1);
        ui->buttonResistance2->setEnabled(1);
        ui->buttonResistance3->setEnabled(1);
        ui->buttonAttackTypeResistance0->setEnabled(1);
        ui->buttonAttackTypeResistance1->setEnabled(1);
        ui->buttonAttackTypeResistance2->setEnabled(1);
    }

//点数大于lv*50 lv亮
    if(point>=50*lv)
    {
        ui->buttonLv->setEnabled(1);
    }
    else
    {
         ui->buttonLv->setEnabled(0);
    }

    //如果有抗性值超过1
    attackTypeResistance[1] = attackTypeResistance[1]>=1?1:attackTypeResistance[1];
    str0 = QString::number(attackTypeResistance[1]);
    ui->label_Resistance_Slash->setText(str0);//斩击抗性标签

    attackTypeResistance[2] = attackTypeResistance[2]>=1?1:attackTypeResistance[2];
    str0 = QString::number(attackTypeResistance[2]);
    ui->label_Resistance_Bludgeon->setText(str0);//钝击抗性标签

    attackTypeResistance[3] = attackTypeResistance[3]>=1?1:attackTypeResistance[3];
    str0 = QString::number(attackTypeResistance[3]);
    ui->label_Resistance_Puncture->setText(str0);//刺击抗性标签

    resistance[1] = resistance[1]>=1?1:resistance[1];
    str0 = QString::number(resistance[1]);
    ui->label_Resistance_1->setText(str0);//冰抗性标签

    resistance[2] = resistance[2]>=1?1:resistance[2];
    str0 = QString::number(resistance[2]);
    ui->label_Resistance_2->setText(str0);//雷抗性标签

    resistance[3] = resistance[3]>=1?1:resistance[3];
    str0 = QString::number(resistance[3]);
    ui->label_Resistance_3->setText(str0);//火抗性标签

    resistance[4] = resistance[4]>=1?1:resistance[4];
    str0 = QString::number(resistance[4]);
    ui->label_Resistance_4->setText(str0);//魔抗性



}




void One_ui::oneuiRecvData(One one)
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<2;j++)
        {
             treasures[i][j] =one.treasures[i][j];
        }

    }
    treasuresUi =0;


    lv = one.LV;
    lvPoint = one.lvPoint;
    point = one.point;
    agile = one.Agile;
    hp = one.Max_HP;
    attack = one.Attack;
    defense = one.Defense;
    for(int i =1;i<=3;i++)
    {
        attackTypeResistance[i] = one.Attack_Type_Resistance[i];
    }
    for(int i =0;i<5;i++)
    {
        elementAttack[i] = one.Element_Attack[i];
    }
    for(int i =0;i<5;i++)
    {
        resistance[i] = one.Resistance[i];
    }
    buttonIsAble();


    str0 = QString::number(hp);
    ui->label_MaxHp->setText(str0);//hp标签

    str0 = QString::number(attack);
    ui->label_Attack->setText(str0);//攻击力标签

    str0 = QString::number(defense);
    ui->label_Defense->setText(str0);//防御力标签

    str0 = QString::number(lv);
    ui->label_lv->setText(str0);//lv标签

    str0 = QString::number(agile);
    ui->label_Agile->setText(str0);//敏捷标签

    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);//等级点数标签

    str0 = QString::number(point);
    ui->label_Point->setText(str0);//点数标签

    str0 = QString::number(attackTypeResistance[1]);
    ui->label_Resistance_Slash->setText(str0);//斩击抗性标签

    str0 = QString::number(attackTypeResistance[2]);
    ui->label_Resistance_Bludgeon->setText(str0);//钝击抗性标签

    str0 = QString::number(attackTypeResistance[3]);
    ui->label_Resistance_Puncture->setText(str0);//刺击抗性标签

    str0 = QString::number(resistance[1]);
    ui->label_Resistance_1->setText(str0);//冰抗性标签

    str0 = QString::number(resistance[2]);
    ui->label_Resistance_2->setText(str0);//雷抗性标签

    str0 = QString::number(resistance[3]);
    ui->label_Resistance_3->setText(str0);//火抗性标签

    str0 = QString::number(resistance[4]);
    ui->label_Resistance_4->setText(str0);//魔抗性标签

    str0 = QString::number(elementAttack[1]);
    ui->label_Attack_1->setText(str0);//冰攻击力标签

    str0 = QString::number(elementAttack[2]);
    ui->label_Attack_2->setText(str0);//雷攻击力标签

    str0 = QString::number(elementAttack[3]);
    ui->label_Attack_3->setText(str0);//火攻击力标签

    str0 = QString::number(elementAttack[4]);
    ui->label_Attack_4->setText(str0);//魔攻击力标签


}




//升级
void One_ui::on_buttonLv_clicked()
{



        hp+=50;
        str0 = QString::number(hp);
        ui->label_MaxHp->setText(str0);//hp标签

        attack+=5;
        str0 = QString::number(attack);
        ui->label_Attack->setText(str0);//攻击力标签

        defense+=8;
        str0 = QString::number(defense);
        ui->label_Defense->setText(str0);//防御力标签



        point-=25*lv;
        str0 = QString::number(point);
        ui->label_Point->setText(str0);//点数标签

        lv+=1;
        str0 = QString::number(lv);
        ui->label_lv->setText(str0);//lv标签

        lvPoint+=1;
        str0 = QString::number(lvPoint);
        ui->label_lvPoint->setText(str0);//等级点数标签

        attackTypeResistance[1]+=0.012;
        str0 = QString::number(attackTypeResistance[1]);
        ui->label_Resistance_Slash->setText(str0);//斩击抗性标签

        attackTypeResistance[2]+=0.012;
        str0 = QString::number(attackTypeResistance[2]);
        ui->label_Resistance_Bludgeon->setText(str0);//钝击抗性标签

        attackTypeResistance[3]+=0.012;
        str0 = QString::number(attackTypeResistance[3]);
        ui->label_Resistance_Puncture->setText(str0);//刺击抗性标签

        resistance[1]+=0.01;
        str0 = QString::number(resistance[1]);
        ui->label_Resistance_1->setText(str0);//冰抗性标签

        resistance[2]+=0.01;
        str0 = QString::number(resistance[2]);
        ui->label_Resistance_2->setText(str0);//雷抗性标签

        resistance[3]+=0.01;
        str0 = QString::number(resistance[3]);
        ui->label_Resistance_3->setText(str0);//火抗性标签

        resistance[4]+=0.01;
        str0 = QString::number(resistance[4]);
        ui->label_Resistance_4->setText(str0);//魔抗性标签
        elementAttack[0] = attack;

        elementAttack[1] +=3;
        str0 = QString::number(elementAttack[1]);
        ui->label_Attack_1->setText(str0);//冰攻击力标签

        elementAttack[2] +=3;
        str0 = QString::number(elementAttack[2]);
        ui->label_Attack_2->setText(str0);//雷攻击力标签

        elementAttack[3] +=3;
        str0 = QString::number(elementAttack[3]);
        ui->label_Attack_3->setText(str0);//火攻击力标签

        elementAttack[4] +=3;
        str0 = QString::number(elementAttack[4]);
        ui->label_Attack_4->setText(str0);//魔攻击力标签

        buttonIsAble();
}

void One_ui::on_buttonAttcak_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    attack+=5;
    str0 = QString::number(attack);
    ui->label_Attack->setText(str0);//攻击力标签
    buttonIsAble();
}

void One_ui::on_buttonDefense_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    defense+=10;
    str0 = QString::number(defense);
    ui->label_Defense->setText(str0);//防御力标签
    buttonIsAble();
}

void One_ui::on_buttonMaxHp_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    hp+=100;
    str0 = QString::number(hp);
    ui->label_MaxHp->setText(str0);//hp标签
    buttonIsAble();
}

void One_ui::on_buttonAgile_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    agile+=1;
    str0 = QString::number(agile);
    ui->label_Agile->setText(str0);
    buttonIsAble();
}


void One_ui::on_buttonAttackTypeResistance0_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    attackTypeResistance[1]+=0.02;
    str0 = QString::number(attackTypeResistance[1]);
    ui->label_Resistance_Slash->setText(str0);//斩击抗性标签
    buttonIsAble();
}

void One_ui::on_buttonAttackTypeResistance1_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    attackTypeResistance[2]+=0.02;
    str0 = QString::number(attackTypeResistance[2]);
    ui->label_Resistance_Bludgeon->setText(str0);//钝击抗性标签
    buttonIsAble();
}


void One_ui::on_buttonAttackTypeResistance2_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    attackTypeResistance[3]+=0.02;
    str0 = QString::number(attackTypeResistance[3]);
    ui->label_Resistance_Puncture->setText(str0);//刺击抗性标签
    buttonIsAble();
}

void One_ui::on_buttonAttack0_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    elementAttack[1] +=5;
    str0 = QString::number(elementAttack[1]);
    ui->label_Attack_1->setText(str0);//冰攻击力标签
    buttonIsAble();
}

void One_ui::on_buttonAttack1_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    elementAttack[2] +=5;
    str0 = QString::number(elementAttack[2]);
    ui->label_Attack_2->setText(str0);
    buttonIsAble();
}

void One_ui::on_buttonAttack2_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    elementAttack[3] +=5;
    str0 = QString::number(elementAttack[3]);
    ui->label_Attack_3->setText(str0);
    buttonIsAble();
}

void One_ui::on_buttonAttack3_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    elementAttack[4] +=5;
    str0 = QString::number(elementAttack[4]);
    ui->label_Attack_4->setText(str0);
    buttonIsAble();
}

void One_ui::on_buttonResistance0_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    resistance[1]+=0.02;
    str0 = QString::number(resistance[1]);
    ui->label_Resistance_1->setText(str0);//冰抗性标签
    buttonIsAble();
}

void One_ui::on_buttonResistance1_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    resistance[2]+=0.02;
    str0 = QString::number(resistance[2]);
    ui->label_Resistance_2->setText(str0);//雷抗性标签
    buttonIsAble();
}

void One_ui::on_buttonResistance2_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    resistance[3]+=0.02;
    str0 = QString::number(resistance[3]);
    ui->label_Resistance_3->setText(str0);//火抗性标签
    buttonIsAble();
}

void One_ui::on_buttonResistance3_clicked()
{
    lvPoint-=1;
    str0 = QString::number(lvPoint);
    ui->label_lvPoint->setText(str0);

    resistance[4]+=0.02;
    str0 = QString::number(resistance[4]);
    ui->label_Resistance_4->setText(str0);//魔抗性标签
    buttonIsAble();
}
//确定按钮
void One_ui::on_buttonSure_clicked()
{
    oneTemp.HP = hp;
    oneTemp.Attack = attack;
    oneTemp.Defense = defense;
    oneTemp.LV = lv;
    oneTemp.lvPoint = lvPoint;
    oneTemp.point = point;
    oneTemp.Agile = agile;
    for(int i=0;i<5;i++)
    {
        oneTemp.Resistance[i] = resistance[i];
        oneTemp.Element_Attack[i] = elementAttack[i];
    }
    for(int i =1;i<=3;i++)
    {
        oneTemp.Attack_Type_Resistance[i] = attackTypeResistance[i];
    }
    emit oneSendData(oneTemp);
    this->close();

}
