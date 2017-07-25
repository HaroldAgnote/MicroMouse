#include "Cell.h"

#include <iostream>
using namespace std;

Cell::Cell()
{
    mVisited = false;
    mWall = false;
}

Cell::Cell(bool isWall)
{
    mVisited = false;
    mWall = isWall;
}

Cell::Cell(bool isVisited, bool isWall)
{
    mVisited = isVisited;
    mWall = isWall;
}

bool Cell::isVisited()
{
    return mVisited;
}

bool Cell::isWall()
{
    return mWall;
}

unsigned char Cell::getDistance()
{
    return mDistance;
}

void Cell::setVisited(bool isVisited)
{
    mVisited = isVisited;
}

void Cell::setWall(bool isWall)
{
    mWall = isWall;
}

void Cell::setDistance(unsigned char distance)
{
    mDistance = distance;
}

