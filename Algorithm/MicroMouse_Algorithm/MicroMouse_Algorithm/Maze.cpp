#include <iostream>
#include <cmath>
#include "Maze.h"
#include "Queue.h"
#include "Mouse.h"
#include "Cell.h"
using namespace std;

Maze::Maze()
{
    Initialize();
}

void Maze::Initialize()
{
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i == 0 || i == 15 || j == 0 || j == 15)
            {
                cells[i][j].setWall(true);
                cells[i][j].setDistance(-1);
            }
            else if ((i == 7 || i == 8) && (j == 7 || j == 8))
            {
                // Center of maze.
                cells[i][j].setWall(false);
                cells[i][j].setDistance(0);
            }
            else
            {
                // Other areas of maze.
                cells[i][j].setDistance(-1);
            }
            cells[i][j].setVisited(false);
        }
    }
    CalculateDistance();
}

void Maze::CalculateDistance()
{
    // Objective is (7, 7), (7, 8), (8, 7), or (8, 8).
    // Calculate manhattan distance and use shortest one.
    int cornerOne = 7;
    int cornerTwo = 8;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            cells[i][j].setDistance(
                CalculateMinimum(
                    CalculateManhattanDistance(i, j, cornerOne, cornerOne),
                    CalculateManhattanDistance(i, j, cornerOne, cornerTwo),
                    CalculateManhattanDistance(i, j, cornerTwo, cornerOne),
                    CalculateManhattanDistance(i, j, cornerTwo, cornerTwo)
                )
            );
        }
    }
}

int Maze::CalculateManhattanDistance(int currentX, int currentY, int objectiveX, int objectiveY)
{
    return abs((double)currentX - objectiveX) + abs((double)currentY - objectiveY);
}

int Maze::CalculateMinimum(int a, int b, int c, int d)
{
    int minimum = a;
    if (b < minimum) {
        minimum = b;
    }
    if (c < minimum) {
        minimum = c;
    }
    if (d < minimum) {
        minimum = d;
    }
    return minimum;
}

void Maze::PrintDistance()
{
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (cells[i][j].getDistance() >= 10) {
                printf("%d ", cells[i][j].getDistance());
            }
            else {
                printf(" %d ", cells[i][j].getDistance());
            }
        }
        printf("\n");
    }
}