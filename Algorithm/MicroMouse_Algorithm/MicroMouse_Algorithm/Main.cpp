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
    Coord start(15, 1);

    Maze maze("Maze.txt");
    //maze.PrintDistance();
    maze.PrintVisited(start);

    system("pause");

    floodFill();
    cout << "Flood Fill Complete!" << endl;

    system("pause");
    return 0;

}

void floodFill()
{
    long DELAY = 250;

    bool valid = false;

    Coord current, start(15,1);
    Cell * currentCell = NULL;

    stack <Coord> cellsToCheck;
    stack <Coord> previousCells;

    Mouse mouse("Maze.txt");

    cellsToCheck.push(mouse.GetPosition());

    Maze * maze = mouse.GetMaze();

    do
    {
        do
        {
            valid = false;

            if (cellsToCheck.empty())
            {
                return;
            }

            current = cellsToCheck.top();
            cellsToCheck.pop();

            currentCell = maze->getCell(current);

            if (current.isInBounds())
            {
                if (!currentCell->isVisited() && !currentCell->isWall())
                {
                    valid = true;
                }
            }

        } while (!valid);
        
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
            maze->PrintVisited(mouse.GetPosition());
            this_thread::sleep_for(chrono::milliseconds(DELAY));
        }

        currentCell->setVisited(true);
        
        // Queue <Coord> neighbors = getNeighbors(current);

        stack <Coord> neighbors;
        Coord up(current.GetRow() - 1, current.GetCol());
        Coord down(current.GetRow() + 1, current.GetCol());
        Coord left(current.GetRow(), current.GetCol() - 1);
        Coord right(current.GetRow(), current.GetCol() + 1);

        
        neighbors.push(down);
        neighbors.push(left);
        neighbors.push(right);
        neighbors.push(up);

        while (!neighbors.empty())
        {
            Coord nextCell = neighbors.top();
            if (!maze->getCell(nextCell)->isWall())
            {
                cellsToCheck.push(neighbors.top());
            }
            neighbors.pop();
        }

        previousCells.push(current);

        maze->PrintVisited(mouse.GetPosition());
        this_thread::sleep_for(chrono::milliseconds(DELAY));
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