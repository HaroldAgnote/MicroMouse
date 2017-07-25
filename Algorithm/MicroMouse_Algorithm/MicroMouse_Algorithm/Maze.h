#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"

class Maze
{
private:
    Cell cells[16][16];


public:
    Maze();

    void Initialize();

    void CalculateDistance();
    int CalculateManhattanDistance(int, int, int, int);
    int CalculateMinimum(int, int, int, int);

    void PrintDistance();
};

#endif