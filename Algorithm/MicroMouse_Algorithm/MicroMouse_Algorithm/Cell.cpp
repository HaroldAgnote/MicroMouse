#include "Cell.h"

#include <iostream>
using namespace std;

Cell::Cell()
{
    mVisited = false;
	mNorth = false;
	mSouth = false;
	mWest = false;
	mEast = false;
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

bool Cell::hasNorthWall()
{
    return mNorth;
}

bool Cell::hasSouthWall()
{
    return mSouth;
}

bool Cell::hasEastWall()
{
    return mEast;
}

bool Cell::hasWestWall()
{
    return mWest;
}

bool Cell::isVisited() const
{
    return mVisited;
}

bool Cell::isWall() const
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

void Cell::setNorthWall(bool boolean)
{
    mNorth = boolean;
}

void Cell::setSouthWall(bool boolean)
{
    mSouth = boolean;
}

void Cell::setEastWall(bool boolean)
{
    mEast = boolean;
}

void Cell::setWestWall(bool boolean)
{
    mWest = boolean;
}


void Cell::setDistance(unsigned char distance)
{
    mDistance = distance;
}

