#ifndef CELL_H
#define CELL_H
#include "Coord.h"

/*
 * Representation of a Cell that resides in a Maze
 */

class Cell
{

private:
    /*
     * Indicator representing if the Cell has been visited
     */
    bool mVisited;
    
    /*
     * Indicator representing if the Cell has a North Wall
     */
	bool mNorthWall;

    /*
     * Indicator representing if the Cell has a South Wall
     */
	bool mSouthWall;

    /*
     * Indicator representing if the Cell has an East Wall
     */
	bool mEastWall;

    /*
     * Indicator representing if the Cell has a West Wall
     */
	bool mWestWall;

    /*
     * The Coordinates of where the Cell Resides
     */
    Coord cellCoord;

    /*
     * Distance of this Cell to the Center of the Maze
     */
    unsigned char mDistance;

public:
    Cell();
    Cell(Coord);

    bool isVisited() const;

	bool hasNorthWall();
	bool hasSouthWall();
	bool hasEastWall();
	bool hasWestWall();

    Coord getCoordinates();

    unsigned char getDistance();

    void setVisited(bool);

    void setNorthWall(bool);
    void setSouthWall(bool);
    void setWestWall(bool);
    void setEastWall(bool);
    
    void setCoordinates(Coord);

    void setDistance(unsigned char);

    bool isAccessibleTo(Cell);
};

#endif