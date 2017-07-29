#include <iostream>
#include "Maze.h"
#include "Mouse.h"
#include <thread>
#include <filesystem>

namespace fs = std::experimental::filesystem;

using namespace std;

int chooseFile();

void runMaze(string);

static string files[] = { "Maze-1.txt", "Maze-2.txt", "Maze-3.txt", "Maze-4.txt", "Maze-5.txt" };

static int numOfFiles = sizeof(files) / sizeof(files[0]);

int main()
{
    bool done = false;

    do
    {
        int choice = chooseFile();
        if (choice < numOfFiles + 1)
        {
            runMaze(files[choice - 1]);
        }
        else if (choice == numOfFiles + 1)
        {
            for (int i = 0; i < numOfFiles; i++)
            {
                runMaze(files[i]);
            }
        }
        else
        {
            done = true;
        }
        
    }
    while (!done);

    return 0;
}

int chooseFile()
{
    for (int i = 0; i < numOfFiles; i++)
    {
        cout << (i + 1) << ". " << files[i] << endl;
    }
    cout << (numOfFiles + 1) << ". Run All Files" << endl;
    cout << (numOfFiles + 2) << ". Quit" << endl;

    int choice;

    cin >> choice;

    return choice;
}

void runMaze(string fileName)
{
    Coord start(15, 0);

    Maze maze(fileName);
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


    mouse.solveMaze();

    system("pause");
}