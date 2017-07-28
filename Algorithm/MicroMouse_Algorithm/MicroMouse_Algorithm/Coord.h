#ifndef COORD_H
#define COORD_H

class Coord {

private:
    unsigned char row;
    unsigned char col;

public:
    Coord();
    Coord(unsigned char, unsigned char);

    ~Coord();

    void SetRow(unsigned char);
    void SetCol(unsigned char);
    unsigned char GetRow() const;
    unsigned char GetCol() const;

    bool MoveUp();
    bool MoveDown();
    bool MoveLeft();
    bool MoveRight();

    bool isInBounds();

	bool isNextTo(Coord);

    bool operator!=(const Coord&) const;

    /*Coord& operator=(const Coord &rhs) {
    row = rhs.row;
    col = rhs.col;
    }*/
};

#endif