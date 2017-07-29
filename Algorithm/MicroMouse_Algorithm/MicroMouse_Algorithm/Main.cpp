#include <iostream>
#include "Maze.h"
#include "Mouse.h"
#include <thread>
#include <fstream>

using namespace std;

/*
int main()
{
    Coord start(15, 1);

    Maze maze("Maze.txt");
    
	Mouse mouse;

	//maze.PrintDistance();
    maze.PrintVisited(start);

    system("pause");

    mouse.floodFill(maze);
    cout << "Flood Fill Complete!" << endl;

    system("pause");
    return 0;
}
*/

int main()
{
    Coord start(15, 0);

    Maze maze("Maze3.txt");
    Mouse mouse;

    maze.printMaze(start);
    system("pause");
    mouse.floodFill(maze);

    printf("Flood Fill Complete!");

    system("pause");
    return 0;
}