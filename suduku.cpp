#include "suduku.h"
#include <QDebug>

Suduku::Suduku()
{
    srand((unsigned)(time(0)));//时间种子，初始化随机数发生器
    newMap();

}

void Suduku::newMap()
{
    //初始化
    blank = 40;
    for(int i=0;i<=9;i++)
    {
        for(int j=0;j<=9;j++)
        {
            suduMap[i][j] = 0;
            suduMapPlay[i][j] = 0;
        }
    }
    //第0行生成1-9
    for (int i = 1; i <= 9; i++)
    {
        suduMap[1][i] = i;
    }
    //随机打乱第一行
    int randnum1;
    int randnum2;
    int temp;
    for(int i=0;i<100;i++)
    {
         randnum1 = rand()%9+1;//[1-9]
         randnum2 = rand()%9+1;//[1-9]
         temp = suduMap[1][randnum1];
         suduMap[1][randnum1] = suduMap[1][randnum2];
         suduMap[1][randnum2] = temp;
    }
    fillMap(suduMap,2,1);
    randomSwapMap(suduMap);
    memcpy(suduMapPlay, suduMap, sizeof(int) * 100);//a复制到B
//希望和挖空数对应
    int x,y;
    while(blank != 0)
    {
        x = rand() % 9;//随机数为0到9之间
        y = rand() % 9;
        if(suduMapPlay[x+1][y+1] != 0)
        {
            suduMapPlay[x+1][y+1] = 0;
            blank--;
        }
    }
    findAns();




}

bool Suduku::fillMap(int (*num)[10], int r, int c)
{
    if (r > 9 || c > 9)
    {
        return 1;
    }
    for (int i = 1; i <= 9; ++i)
    {
        bool e = isExist(num, r, c, i);
        if (e)
        {
            continue;
        }
        else
        {
            num[r][c] = i;
            if (c == 9)
            {
                if (fillMap(num, r + 1, 1))
                {
                    return 1;
                }
                else
                {
                    num[r][c] = 0;
                    continue;
                }
            }
            else
            {
                if (fillMap(num, r, c + 1))
                {
                    return 1;
                }
                else
                {
                    num[r][c] = 0;
                    continue;
                }
            }
        }
    }
    return 0;
}

//判断是否合乎规则，给定的是r行c列的n，判断该行该列该九宫格
//合规返回0 ，不合规返回1
bool Suduku::isExist(int (*num)[10], int r, int c, int n)
{
    bool YN = false;
    for(int i=1; i<9;i++)
    {
        if(num[r][i] == n  && i!=c)
        {
            YN =true;
            return YN;
        }
    }
    for(int i=1;i<9;i++)
    {
        if(num[i][c] == n && i!=r)
        {
            YN = true;
            return YN;
        }
    }

    int gmr = (r - 1) / 3 * 3 + 1;//该九宫格最小行
    int gmc = (c - 1) / 3 * 3 + 1;//该九宫格最小列
        for (int i = gmr; i < gmr + 3; i++)
        {
            for (int j = gmc; j < gmc + 3; ++j)
            {
                if (  (!(i==r && j==c)) && (num[i][j] == n) )
                {
                    YN = 1;
                }
            }
        }
        return YN;
}

void Suduku::randomSwapMap(int (*a)[10])
{
    for (int c = 0; c < 99; c++)//三列一组内部随机乱交换
    {
        int p = rand() % 3 * 3 + 1;//p随机为147中一个
        int m = p + rand() % 3;//p为1，m,n为123中随机一个
        int n = p + rand() % 3;
        swapColumnMap(a, m, n);
    }

    //三列一组，按组随机交换十次
    for(int i=0;i<10;i++)
    {
        int p = rand() % 3 * 3 + 1;
        if (p == 1 || p == 4)
        {//例如123列和456列换
            swapColumnMap(a, p, p + 3);
            swapColumnMap(a, p + 1, p + 4);
            swapColumnMap(a, p + 2, p + 5);
        }
        else
        {
            swapColumnMap(a, p, p - 6);
            swapColumnMap(a, p + 1, p - 5);
            swapColumnMap(a, p + 2, p - 4);
        }
    }
}

void Suduku::swapColumnMap(int (*a)[10], int m, int n)
{
    int t[10];//交换数组
    for (int i = 1; i <= 9; i++)
    {
        t[i] = a[i][m];
    }
    for (int i = 1; i <= 9; i++)
    {
        a[i][m] = a[i][n];
    }
    for (int i = 1; i <= 9; i++)
    {
        a[i][n] = t[i];
    }
}

void Suduku::findAns()
{
    int temp =0;
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            if(suduMapPlay[i][j] == 0)
            {
                temp++;
                if(temp == 21)
                {
                    setAns(suduMap[i][j]);
                }
            }

        }
    }
}



void Suduku::setSuduMap(int x, int y, int value)
{
    suduMap[x][y] = value;
}

int Suduku::getSuduMap(int x, int y)
{
    return suduMap[x][y];
}

void Suduku::setSuduMapPlay(int x, int y, int value)
{
    suduMapPlay[x][y] = value;
}

int Suduku::getSuduMapPlay(int x, int y)
{
    return suduMapPlay[x][y];
}

int Suduku::getAns() const
{
    return ans;
}

void Suduku::setAns(int value)
{
    ans = value;
}
