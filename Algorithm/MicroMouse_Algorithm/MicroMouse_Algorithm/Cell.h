#ifndef CELL_H
#define CELL_H
#include "Coord.h"

class Cell
{

private:

    Coord cellCoord;

    bool mVisited;
    bool mWall;
	bool mNorth;
	bool mSouth;
	bool mEast;
	bool mWest;
    unsigned char mDistance;

public:
    Cell();
    Cell(Coord);


    bool isVisited() const;
    bool isWall() const;

	bool hasNorthWall();
	bool hasSouthWall();
	bool hasEastWall();
	bool hasWestWall();

    Coord getCoordinates();

    unsigned char getDistance();

    void setCoordinates(Coord);

    void setVisited(bool);
    
	void setNorthWall(bool);
	void setSouthWall(bool);
	void setWestWall(bool);
	void setEastWall(bool);

    bool isAccessibleTo(Cell);

    void setDistance(unsigned char);
};

#endif