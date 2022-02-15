#include "dialogprincess.h"
#include "ui_dialogprincess.h"

DialogPrincess::DialogPrincess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPrincess)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);//设置右上角没有？
    setWindowTitle(QObject::tr("公主"));

    ui->pushButton->setVisible(false);
    ui->pushButton->setEnabled(false);
    count =0;
    eventNum =0;
    ui->talkWithPri->setReadOnly(true);
    setText();
}

DialogPrincess::~DialogPrincess()
{
    delete ui;
}

void DialogPrincess::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F :
        ui->talkWithPri->appendPlainText(talkText[eventNum][count]);
        count++;
        break;
    case Qt::Key_C :
        this->close();
        break;
    }
}

void DialogPrincess::setText()
{
    int i=0;
    talkText[0][i] = "【勇者】:  你好";i++;
    talkText[0][i] = "【公主】:  你也被困在这塔里了吗";i++;
    talkText[0][i] = "【公主】:  被困在塔里的人都在找出去的路，我现在有一些线索了";i++;
    talkText[0][i] = "【公主】:  在我继续回答你之前，你得向我证明自己";i++;
    talkText[0][i] = "【公主】:  在我南边有个水壶，去把它拿到手，然后再来找我";i++;

    i=0;
    talkText[1][i] = "【公主】:  装备这个水壶去水潭边按F接水，使用会增强这层楼里的对应属性的怪物和你自己";i++;
    talkText[1][i] = "【公主】:  同时也能削弱其他属性的的怪物";i++;
    talkText[1][i] = "【公主】:  上面几层有一个白色的网，去拿到之后来找我";i++;

    i=0;
    talkText[2][i] = "【公主】:  装备这个网可以直接抓住蝙蝠和史莱姆";i++;
    talkText[2][i] = "【公主】:  抓蝙蝠可以增加攻防，抓史莱姆可以增加元素攻击力";i++;
    talkText[2][i] = "【公主】:  基础属性越高，增加的值越多";i++;
    talkText[2][i] = "【公主】:  准备得差不多了，接下来的事情你给我听好了";i++;
    talkText[2][i] = "【公主】:  我需要五个元素之力来离开这里 冰元素在我这里";i++;
    talkText[2][i] = "【公主】:  火元素和雷元素都在对应的楼层很好找";i++;
    talkText[2][i] = "【公主】:  魔元素我只能确定在上面的某一层的机关里";i++;
    talkText[2][i] = "【公主】:  最后的钢铁元素被黑骑士守护着，你要小心，黑骑士非常强";i++;
    talkText[2][i] = "【公主】:  塔里的强者都只是生前的一部分，他们没有什么特殊能力，只是单纯的强而已";i++;
    talkText[2][i] = "【公主】:  去集齐剩下四个元素来找我";i++;

    i=0;
    talkText[3][i] = "【公主】:  点左边的按钮合成元素之力";i++;
    talkText[3][i] = "【公主】:  合成之后元素就消失了，拿着这把钥匙吧，我们从魔法阵的左边走";i++;
    talkText[3][i] = "【公主】:  路上应该会遇上那个一直自杀的吸血鬼，他一直在不停地烧死自己，然后大概每隔几天就又会从血迹里爬出来";i++;
    talkText[3][i] = "【公主】:  对他用炎拳吧";i++;
    talkText[3][i] = "【公主】:  然后我们从黑海的下面游出去";i++;

}
int DialogPrincess::getEventNum() const
{
    return eventNum;
}

void DialogPrincess::setEventNum(int value)
{
    eventNum = value;
    count = 0;
    if(value == 3)
    {
        ui->pushButton->setVisible(true);
        ui->pushButton->setEnabled(true);
    }
}

void DialogPrincess::on_pushButton_clicked()
{
     emit sendWithPr(true);
}
