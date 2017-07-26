#ifndef MAZE_H
#define MAZE_H

#include <string>
#include "Cell.h"

using namespace std;

class Coord;

class Maze
{
private:
    Cell cells[16][16];


public:
    Maze();
    Maze(string);

    void Initialize();

    Cell * getCell(Coord);

    void CalculateDistance();
    int CalculateManhattanDistance(int, int, int, int);
    int CalculateMinimum(int, int, int, int);

    void PrintDistance();
    void PrintVisited(Coord);
};

#endif