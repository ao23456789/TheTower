#ifndef DIALOGELF_H
#define DIALOGELF_H
#include <QDialog>
#include <QDebug>

namespace Ui {
class DialogElf;
}

class DialogElf : public QDialog
{
    Q_OBJECT

public:
    explicit DialogElf(QWidget *parent = nullptr);
    ~DialogElf();

    void setTxet(int i,int j,QString str);
    void setText();

    //键盘事件
     void keyPressEvent(QKeyEvent *event);

     int getEventNum() const;
     //事件值
     void setEventNum(int value);

     bool getIsEnoughPoint() const;
     void setIsEnoughPoint(bool value);

signals:
     void sendRecuoerate(int num);
     void dedication(bool YN);


private slots:
     void on_pushButton_clicked();

     void on_pushButton_2_clicked();

private:
     QString talkText[5][50];
     int count;
    int eventNum;
    bool isEnoughPoint;

private:
    Ui::DialogElf *ui;

};

#endif // DIALOGELF_H

