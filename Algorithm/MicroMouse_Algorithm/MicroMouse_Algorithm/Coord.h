#ifndef COORD_H
#define COORD_H

/*
 * Representation of a Set of Coordinates (x, y) within a Maze
 */
class Coord
{
private:
    /*
     * The row of the Coordinate (x)
     */
    unsigned char row;

    /*
     * The columns of the Coordinate (y)
     */
    unsigned char col;

public:
    Coord();
    Coord(unsigned char, unsigned char);

    ~Coord();

    unsigned char GetRow() const;
    unsigned char GetCol() const;

    void SetRow(unsigned char);
    void SetCol(unsigned char);

    bool isInBounds();

    bool isNextTo(Coord);

    bool isAbove(Coord);
    bool isBelow(Coord);
    bool isLeftOf(Coord);
    bool isRightOf(Coord);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    bool operator==(const Coord &) const;
    bool operator!=(const Coord&) const;

};

#endif