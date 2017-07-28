#ifndef MOUSE_H
#define MOUSE_H

#include "Coord.h"

#include "Maze.h"
#include "Cell.h"
#include <stack>


class Mouse {

    // Representation of a mouse in lieu of the real thing.

private:
    Maze completeMaze; // Internal representation of the maze

    unsigned char mBoardSize;

	/*
	 * Mouse's position
	 */
    Coord mPosition;

    bool isInBounds(Coord);
    bool isInBounds(unsigned char, unsigned char);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

public:
    Mouse();
    Mouse(string);
    Mouse(unsigned char);
    
    const Coord getPosition();
    Maze * getMaze();

    bool isNextTo(Coord);

	void setPosition(unsigned char, unsigned char);

	void floodFill();
	void floodFill(Maze);

	void moveToCell(Coord);

	void readCell(Coord);
    void readCell(Coord, Cell);

	void visitCell();


	stack <Coord> getNeighbors();
	stack <Coord> getNeighbors(Maze);
};

#endif