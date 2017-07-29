#include <iostream>
#include "Maze.h"
#include "Mouse.h"
#include <thread>
#include <filesystem>

using namespace std;

int menu();
bool promptFloodFill();
void runMaze(string, bool);
void runAllMazes(bool);

// List of files to read
static string files[] = { "Maze-1.txt", "Maze-2.txt", "Maze-3.txt", "Maze-4.txt", "Maze-5.txt", "Maze-6.txt" };
// Number of files
static int numOfFiles = sizeof(files) / sizeof(files[0]);

int main()
{
    bool done = false;
    bool floodFill;
    do
    {
        int choice = menu();
        
        if (choice < numOfFiles + 2)
        {
            floodFill = promptFloodFill();
        }

        if (choice < numOfFiles + 1)
        {
            // Read a chosen maze
            runMaze(files[choice - 1], floodFill);
        }
        else if (choice == numOfFiles + 1)
        {
            // Read all mazes
            runAllMazes(floodFill);
        }
        else
        {
            // Exit
            done = true;
        }
        
    }
    while (!done);

    return 0;
}

/*
 * Prompts user to choose an action (Read maze, read all mazes, quit)
 */
int menu()
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

/*
 * Prompt user to specify if they'd like to view the Flood Fill Process
 */
bool promptFloodFill()
{
    cout << "View Flood Fill? (Y/N)" << endl;

    bool valid = false;
    char a;

    while (!valid)
    {
        cin >> a;
        cout << endl;
        if (a == 'y' || a == 'Y')
        {
            return true;
        }
        if (a == 'n' || a == 'N')
        {
            return false;
        }
    }

}

/*
 * Run a specified maze 
 */
void runMaze(string fileName, bool viewFloodFill)
{
    Coord start(15, 0);

    string pathToFile = "..\\Mazes\\" + fileName;
    Maze maze(pathToFile);
    Mouse mouse;

    bool solvable = false;

    // Preview maze to user
    maze.printMaze(start);
    cout << "\n" << fileName << "\n" << endl;
    system("pause");
    
    mouse.floodFill(maze, viewFloodFill);

    solvable = mouse.getMaze()->isFloodFilled();

    if (solvable)
    {
        printf("Flood Fill Complete!\n");
        if (viewFloodFill)
        {
            system("pause");
        }
        mouse.solveMaze();
    }
    else
    {
        printf("Flood Fill Fail :( \n");
    }

    system("pause");
}

/*
 * Run all mazes 
 */
void runAllMazes(bool viewFloodFill)
{
    for (int i = 0; i < numOfFiles; i++)
    {
        runMaze(files[i], viewFloodFill);
    }
}