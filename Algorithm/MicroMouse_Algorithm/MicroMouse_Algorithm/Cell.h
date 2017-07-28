#ifndef CELL_H
#define CELL_H

class Cell
{

private:
    bool mVisited;
    bool mWall;
	bool mNorth;
	bool mSouth;
	bool mEast;
	bool mWest;
    unsigned char mDistance;

public:
    Cell();
    Cell(bool);
    Cell(bool, bool);


    bool isVisited() const;
    bool isWall() const;

	bool hasNorthWall();
	bool hasSouthWall();
	bool hasEastWall();
	bool hasWestWall();

    unsigned char getDistance();


    void setVisited(bool);
    
	void setWall(bool);
	void setNorthWall(bool);
	void setSouthWall(bool);
	void setWestWall(bool);
	void setEastWall(bool);

    void setDistance(unsigned char);
};

#endif