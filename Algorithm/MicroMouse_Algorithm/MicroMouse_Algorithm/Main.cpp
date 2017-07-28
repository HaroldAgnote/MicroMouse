#include <iostream>
#include "Maze.h"
#include "Mouse.h"
#include <thread>

using namespace std;


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