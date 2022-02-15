#include "note.h"
#include "ui_note.h"

Note::Note(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
}

Note::~Note()
{
    delete ui;
}



void Note::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F:
        this->close();
        break;
    }
}


void Note::noteRecvData(Monster *monster)
{
    //攻击
    str0 = QString::number(monster->getAttack());
    ui->label_Attack->setText(str0);
    //防御
    str0 = QString::number(monster->getDefense());
    ui->label_Defense->setText(str0);
    //最大血量
    str0 = QString::number(monster->getMax_HP());
    ui->label_MaxHp->setText(str0);
    //敏捷
    str0 = QString::number(monster->getAgile());
    ui->label_Agile->setText(str0);
    //斩击抗性
    str0 = QString::number(monster->getAttack_Type_Resistance(1));
    ui->label_Resistance_Slash->setText(str0);
    //钝击抗性
    str0 = QString::number(monster->getAttack_Type_Resistance(2));
    ui->label_Resistance_Bludgeon->setText(str0);
    //刺击抗性
    str0 = QString::number(monster->getAttack_Type_Resistance(3));
    ui->label_Resistance_Puncture->setText(str0);
    //属性攻击力
    str0 = QString::number(monster->getElement_Attack(monster->getAttack_Element()));
    ui->label_Attack_1->setText(str0);
    //冰抗
    str0 = QString::number(monster->getResistance(1));
    ui->label_Resistance_1->setText(str0);
    //雷抗
    str0 = QString::number(monster->getResistance(2));
    ui->label_Resistance_2->setText(str0);
    //火抗
    str0 = QString::number(monster->getResistance(3));
    ui->label_Resistance_3->setText(str0);
    //魔抗
    str0 = QString::number(monster->getResistance(4));
    ui->label_Resistance_4->setText(str0);

    switch (monster->getAttack_Element())
    {
    case 0:
        str0 = "物理";
        ui->labelEType->setText(str0);
        break;
    case 1:
        str0 = "冰";
        ui->labelEType->setText(str0);
        break;
    case 2:
        str0 = "雷";
        ui->labelEType->setText(str0);
        break;
    case 3:
        str0 = "火";
        ui->labelEType->setText(str0);
        break;
    case 4:
        str0 = "魔";
        ui->labelEType->setText(str0);
        break;
    }

    int adjective = monster->getAttack_Element();
    int numId = monster->getMonsterId();

    if(numId >= SLIME  && numId < SLIME+10)
    {
        str0.clear();
        whatKindMonster(adjective);
        str0 += "史莱姆";
        ui->labelMonsterId->setText(str0);
        str0 = "  一种纯正的属性生物,摸起来比看起来恶心得多";
        ui->labelText->setText(str0);
    }
    else if(numId >= BAT  && numId < BAT+10)
    {
        str0.clear();
        whatKindMonster(adjective);
        str0 += "蝙蝠";
        ui->labelMonsterId->setText(str0);
        str0 = "  一种常见的动物，在这个鬼地方变成什么鬼样我都不会惊讶";
        ui->labelText->setText(str0);
    }

    else if(numId >= SKELETON  && numId < SKELETON+10)
    {
        switch (numId-SKELETON)
        {
        case 0:
        case 2:
        case 3:
        case 6:
        case 7:
            ui->labelMonsterId->setText("骷髅");
            str0 = "  从不起眼的地方爬出来的一个能动的骨头";
            ui->labelText->setText(str0);
            break;
        default:
            ui->labelMonsterId->setText("骷髅队长");
            str0 = "  能动的骨头拿起了盾牌和武器，幸亏不是锤子和镰刀";
            ui->labelText->setText(str0);
            break;
        }
    }

    else if(numId >= ORCISH  && numId < ORCISH+10)
    {
        switch (numId-ORCISH)
        {
        case 0:
        case 2:
        case 4:
        case 5:
            ui->labelMonsterId->setText("兽人");
            str0 = "  兽人呃啊---会说话呃啊----没脑子呃啊--";
            ui->labelText->setText(str0);
            break;
        default:
            ui->labelMonsterId->setText("武装兽人");
            str0 = "  他们会用剑漂亮地接住你的剑，然后用盾牌砸向你的脸";
            ui->labelText->setText(str0);
            break;
        }
    }

    else if(numId >= MAGICER  && numId < MAGICER+10)
    {
        str0.clear();
        whatKindMonster(adjective);
        str0 += "术士";
        ui->labelMonsterId->setText(str0);
        str0 = "  在成为法师之前，他曾是一名牧师";
        ui->labelText->setText(str0);
    }

    else if(numId >= ELEMENTSTONE  && numId < ELEMENTSTONE+10)
    {
        str0.clear();
        whatKindMonster(adjective);
        str0 += "石头人";
        ui->labelMonsterId->setText(str0);
        str0 = "  和看起来一样硬";
        ui->labelText->setText(str0);
    }

    else if(numId >= CRUSADEKNIGHT  && numId < CRUSADEKNIGHT+10)
    {
        str0.clear();
        whatKindMonster(adjective);
        str0 += "十字骑士";
        ui->labelMonsterId->setText(str0);
        str0 = "  皈依基督之前，他们被叫新月骑士";
        ui->labelText->setText(str0);
    }

    else if(numId >= MATRIXKNIGHT  && numId < MATRIXKNIGHT+10)
    {
        str0.clear();
        whatKindMonster(adjective);
        str0 += "矩阵骑士";
        ui->labelMonsterId->setText(str0);
        str0 = "  像矩阵一样可靠，除非变换";
        ui->labelText->setText(str0);

    }

    else if(numId >= SWORDMAN  && numId < SWORDMAN+10)
    {
        switch (numId - SWORDMAN)
        {
        case 0:
        case 1:
        case 9:
            str0 = "黄衣武士";
            ui->labelMonsterId->setText(str0);
            str0 = "  黄衣武士就是喜欢穿黄色衣服的武士（确信）";
            ui->labelText->setText(str0);
            break;
        case 2:
        case 3:
        case 4:
            str0 = "红衣武士";
            ui->labelMonsterId->setText(str0);
            str0 = "  高价收购红衣武士的衣服";
            ui->labelText->setText(str0);
            break;
        default:
            str0 = "蓝衣武士";
            ui->labelMonsterId->setText(str0);
            str0 = "  这衣服狗都不穿----武士";
            ui->labelText->setText(str0);
            break;
        }
    }

    switch (numId)
    {
    case 180:
        str0 = "芒力";
        ui->labelMonsterId->setText(str0);
        str0 = "  褪下资本面纱，我们竟然是朋友";
        ui->labelText->setText(str0);
        break;
    case 181:
        str0 = "艾尔芙";
        ui->labelMonsterId->setText(str0);
        str0 = "  狗字的二十四种写法";
        ui->labelText->setText(str0);
        break;
    case 182:
        str0 = "蒲莱恩丝";
        ui->labelMonsterId->setText(str0);
        str0 = "  公主的塔中生活过得不是很理想";
        ui->labelText->setText(str0);
        break;
    case 190:
        str0 = "无辜的巨龙";
        ui->labelMonsterId->setText(str0);
        str0 = "  至少比你无辜一百倍";
        ui->labelText->setText(str0);
        break;
    case 191:
        str0 = "安详的海怪";
        ui->labelMonsterId->setText(str0);
        str0 = "  像等待小红帽的狼外婆一样安详";
        ui->labelText->setText(str0);
        break;
    case 192:
        str0 = "坚守阵地的黑骑士";
        ui->labelMonsterId->setText(str0);
        str0 = "  一个脱离低级趣味，忠心耿耿，本领高强的-------保安";
        ui->labelText->setText(str0);
        break;
    case 193:
        str0 = "一心求死的吸血鬼";
        ui->labelMonsterId->setText(str0);
        str0 = "  在牢笼里，不死的祝福比诅咒更恶毒";
        ui->labelText->setText(str0);
        break;
    case 194:
        str0 = "魔王";
        ui->labelMonsterId->setText(str0);
        str0 = "  在进塔之前，我的名字是张三";
        ui->labelText->setText(str0);
        break;
    }
}

void Note::whatKindMonster(int kind)
{
    switch (kind)
    {
    case 0:
        str0+="钢铁";
        break;
    case 1:
        str0+="寒冰";
        break;
    case 2:
        str0+="雷霆";
        break;
    case 3:
        str0+="烈焰";
        break;
    case 4:
        str0+="魔法";
        break;
    }

}

