#include <iostream>
#include "Maze.h"
#include "Mouse.h"
#include "Cell.h"
#include <queue>
#include <stack>
#include <chrono>
#include <thread>

using namespace std;

void floodFill();

int main()
{
    Maze maze;
    maze.Initialize();
    maze.PrintDistance();

    floodFill();
    cout << endl << endl << endl;

    system("pause");
    return 0;

}

void floodFill()
{
    Coord current, start(15,1);
    Cell * currentCell = NULL;

    queue <Coord> cellsToCheck;
    stack <Coord> previousCells;

    Mouse mouse;

    cellsToCheck.push(mouse.GetPosition());

    Maze * maze = mouse.GetMaze();

    do
    {
        do
        {
            current = cellsToCheck.front();
            cellsToCheck.pop();
            currentCell = maze->getCell(current);
        } while (cellsToCheck.size() > 1 && (currentCell != NULL && (currentCell->isWall() || currentCell->isVisited())) || current != start && !current.isInBounds());
        
        while (current != mouse.GetPosition())
        {
            if (mouse.isNextTo(current))
            {
                mouse.MoveToCell(current);
            }
            else
            {
                Coord prev = previousCells.top();
                mouse.MoveToCell(prev);
                previousCells.pop();
            }
        }

        currentCell->setVisited(true);
        
        // Queue <Coord> neighbors = getNeighbors(current);

        queue <Coord> neighbors;
        Coord up(current.GetRow() - 1, current.GetCol());
        Coord down(current.GetRow() + 1, current.GetCol());
        Coord left(current.GetRow(), current.GetCol() - 1);
        Coord right(current.GetRow(), current.GetCol() + 1);

        neighbors.push(up);
        neighbors.push(down);
        neighbors.push(left);
        neighbors.push(right);

        while (!neighbors.empty())
        {
            cellsToCheck.push(neighbors.front());
            neighbors.pop();
        }

        previousCells.push(current);

        maze->PrintVisited(mouse.GetPosition());
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    while (!cellsToCheck.empty());
}
/*
Queue <Coord> getNeighbors(Coord mousePos)
{
    Queue <Coord> neighbors;
    cout << "Checking for neighbors..." << endl;
    Coord up(mousePos.GetRow() - 1, mousePos.GetCol());
    Coord down(mousePos.GetRow() + 1, mousePos.GetCol());
    Coord left(mousePos.GetRow(), mousePos.GetCol() - 1);
    Coord right(mousePos.GetRow(), mousePos.GetCol() + 1);

    neighbors.enqueue(up);
    neighbors.enqueue(down);
    neighbors.enqueue(left);
    neighbors.enqueue(right);

    return neighbors;
}
*/