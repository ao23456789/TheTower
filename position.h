#ifndef POSITION_H
#define POSITION_H


class Position
{

public:
    int layler;
    int x;
    int y;
public:
    Position();

    Position(int,int,int);
    //拷贝构造方法
    Position(Position &p);

    bool operator ==(const Position p)
    {
        return (p.x==x)&&(p.y==y)&(p.layler==layler);
    }

};



#endif // POSITION_H
