#include "position.h"

Position::Position()
{
}

Position::Position(int layler,int x ,int y)
{
    this->layler=layler;
    this->x=x;
    this->y=y;
}

Position::Position(Position &p)
{
    this->layler=p.layler;
    this->x=p.x;
    this->y=p.y;
}

