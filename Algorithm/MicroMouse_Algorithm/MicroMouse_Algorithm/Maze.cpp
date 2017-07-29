#include <iostream>
#include <fstream>
#include <cmath>
#include "Maze.h"
#include "Queue.h"
#include "Mouse.h"
#include "Cell.h"
#include <string>
using namespace std;


/*
 * Create empty maze
 */
Maze::Maze()
{
    for (int i = 0; i < 33; i++)
    {
        for (int j = 0; j < 81; j++)
        {
            cellString[i][j] = ' ';
            if (i == 0 || i == 32)
            {
                cellString[i][j] = '-';
            }
            if (i % 2 == 0 && j % 5 == 0)
            {
                if (i == 16 && j == 40)
                {
                    cellString[i][j] = ' ';
                }
                else
                {
                    cellString[i][j] = '+';
                }
            }
            if (i % 2 == 1 && (j == 0 || j == 80))
            {
                cellString[i][j] = '|';
            }
            if (i == 15 || i == 17)
            {
                if (j == 38 || j == 42)
                {
                    cellString[i][j] = 'G';
                }
            }
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i == 0 || i == 15 || j == 0 || j == 15)
            {
                if (i == 0)
                {
                    cells[i][j].setNorthWall(true);
                }
                if (i == 15)
                {
                    cells[i][j].setSouthWall(true);
                }
                if (j == 0)
                {
                    cells[i][j].setWestWall(true);
                }
                if (j == 15)
                {
                    cells[i][j].setEastWall(true);
                }
                cells[i][j].setDistance(-1);
            }
            else if ((i == 7 || i == 8) && (j == 7 || j == 8))
            {
                // Center of maze.
                cells[i][j].setDistance(0);
            }
            else
            {
                // Other areas of maze.
                cells[i][j].setDistance(-1);
            }
            Coord coord(i, j);
            cells[i][j].setCoordinates(coord);
            cells[i][j].setVisited(false);
        }
    }
    CalculateDistance();
}

Maze::~Maze()
{

    

}

/*
 * Create maze generated from reading a text file
 */
Maze::Maze(string fileName)
{
    ifstream myFile;

    myFile.open(fileName);
    string LINE;
    for (int i = 0; i < 33; i++)
    {
        getline(myFile, LINE);
        for (int j = 0; j < LINE.size(); j++)
        {
            cellString[i][j] = LINE.at(j);
            if (i == 15 || i == 17)
            {
                if (j == 38 || j == 42)
                {
                    cellString[i][j] = 'G';
                }
            }
        }
    }


    int f = 1;

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            Coord coord(i, j);
            if (cellString[f - 1][(j * 5) + 2] != ' ')
            {
                cells[i][j].setNorthWall(true);
            }
            if (cellString[f][j * 5] != ' ')
            {
                cells[i][j].setWestWall(true);
            }
            if (cellString[f][(j * 5) + 5] != ' ')
            {
                cells[i][j].setEastWall(true);
            }
            if (cellString[f + 1][(j * 5) + 2] != ' ')
            {
                cells[i][j].setSouthWall(true);
            }
            cells[i][j].setCoordinates(coord);
        }
        f += 2;
    }
}

/*
 * Get a Cell given a set of coordinates
 */
Cell & Maze::getCell(Coord cellCoord)
{
    return cells[cellCoord.GetRow()][cellCoord.GetCol()];
}

bool Maze::isFloodFilled()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (!cells[i][j].isVisited())
            {
                return false;
            }
        }
    }
    return true;
}


void Maze::markCellVisited(Coord cellCoord)
{
    int cellString_Row = (cellCoord.GetRow() * 2) + 1;
    int cellString_Col = (cellCoord.GetCol() * 5) + 2;

    cellString[cellString_Row][cellString_Col + 0] = '*';
    cellString[cellString_Row][cellString_Col + 1] = '*';
}

void Maze::markCellNorthWall(Coord cellCoord)
{
    int cellString_Row = (cellCoord.GetRow() * 2) + 1;
    int cellString_Col = (cellCoord.GetCol() * 5) + 2;

    cellString[cellString_Row - 1][cellString_Col - 1] = '-';
    cellString[cellString_Row - 1][cellString_Col + 0] = '-';
    cellString[cellString_Row - 1][cellString_Col + 1] = '-';
    cellString[cellString_Row - 1][cellString_Col + 2] = '-';
}

void Maze::markCellSouthWall(Coord cellCoord)
{
    int cellString_Row = (cellCoord.GetRow() * 2) + 1;
    int cellString_Col = (cellCoord.GetCol() * 5) + 2;

    cellString[cellString_Row + 1][cellString_Col - 1] = '-';
    cellString[cellString_Row + 1][cellString_Col + 0] = '-';
    cellString[cellString_Row + 1][cellString_Col + 1] = '-';
    cellString[cellString_Row + 1][cellString_Col + 2] = '-';
}

void Maze::markCellWestWall(Coord cellCoord)
{
    int cellString_Row = (cellCoord.GetRow() * 2) + 1;
    int cellString_Col = (cellCoord.GetCol() * 5) + 2;

    cellString[cellString_Row][cellString_Col - 2] = '|';
}

void Maze::markCellEastWall(Coord cellCoord)
{
    int cellString_Row = (cellCoord.GetRow() * 2) + 1;
    int cellString_Col = (cellCoord.GetCol() * 5) + 2;

    cellString[cellString_Row][cellString_Col + 3] = '|';
}

void Maze::resetMaze()
{
    for (int i = 0; i < 33; i++)
    {
        for (int j = 0; j < 81; j++)
        {
            cellString[i][j] = ' ';
            if (i == 0 || i == 32)
            {
                cellString[i][j] = '-';
            }
            if (i % 2 == 0 && j % 5 == 0)
            {
                if (i == 16 && j == 40)
                {
                    cellString[i][j] = ' ';
                }
                else
                {
                    cellString[i][j] = '+';
                }
            }
            if (i % 2 == 1 && (j == 0 || j == 80))
            {
                cellString[i][j] = '|';
            }

        }
    }
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

void Maze::printMaze(Coord mousePosition)
{
    system("cls");
    
    int cellString_Row = (mousePosition.GetRow() * 2) + 1;
    int cellString_Col = (mousePosition.GetCol() * 5) + 2;

    for (int i = -1; i < 33; i++)
    {
        for (int j = -1; j < 81; j++)
        {
            if (i == -1)
            {
                if (j >= 0)
                {
                    if ((j - 3) % 5 == 0)
                    {
                        if (j/5 < 10)
                        {
                            cout << " 0";
                        }
                        else
                        {
                            cout << " ";
                        }
                        cout << j/5 << " ";
                    }
                }
                if (j % 5 == 0)
                {
                    cout << "|";
                }
            }
            if (j == -1)
            {
                    if (i % 2 == 1)
                    {
                        cout << " ";
                        if (i/2 < 10)
                        {
                            cout << "0";
                        }
                        cout << i / 2 << " ";
                    }
                    else if (i > -1)
                    {
                        cout << "----";
                    }
                    else
                    {
                        cout << "    ";
                    }
            }

            if (i == cellString_Row && (j == cellString_Col || j == cellString_Col + 1))
            {
                printf("M");
            }
            else if (i > -1 && j > -1)
            {
                cout << cellString[i][j];
            }
        }
        printf("\n");
    }
    printf("\n");
}

void Maze::PrintVisited(Coord mousePosition)
{
    printf("\n- - - - - - - - - - - - - - - -\n");
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i == mousePosition.GetRow() && j == mousePosition.GetCol())
            {
				// Print mouse position
                printf("+ ");
            }
            else if (cells[i][j].isVisited())
			{
				// Print a visited cell
                printf("* ");
            }
            else if (cells[i][j].isWall())
            {
				// Print a Wall
                printf("W ");
            }
            else
            {
				// Print unvisited/unexplored square
                printf("O ");
            }
        }
        printf("\n");
    }
    printf("- - - - - - - - - - - - - - - -\n");
}