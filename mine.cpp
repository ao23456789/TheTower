#include "mine.h"

Mine::Mine()
{
    mines=10;
    srand(time(NULL));//以当前时间为随机种子，保证随机性
    newMap();
}

void Mine::newMap()
{
    //初始化
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            mineNumberMap[i][j] = 0;
        }
    }

    int r_x=0, r_y=0;
    int m = mines;//剩余地雷数

    //埋雷---采用随机生成雷坐标的方式,雷使用9
    while(m != 0)
    {
        r_x = rand() % 9;//随机数[0，8]
        r_y = rand() % 9;

        if(mineNumberMap[r_x][r_y] == 0)//判断是否已经为雷
        {
            mineNumberMap[r_x][r_y] = 9;
            m--;
        }
    }
    //雷周围一圈+1
    int x1, x2, y1, y2;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(mineNumberMap[i][j] == 9)
            {
                //x1,y1,x2,y2为以一个点为中心的九宫格3*3
                x1 = (i-1>=0)? i-1 : i;//如果是第一行(i-1)<0，就取0
                x2 = (i+1<9)? i+1 : i;//如果是最后一行i+1>9,就取8
                y1 = (j-1 >= 0) ? (j-1) : j;
                y2 = (j+1 < 9) ? (j+1) : j;
            for(int i=x1;i<=x2;i++)
            {
                for(int j=y1;j<=y2;j++)
                {
                    if(mineNumberMap[i][j] != 9)
                    {
                        mineNumberMap[i][j]++;
                    }
                }
            }
          }
        }
    }
}

int Mine::getMineNumberMap(int x, int y)
{
    return mineNumberMap[x][y];
}
void Mine::setMineNumberMap(int x, int y, int value)
{
    mineNumberMap[x][y] = value;
}


int Mine::getMines() const
{
    return mines;
}

void Mine::setMines(int value)
{
    mines = value;
}

