#ifndef MINE_H
#define MINE_H
#include <ctime>
#include <algorithm>
#include"tower.h"

class Mine
{
public:
    Mine();
    void newMap();

    int getMineNumberMap(int x,int y);
    void setMineNumberMap(int x,int y,int value);

    int getMines() const;
    void setMines(int value);

private:
    int mineNumberMap[9][9];//数字地图
    int mines;//地雷数


};

#endif // MINE_H
