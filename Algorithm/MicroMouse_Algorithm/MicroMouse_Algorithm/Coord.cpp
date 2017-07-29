#include "Coord.h"

Coord::Coord() {

}

Coord::Coord(unsigned char row, unsigned char col) : row(row), col(col) {

}

Coord::~Coord() {

}

void Coord::SetRow(unsigned char row) {
    row= row;
}

void Coord::SetCol(unsigned char col) {
    col = col;
}

unsigned char Coord::GetRow() const {
    return row;
}

unsigned char Coord::GetCol() const {
    return col;
}

bool Coord::MoveUp() {
    row -= 1;
    return false;
}

bool Coord::MoveDown() {
    row += 1;
    return false;
}

bool Coord::MoveLeft() {
    col -= 1;
    return false;
}

bool Coord::MoveRight() {
    col += 1;
    return false;
}

bool Coord::operator ==(const Coord & coord) const
{
    return (row == coord.row && col == coord.col);
}

bool Coord::operator !=(const Coord & coord) const
{
    return !(row == coord.row && col == coord.col);
}


bool Coord::isInBounds()
{
    return row >= 0 && row < 16 && col >= 0 && col < 16; // Board size is 16
}

bool Coord::isNextTo(Coord coord)
{
	if (row == coord.row)
	{
        return (col == (coord.col + 1)) || (col == (coord.col - 1));
	}
	if (col == coord.col)
	{
		return (row == (coord.row + 1)) || (row == (coord.row - 1));
	}
	return false;
}

bool Coord::isAbove(Coord coord)
{
    return row == (coord.row - 1);
}

bool Coord::isBelow(Coord coord)
{
    return row == (coord.row + 1);
}

bool Coord::isLeftOf(Coord coord)
{
    return col == (coord.col - 1);
}

bool Coord::isRightOf(Coord coord)
{
    return col == (coord.col + 1);

}




