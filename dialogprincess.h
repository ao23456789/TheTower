#ifndef DIALOGPRINCESS_H
#define DIALOGPRINCESS_H

#include <QDialog>

namespace Ui {
class DialogPrincess;
}

class DialogPrincess : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPrincess(QWidget *parent = nullptr);
    ~DialogPrincess();

    void keyPressEvent(QKeyEvent *event);
    void setText();



    int getEventNum() const;
    void setEventNum(int value);

private slots:



    void on_pushButton_clicked();

signals:
     void sendWithPr(bool YN);
private:
    Ui::DialogPrincess *ui;
    QString talkText[5][50];
    int count;
    int eventNum;
};

#endif // DIALOGPRINCESS_H
