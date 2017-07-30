#include "Mouse.h"
#include "Coord.h"
#include <stack>
#include <chrono>
#include <thread>

/*
 * Default Constructor
 */
Mouse::Mouse() : mBoardSize(16), mPosition(15, 0)
{

}

/*
 * Constructor that preemptively grants knowledge of a Maze to the Mouse given a text file
 */
Mouse::Mouse(string fileName) : mBoardSize(16), mPosition(15, 0), completeMaze(fileName)
{
    
}

/*
 * Gets the Mouse's position
 */
const Coord Mouse::getPosition()
{
    return mPosition;
}

/*
 * Gets the Mouse's knowledge of the Maze
 */
Maze* Mouse::getMaze()
{
    return & completeMaze;
}

/*
 * Sets the Mouse's Position to a given location
 */
void Mouse::setPosition(unsigned char x, unsigned char y) {

    Coord position(x, y);

    if (isInBounds(position)) {
        mPosition.SetRow(x);
        mPosition.SetCol(y);
    }
}

/*
 * Sets the Mouse's Position to a given location
 */
void Mouse::setPosition(Coord coord)
{
    setPosition(coord.GetRow(), coord.GetCol());
}

/*
 * Resets the Mouse's Position to the default start location
 */
void Mouse::resetPosition()
{
    Coord start(15, 0);
    setPosition(start);
}

/*
 * Checks if Mouse is in bounds according to the board
 */
bool Mouse::isInBounds(Coord position) {
    if (position.GetRow() >= 0 && position.GetRow() < mBoardSize && position.GetCol() >= 0 && position.GetCol() < mBoardSize) {
        return true;
    }
    return false;
}

/*
 * Checks if Mouse is in bounds according to the board
 */
bool Mouse::isInBounds(unsigned char x, unsigned char y)
{
    if (x >= 0 && x < mBoardSize && y >= 0 && y < mBoardSize) {
        return true;
    }
    return false;
}

/*
 * Checks if Mouse is adjacent to a set of Coordinates (Does not consider wall collision)
 */
bool Mouse::isNextTo(Coord cell)
{
	if (cell.GetRow() == mPosition.GetRow())
	{
		if (cell.GetCol() == (mPosition.GetCol() + 1) || cell.GetCol() == (mPosition.GetCol() - 1))
		{
			return true;
		}
	}

	if (cell.GetCol() == mPosition.GetCol())
	{
		if (cell.GetRow() == (mPosition.GetRow() + 1) || cell.GetRow() == (mPosition.GetRow() - 1))
		{
			return true;
		}
	}

    return false;
}

/*
 * Checks if Mouse is Accessible to a cell
 */
bool Mouse::isAccessibleTo(Cell cell)
{
    if (!isNextTo(cell.getCoordinates()))
    {
        return false;
    }

    if (mPosition.isAbove(cell.getCoordinates()))
    {
        return !cell.hasNorthWall();
    }
    if (mPosition.isBelow(cell.getCoordinates()))
    {
        return !cell.hasSouthWall();
    }
    if (mPosition.isLeftOf(cell.getCoordinates()))
    {
        return !cell.hasWestWall();
    }
    if (mPosition.isRightOf(cell.getCoordinates()))
    {
        return !cell.hasEastWall();
    }
}

/*
 * Returns true if Mouse is in the goal of the maze, returns false otherwise
 */
bool Mouse::isInGoal()
{
    if (mPosition.GetRow() == 7 || mPosition.GetRow() == 8)
    {
        if (mPosition.GetCol() == 7 || mPosition.GetCol() == 8)
        {
            return true;
        }
    }
    return false;
}

/*
 * Moves Mouse up
 */
void Mouse::moveUp() {
    mPosition.MoveUp();
}

/*
 * Moves Mouse down
 */
void Mouse::moveDown() {
    mPosition.MoveDown();
}

/*
 * Moves Mouse left
 */
void Mouse::moveLeft() {
    mPosition.MoveLeft();
}

/*
 * Moves Mouse right
 */
void Mouse::moveRight() {
    mPosition.MoveRight();
}

/*
 * Adjusts Mouse to an adjacent set of Coordinates
 */
void Mouse::moveToCell(Coord cell)
{
	if (cell.GetRow() == mPosition.GetRow())
	{
		if (cell.GetCol() < mPosition.GetCol())
		{
			moveLeft();
			return;
		}
		if (cell.GetCol() > mPosition.GetCol())
		{
			moveRight();
			return;
		}
	}
   
	if (cell.GetCol() == mPosition.GetCol())
	{
		if (cell.GetRow() < mPosition.GetRow())
		{
			moveUp();
			return;
		}
		if (cell.GetRow() > mPosition.GetRow())
		{
			moveDown();
			return;
		}
	}
    
}

/*
 * Reads the cell in the Mouse's current position
 */
void Mouse::readCell()
{
    if (completeMaze.getCell(mPosition).hasNorthWall())
    {
        completeMaze.markCellNorthWall(mPosition);
    }
    if (completeMaze.getCell(mPosition).hasSouthWall())
    {
        completeMaze.markCellSouthWall(mPosition);
    }
    if (completeMaze.getCell(mPosition).hasEastWall())
    {
        completeMaze.markCellEastWall(mPosition);
    }
    if (completeMaze.getCell(mPosition).hasWestWall())
    {
        completeMaze.markCellWestWall(mPosition);
    }
}

/*
 * Reads cell given a set of Coordinates (Must integrate with Hardware)
 */
void Mouse::readCell(Coord cellCoord)
{
	// Hardware code to check if cell is wall


}

/*
 * Reads cell given a set of Coordinates and information about the cell
 */
void Mouse::readCell(Coord cellCoord, Cell cell)
{
    if (cellCoord.GetRow() == mPosition.GetRow())
    {
        if (cellCoord.GetCol() < mPosition.GetCol())
        {
            completeMaze.getCell(cellCoord).setEastWall(cell.hasEastWall());
            completeMaze.getCell(mPosition).setWestWall(cell.hasEastWall());
            if (cell.hasEastWall())
            {
                completeMaze.markCellEastWall(cellCoord);
            }
        }
        else if (cellCoord.GetCol() > mPosition.GetCol())
        {
            completeMaze.getCell(cellCoord).setWestWall(cell.hasWestWall());
            completeMaze.getCell(mPosition).setEastWall(cell.hasWestWall());
            if (cell.hasWestWall())
            {
                completeMaze.markCellWestWall(cellCoord);
            }
        }
    }
    else if (cellCoord.GetCol() == mPosition.GetCol())
    {
        if (cellCoord.GetRow() < mPosition.GetRow())
        {
            completeMaze.getCell(cellCoord).setSouthWall(cell.hasSouthWall());
            completeMaze.getCell(mPosition).setNorthWall(cell.hasSouthWall());
            if (cell.hasSouthWall())
            {
                completeMaze.markCellSouthWall(cellCoord);
            }
        }
        else if (cellCoord.GetRow() > mPosition.GetRow())
        {
            completeMaze.getCell(cellCoord).setNorthWall(cell.hasNorthWall());
            completeMaze.getCell(mPosition).setSouthWall(cell.hasNorthWall());
            if (cell.hasNorthWall())
            {
                completeMaze.markCellNorthWall(cellCoord);
            }
        }
    }
}

/*
 * Marks cell in the Mouse's current position as 'visited'
 */
void Mouse::visitCell()
{
	completeMaze.getCell(mPosition).setVisited(true);
    completeMaze.markCellVisited(mPosition);
}

/*
 * Initiates Flood Fill process for Mouse
 */
void Mouse::floodFill()
{
	
}

/*
 * Initiates Flood Fill process for Mouse given information about a Maze
 */
void Mouse::floodFill(Maze maze)
{
    // Speeds up process by removing observation of Flood Fill
    floodFill(maze, false);
}

/*
* Initiates Flood Fill process for Mouse given information about a Maze
*/
void Mouse::floodFill(Maze maze, bool viewFloodFill)
{
    // Sets refresh rate for Flood Fill Process
    const long DELAY = 5;

    Coord current, start(15, 0);
    Cell currentCell;

    bool trackSolution = true;

    // Used to mark the next unexplored cells for the Mouse to check
    stack <Coord> cellsToCheck;
    // Used to keep track of previous cells visited by the Mouse (For Backtracking)
    stack <Coord> previousCells;

    // Push the starting position of mouse as the first cell for the Mouse to check
    cellsToCheck.push(start);

    do
    {
        // Flood Fill Complete
        if (cellsToCheck.empty())
        {
            return;
        }
        // Stop updating solution stack if goal is found
        if (isInGoal())
        {
            trackSolution = false;
        }

        // Get the next cell to explore
        current = cellsToCheck.top();
        cellsToCheck.pop();

        currentCell = completeMaze.getCell(current);

        // While loop corrects position of Mouse until it's on the next explored Point
        while (current != getPosition())
        {
            // Move Mouse towards next explored point if adjacent and accessible

            if (isAccessibleTo(currentCell))
            {
                moveToCell(current);
            }
            else
            {
                // Backtrack mouse to the last cell it visited
                Coord prev = previousCells.top();
                moveToCell(prev);
                // If previous cell doesn't lead to another opening, drop it
                if (!prev.isNextTo(current))
                {
                    previousCells.pop();
                    if (trackSolution)
                    {
                        // Remove useless cell if backtracking
                        solution.pop();
                    }
                }
                // If previous cell is inaccessible to next target cell, drop it
                if (prev.isNextTo(current) && !completeMaze.getCell(prev).isAccessibleTo(currentCell))
                {
                    previousCells.pop();
                    if (trackSolution)
                    {
                        // Remove useless cell if backtracking
                        solution.pop();
                    }
                }
            }
            if (viewFloodFill)
            {
                completeMaze.printMaze(mPosition);
                this_thread::sleep_for(chrono::milliseconds(DELAY));
            }
            // system("pause"); // This is used for debugging
        }

        // Mark cell as visited
        visitCell();

        stack <Coord> neighbors = getNeighbors(maze);

        while (!neighbors.empty())
        {
            // Add neighbors as next cells to check
            Coord next = neighbors.top();
            cellsToCheck.push(neighbors.top());
            neighbors.pop();
        }

        // Mark current position as last cell visited by Mouse
        previousCells.push(current);

        // Add the current cell to the solution stack
        if (trackSolution)
        {
            solution.push(current);
        }

        if (viewFloodFill)
        {
            completeMaze.printMaze(mPosition);
            this_thread::sleep_for(chrono::milliseconds(DELAY));
        }
        // system("pause"); // This is used for debugging
    }
    while (!cellsToCheck.empty());
}

/*
 * Runs the Solution Course through the Mouse 
 */
void Mouse::solveMaze()
{
    long DELAY = 5;

    stack <Coord> solutionCopy = solution;
    stack <Coord> course;

    while (!solutionCopy.empty())
    {
        Coord next = solutionCopy.top();
        course.push(next);
        solutionCopy.pop();
    }

    setPosition(15, 0);

    completeMaze.resetMaze();

    while (!course.empty())
    {
        Coord next = course.top();
        course.pop();
        moveToCell(next);
        readCell();
        visitCell();
        completeMaze.printMaze(mPosition);
    }

}

/*
 * Gets the neighboring coordinates of the Mouse and returns viable cells to visit
 */
stack <Coord> Mouse::getNeighbors()
{
	stack <Coord> neighbors;
    
    // Hardware Code

	return neighbors;
}

/*
* Gets the neighboring coordinates of the Mouse and returns viable cells to visit
*/
stack <Coord> Mouse::getNeighbors(Maze maze)
{
	// Acquire neighbors
	stack <Coord> validNeighbors;
	stack <Coord> neighbors;

	Coord up(mPosition.GetRow() - 1, mPosition.GetCol());
	Coord down(mPosition.GetRow() + 1, mPosition.GetCol());
	Coord left(mPosition.GetRow(), mPosition.GetCol() - 1);
	Coord right(mPosition.GetRow(), mPosition.GetCol() + 1);

	neighbors.push(down);
	neighbors.push(left);
	neighbors.push(right);
	neighbors.push(up);

    
	while (!neighbors.empty())
	{
		Coord currentNeighbor = neighbors.top();
		neighbors.pop();
		if (currentNeighbor.isInBounds() && !completeMaze.getCell(currentNeighbor).isVisited())
		{
			Cell cell = maze.getCell(currentNeighbor);
			readCell(currentNeighbor, cell);

			if (mPosition.isAbove(currentNeighbor))
			{
			    if (!cell.hasNorthWall())
			    {
			        validNeighbors.push(currentNeighbor);
			    }
			}
            if (mPosition.isBelow(currentNeighbor))
            {
                if (!cell.hasSouthWall())
                {
                    validNeighbors.push(currentNeighbor);
                }
            }
            if (mPosition.isLeftOf(currentNeighbor))
            {
                if (!cell.hasWestWall())
                {
                    validNeighbors.push(currentNeighbor);
                }
            }
            if (mPosition.isRightOf(currentNeighbor))
            {
                if (!cell.hasEastWall())
                {
                    validNeighbors.push(currentNeighbor);
                }
            }
		}
	}
	return validNeighbors;
}