#ifndef SUDUKU_H
#define SUDUKU_H
#include <ctime>
#include <algorithm>
#include <QMainWindow>
#include "tower.h"
class Suduku
{
public:
    Suduku();
    void newMap();
    bool fillMap(int(*num)[10], int r, int c);
    bool isExist(int(*num)[10], int r, int c,int n);
    //先生成第一排再随机打乱，然后再按规则填满数组
    void randomSwapMap(int(*a)[10]);
    void swapColumnMap(int(*a)[10], int m, int n);
    void findAns();



    void setSuduMap(int x,int y,int value);
    int getSuduMap(int x,int y);
    void setSuduMapPlay(int x,int y,int value);
    int getSuduMapPlay(int x,int y);
    int getAns() const;
    void setAns(int value);

private:
    int suduMap[10][10];
    int suduMapPlay[10][10];
    int blank;
    int ans;



};

#endif // SUDUKU_H
