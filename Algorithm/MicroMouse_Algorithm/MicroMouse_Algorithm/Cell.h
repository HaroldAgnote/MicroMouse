#ifndef CELL_H
#define CELL_H

class Cell
{

private:
    bool mVisited;
    bool mWall;
    unsigned char mDistance;

public:
    Cell();
    Cell(bool);
    Cell(bool, bool);


    bool isVisited() const;
    bool isWall() const;
    unsigned char getDistance();


    void setVisited(bool);
    void setWall(bool);
    void setDistance(unsigned char);
};

#endif