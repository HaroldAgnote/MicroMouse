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

Cell::Cell(Coord coord)
{
    cellCoord = coord;
    mVisited = false;
    mNorth = false;
    mSouth = false;
    mWest = false;
    mEast = false;
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

Coord Cell::getCoordinates()
{
    return cellCoord;
}


unsigned char Cell::getDistance()
{
    return mDistance;
}

void Cell::setCoordinates(Coord coord)
{
    cellCoord = coord;
}


void Cell::setVisited(bool isVisited)
{
    mVisited = isVisited;
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

bool Cell::isAccessibleTo(Cell cell)
{
    if (cellCoord.isAbove(cell.cellCoord))
    {
        return !cell.hasNorthWall();
    }
    if (cellCoord.isBelow(cell.cellCoord))
    {
        return !cell.hasSouthWall();
    }
    if (cellCoord.isLeftOf(cell.cellCoord))
    {
        return !cell.hasWestWall();
    }
    if (cellCoord.isRightOf(cell.cellCoord))
    {
        return !cell.hasEastWall();
    }
}

void Cell::setDistance(unsigned char distance)
{
    mDistance = distance;
}

