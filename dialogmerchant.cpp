#include "dialogmerchant.h"
#include "ui_dialogmerchant.h"

DialogMerchant::DialogMerchant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMerchant)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);//设置右上角没有？
    setWindowTitle(QObject::tr("商人"));
    ui->talkWithMer->setReadOnly(true);
    setText();
}

DialogMerchant::~DialogMerchant()
{
    delete ui;
}

void DialogMerchant::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F :
        ui->talkWithMer->appendPlainText(talkText[eventNum][count]);
        count++;
        break;
    case Qt::Key_C :
        this->close();
        break;
    }
}

void DialogMerchant::setText()
{
    int i=0;
    talkText[0][i] = "【勇者】:  你好";i++;
    talkText[0][i] = "【商人】:  我这有些好东西，要看看吗";i++;
    talkText[0][i] = "【商人】:  一把钥匙，我只卖你100p，如果你感兴趣的话可以来找我";i++;

    i=0;
    talkText[1][i] = "【商人】:  谢谢光顾";i++;
    talkText[1][i] = "【商人】:  一杯红色药水，我只卖你200p，如果你感兴趣的话可以来找我";i++;

    i=0;
    talkText[2][i] = "【商人】:  谢谢光顾";i++;
    talkText[2][i] = "【商人】:  一颗亮晶晶的红宝石，我只卖你300p";i++;
    talkText[2][i] = "【商人】:  后面如果你肯再出400p的话我可以把左边的铁门给你打开";i++;

    i=0;
    talkText[3][i] = "【商人】:  谢谢光顾";i++;
    talkText[3][i] = "【商人】: 400p换一个开门你绝对不会亏";i++;
    i=0;
    talkText[4][i] = "【商人】: 好吧不开玩笑了，其实我一直在找机会离开这里，而且我已经有些门道了，看你可怜我可以带上你，但你也知道这不可能是免费的";i++;
    talkText[4][i] = "【商人】: 这次的价格是10000p,如果你拿得出手，我不介意带着你一块走，毕竟在路上需要打手来处理杂鱼";i++;
    talkText[4][i] = "【商人】: 而且我警告你不要和那边那个自称精灵的家伙还有楼上那个自称公主的人做过多接触";i++;

    i=0;
    talkText[5][i] = "【商人】: 很好，你拿好这把钥匙，它能打开最后一层的绿门";i++;

    i=0;
    talkText[6][i] = "【商人】: 我记得我警告过不要和那两个人做过多接触，快给我滚，我们的交易就此终止";i++;



}

bool DialogMerchant::getIsEnoughPoint() const
{
    return isEnoughPoint;
}

void DialogMerchant::setIsEnoughPoint(bool value)
{
    isEnoughPoint = value;
}

int DialogMerchant::getEventNum() const
{
    return eventNum;
}

void DialogMerchant::setEventNum(int value)
{
    eventNum = value;
     count = 0;
}

void DialogMerchant::on_pushButton_clicked()
{
    switch (eventNum)
    {
    case 0:
        if(isEnoughPoint)
        {
            emit sendBuy(1);//买钥匙
        }
        break;
    case 1:
        if(isEnoughPoint)
        {
            emit sendBuy(2);//买血瓶
        }
        break;
    case 2:
        if(isEnoughPoint)
        {
            emit sendBuy(3);//买宝石
        }
        break;
    case 3:
        if(isEnoughPoint)
        {
            emit sendBuy(4);//买开门
        }
        break;
    case 4:
        if(isEnoughPoint)
        {
            emit sendBuy(5);//买结局
        }
        break;
    }
    ui->talkWithMer->appendPlainText(talkText[eventNum][count]);
    count++;
}
