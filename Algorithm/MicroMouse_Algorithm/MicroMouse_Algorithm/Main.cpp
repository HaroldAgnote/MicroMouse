#include <iostream>
#include "Maze.h"

using namespace std;

int main() {
    Maze maze;
    maze.Initialize();
    maze.PrintDistance();

    cout << endl << endl << endl;

    system("pause");
    return 0;

}