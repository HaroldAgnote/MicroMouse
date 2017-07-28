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
    char cellString[33][81];

public:
    Maze();
    Maze(string);
    ~Maze();

    Cell & getCell(Coord);
    
    void markCellVisited(Coord);
    void markCellNorthWall(Coord);
    void markCellSouthWall(Coord);
    void markCellWestWall(Coord);
    void markCellEastWall(Coord);

    void CalculateDistance();
    int CalculateManhattanDistance(int, int, int, int);
    int CalculateMinimum(int, int, int, int);

    void PrintDistance();
    void printMaze(Coord);
    void PrintVisited(Coord);
};

#endif