#include <iostream>
#include "Maze.h"
#include "Mouse.h"
#include <thread>
#include <fstream>

using namespace std;

int main()
{
    Coord start(15, 0);

    Maze maze("Maze3.txt");
    Mouse mouse;

    maze.printMaze(start);
    system("pause");
    mouse.floodFill(maze);

    if (mouse.getMaze()->isFloodFilled())
    {
        printf("Flood Fill Complete!\n");
    }
    else
    {
        printf("Flood Fill Fail :( \n");
    }

    system("pause");
    return 0;
}