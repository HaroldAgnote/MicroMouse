#ifndef MOUSE_H
#define MOUSE_H

#include "Coord.h"

#include "Maze.h"
#include "Cell.h"
#include <stack>

/*
 *  Representation of a mouse in lieu of the real thing.
 */
class Mouse
{

private:

    /*
     * Representation of a mouse in lieu of the real thing.
     */
    Maze completeMaze;
    
    /*
     * Coordinates from the goal of the maze to the starting position
     */
    stack <Coord> solution;

    /*
     * Size of the board
     */
    unsigned char mBoardSize;

	/*
	 * Mouse's position
	 */
    Coord mPosition;

    bool isInBounds(Coord);
    bool isInBounds(unsigned char, unsigned char);
    bool isAccessibleTo(Cell);
    bool isInGoal();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

public:
    Mouse();
    Mouse(string);
    
    const Coord getPosition();
    Maze * getMaze();

    bool isNextTo(Coord);

	void setPosition(unsigned char, unsigned char);
    void setPosition(Coord);
    void resetPosition();

	void floodFill();
    void floodFill(Maze);
	void floodFill(Maze, bool);

    void solveMaze();

	void moveToCell(Coord);

    void readCell();
	void readCell(Coord);
    void readCell(Coord, Cell);

	void visitCell();


	stack <Coord> getNeighbors();
	stack <Coord> getNeighbors(Maze);
};

#endif