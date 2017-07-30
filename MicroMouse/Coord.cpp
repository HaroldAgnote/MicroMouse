#include "Coord.h"

/*
 * Default Constructor of Set of Coordinates which sets Coordinates to start of Maze
 */
Coord::Coord()
{
    row = 15;
    col = 0;
}

/*
 * Constructor that sets Coordinates to a gien row and column
 */
Coord::Coord(unsigned char row, unsigned char col) : row(row), col(col)
{

}

/*
 * Destructor
 */
Coord::~Coord()
{

}

/*
 * Returns the row of the Coordinate
 */
unsigned char Coord::GetRow() const
{
    return row;
}

/*
 * Returns the column of the Coordinate
 */
unsigned char Coord::GetCol() const
{
    return col;
}

/*
 * Modifies the row of the Coordinate
 */
void Coord::SetRow(unsigned char row) {
    this->row= row;
}

/*
 * Modifies the column of the Coordinate
 */
void Coord::SetCol(unsigned char col) {
    this->col = col;
}

/*
 * Indicates if the Coordinate is within the bounds of the Maze
 */
bool Coord::isInBounds()
{
    // Board dimension is 16 x 16
    return row >= 0 && row < 16 && col >= 0 && col < 16;
}

/*
 * Indicates if the Coordinate is adjacent to another given set of Coordinates
 */
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

/*
 * Indicates if the Coordinate is above another set of Coordinates
 */
bool Coord::isAbove(Coord coord)
{
    return row == (coord.row - 1);
}

/*
 * Indicates if the Coordinate is below another set of Coordinates
 */
bool Coord::isBelow(Coord coord)
{
    return row == (coord.row + 1);
}

/*
 * Indicates if the Coordinate is to the Left of another set of Coordinates
 */
bool Coord::isLeftOf(Coord coord)
{
    return col == (coord.col - 1);
}

/*
 * Indicates if the Coordinate is to the Right of another set of Coordinates
 */
bool Coord::isRightOf(Coord coord)
{
    return col == (coord.col + 1);

}

/*
 * Adjusts the Coordinates up one row
 */
void Coord::MoveUp() {
    row -= 1;
}

/*
 * Adjusts the Coordinates down one row
 */
void Coord::MoveDown() {
    row += 1;
}

/*
 * Adjusts the Coordinates left one column
 */
void Coord::MoveLeft() {
    col -= 1;
}

/*
 * Adjusts the Coordinates right one column
 */
void Coord::MoveRight() {
    col += 1;
}

/*
 * Overloaded Operator that tests if the Coordinate is equal to another set of Coordinates
 */
bool Coord::operator==(const Coord & coord) const
{
    return (row == coord.row && col == coord.col);
}

/*
 * Overloaded Operator that test if the Coordinate is not equal to another set of Coordinates
 */
bool Coord::operator!=(const Coord & coord) const
{
    return !(row == coord.row && col == coord.col);
}






