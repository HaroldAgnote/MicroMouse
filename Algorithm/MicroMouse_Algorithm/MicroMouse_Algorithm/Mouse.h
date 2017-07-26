#ifndef MOUSE_H
#define MOUSE_H

#include "Coord.h"

#include "Maze.h"
#include "Cell.h"


class Mouse {

    // Representation of a mouse in lieu of the real thing.

private:
    Maze completeMaze; // Internal representation of the maze

    unsigned char mBoardSize;
    Coord mPosition;
    bool InBounds(Coord);
    bool InBounds(unsigned char, unsigned char);
    void SetUpMaze();

public:
    Mouse();
    Mouse(string);
    Mouse(unsigned char);
    
    const Coord GetPosition();
    Maze * GetMaze();

    bool isNextTo(Coord);

    void SetPosition(unsigned char, unsigned char);
    void MoveToCell(Coord);
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void ReadCell(Coord, Cell);
};

#endif