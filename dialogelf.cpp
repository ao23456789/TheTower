#include "dialogelf.h"
#include "ui_dialogelf.h"


DialogElf::DialogElf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogElf)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);//设置右上角没有？
    setWindowTitle(QObject::tr("精灵"));
    count =0;
    eventNum =0;

    ui->pushButton_2->setVisible(false);
    ui->pushButton_2->setEnabled(false);
    ui->talkWithElf->setReadOnly(true);
    setText();
}
DialogElf::~DialogElf()
{
    delete ui;
}

void DialogElf::setTxet(int i, int j, QString str)
{
    talkText[i][j] = str;
}

void DialogElf::setText()
{
    int i=0;
    talkText[0][i] = "【勇者】:  你好";i++;
    talkText[0][i] = "【精灵】:  你好，勇者，我是守护着这个塔的精灵，你可以随时用100p来让我帮你恢复血量";i++;
    talkText[0][i] = "【精灵】:  我来告诉你一些具体的操作吧";i++;
    talkText[0][i] = "【精灵】:  Z切换你的攻击方式，分别为斩击钝击和刺击";i++;
    talkText[0][i] = "【精灵】:  X切换你当前使用的元素类型，如果元素攻击力不是很高的话建议还是用无属性";i++;
    talkText[0][i] = "【精灵】:  C可以打开你的角色面板，你可以用点数升级或者留着其他用途";i++;
    talkText[0][i] = "【精灵】:  在角色面板里WS可以切换你获得的宝物，按F选中，按F使用，当然你现在应该什么都没有";i++;
    talkText[0][i] = "【勇者】:  呃，好吧";i++;

    i=0;
    talkText[1][i] = "【精灵】:  有和上面那个家伙说过话了吗，他叫芒力 ";i++;
    talkText[1][i] = "【精灵】:  芒力是我见过的最恶心的人 ";i++;
    talkText[1][i] = "【精灵】:  他收费很贵，而且东西相当不值当";i++;
    talkText[1][i] = "【勇者】:  你想说什么";i++;
    talkText[1][i] = "【精灵】:  我可以给你任何他能给你的东西，只要你能帮我办一件事";i++;
    talkText[1][i] = "【勇者】:  你说";i++;
    talkText[1][i] = "【精灵】:  上面右边有一个密道，顺着走可以绕到他背后";i++;
    talkText[1][i] = "【精灵】:  然后就可以动手了，不过建议你升下级再这么干";i++;

    i=0;
    talkText[2][i] = "【精灵】:  很好，你做得很好 ";i++;
    talkText[2][i] = "【精灵】:  我已经帮你把门打开了";i++;
    talkText[2][i] = "【精灵】:  你再继续往上走，会有个公主在那";i++;
    talkText[2][i] = "【精灵】:  如果你想离开这的话，你需要五个元素之力，她藏着其中一个";i++;
    talkText[2][i] = "【精灵】:  她不死没人能离开这";i++;
    talkText[2][i] = "【精灵】:  如果你有能耐，去把五个元素之力带给我，我可以带你直接离开这里";i++;

    i=0;
    talkText[3][i] = "【精灵】:  左边有个按钮看见没有 ";i++;
    talkText[3][i] = "【精灵】:  按下它";i++;

    i=0;
    talkText[4][i] = "【精灵】:  哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈！ ";i++;
    talkText[4][i] = "【精灵】:  哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈";i++;
    talkText[4][i] = "【精灵】:  终于，终于自由了，诅咒转移到你身上了";i++;
    talkText[4][i] = "【精灵】:  我要谢谢你，可怜的傻逼";i++;


}

void DialogElf::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F :
        ui->talkWithElf->appendPlainText(talkText[eventNum][count]);
        qDebug()<<eventNum;
        count++;
        break;
    case Qt::Key_C :
        this->close();
        break;
    }
}

int DialogElf::getEventNum() const
{
    return eventNum;
}

void DialogElf::setEventNum(int value)
{
    eventNum = value;
    count = 0;

    if(value ==3)
    {
        ui->pushButton_2->setVisible(true);
        ui->pushButton_2->setEnabled(true);
    }
    else if(value == 4)
    {
        emit dedication(false);
    }
}


void DialogElf::on_pushButton_clicked()
{
    if(isEnoughPoint)
    {
        emit sendRecuoerate(1);
    }
}

bool DialogElf::getIsEnoughPoint() const
{

    return isEnoughPoint;
}

void DialogElf::setIsEnoughPoint(bool value)
{
    isEnoughPoint = value;
}

void DialogElf::on_pushButton_2_clicked()
{
    emit dedication(true);
}
