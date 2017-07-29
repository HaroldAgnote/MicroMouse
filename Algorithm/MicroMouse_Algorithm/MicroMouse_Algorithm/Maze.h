#ifndef MAZE_H
#define MAZE_H

#include <string>
#include "Cell.h"
#include "Coord.h"

using namespace std;

/*
 * Representation of a Maze
 */
class Maze
{
private:
    /*
     * 16 x 16 grid of the Maze
     */
    Cell cells[16][16];

    /*
     * String representation of the Maze
     */
    char cellString[33][81];

public:
    Maze();
    Maze(string);
    ~Maze();

    Cell & getCell(Coord);
    
    bool isFloodFilled();
    
    void markCellVisited(Coord);
    void markCellNorthWall(Coord);
    void markCellSouthWall(Coord);
    void markCellWestWall(Coord);
    void markCellEastWall(Coord);

    void resetMaze();

    void CalculateDistance();
    int CalculateManhattanDistance(int, int, int, int);
    int CalculateMinimum(int, int, int, int);

    void PrintDistance();
    void printMaze(Coord);
};

#endif