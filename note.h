#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include "Monster.h"
#include "map.h"
#include <QKeyEvent>

namespace Ui {
class Note;
}

class Note : public QWidget
{
    Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr);
    ~Note();
public slots:
    void noteRecvData(Monster *monster);

    void whatKindMonster(int kind);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Note *ui;
    QString str0;
};

#endif // NOTE_H
