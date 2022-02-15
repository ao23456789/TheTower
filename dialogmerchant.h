#ifndef DIALOGMERCHANT_H
#define DIALOGMERCHANT_H

#include <QDialog>
#include <QKeyEvent>
namespace Ui {
class DialogMerchant;
}

class DialogMerchant : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMerchant(QWidget *parent = nullptr);
    ~DialogMerchant();

    //键盘事件
     void keyPressEvent(QKeyEvent *event);
     void setText();




     bool getIsEnoughPoint() const;
     void setIsEnoughPoint(bool value);
     int getEventNum() const;
     void setEventNum(int value);

private slots:
     void on_pushButton_clicked();


signals:
     void sendBuy(int num);

private:
     Ui::DialogMerchant *ui;

     QString talkText[7][50];
     int count;
    int eventNum;
    bool isEnoughPoint;
};

#endif // DIALOGMERCHANT_H
