#include "Cell.h"

#include <iostream>
using namespace std;

/*
 * Default Constructor of Cell that sets all indicators to False
 */
Cell::Cell()
{
    mVisited = false;
	mNorthWall = false;
	mSouthWall = false;
	mWestWall = false;
	mEastWall = false;
}

/*
 * Constructor of Cell that sets its Coordinates and all indicators to False
 */
Cell::Cell(Coord coord)
{
    cellCoord = coord;
    mVisited = false;
    mNorthWall = false;
    mSouthWall = false;
    mWestWall = false;
    mEastWall = false;
}

/*
 * Returns the state of visitation of the Cell
 */
bool Cell::isVisited() const
{
    return mVisited;
}

/*
 * Returns whether the Cell has a North Wall or not
 */
bool Cell::hasNorthWall()
{
    return mNorthWall;
}

/*
 * Returns whether the Cell has a South Wall or not
 */
bool Cell::hasSouthWall()
{
    return mSouthWall;
}
/*
 * Returns whether the Cell has a East Wall or not
 */
bool Cell::hasEastWall()
{
    return mEastWall;
}
/*
 * Returns whether the Cell has a West Wall or not
 */
bool Cell::hasWestWall()
{
    return mWestWall;
}

/*
 * Returns the set of Coordinates of the Cell
 */
Coord Cell::getCoordinates()
{
    return cellCoord;
}

/*
 * Returns the distance of the Cell to the Center
 */
unsigned char Cell::getDistance()
{
    return mDistance;
}

/*
 * Modifies the status of the Cell's visitation
 */
void Cell::setVisited(bool isVisited)
{
    mVisited = isVisited;
}

/*
 * Modifies the status of the Cell's North Wall
 */
void Cell::setNorthWall(bool boolean)
{
    mNorthWall = boolean;
}

/*
 * Modifies the status of the Cell's South Wall
 */
void Cell::setSouthWall(bool boolean)
{
    mSouthWall = boolean;
}

/*
 * Modifies the status of the Cell's East Wall
 */
void Cell::setEastWall(bool boolean)
{
    mEastWall = boolean;
}

/*
 * Modifies the status of the Cell's West Wall
 */
void Cell::setWestWall(bool boolean)
{
    mWestWall = boolean;
}

/*
 * Modifies the Cell's coordinates given a set of Coordinates
 */
void Cell::setCoordinates(Coord coord)
{
    cellCoord = coord;
}

/*
 * Modifies the Cell's Distance to the Center
 */
void Cell::setDistance(unsigned char distance)
{
    mDistance = distance;
}

/*
 * Checks if a given Cell is Accessible from the current Cell
 */
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
    return false;
}
