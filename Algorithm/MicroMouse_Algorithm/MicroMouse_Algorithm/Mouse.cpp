#include "Mouse.h"
#include "Coord.h"
#include <stack>
#include <chrono>
#include <thread>


Mouse::Mouse() : mBoardSize(16), mPosition(15, 0)
{

}

Mouse::Mouse(string fileName) : mBoardSize(16), mPosition(15, 0), completeMaze(fileName)
{
    
}

Mouse::Mouse(unsigned char boardSize) : mBoardSize(boardSize), mPosition{ { 15 },{ 0 } } {

}

const Coord Mouse::getPosition()
{
    return mPosition;
}

Maze* Mouse::getMaze()
{
    return & completeMaze;
}


void Mouse::setPosition(unsigned char x, unsigned char y) {

    Coord position(x, y);

    if (isInBounds(position)) {
        mPosition.SetRow(x);
        mPosition.SetCol(y);
    }
}

bool Mouse::isInBounds(Coord position) {
    if (position.GetRow() >= 0 && position.GetRow() < mBoardSize && position.GetCol() >= 0 && position.GetCol() < mBoardSize) {
        return true;
    }
    return false;
}

bool Mouse::isInBounds(unsigned char x, unsigned char y)
{
    if (x >= 0 && x < mBoardSize && y >= 0 && y < mBoardSize) {
        return true;
    }
    return false;
}

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

bool Mouse::isAccessibleTo(Cell cell)
{
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

void Mouse::moveUp() {
	mPosition.MoveUp();
}

void Mouse::moveDown() {
	mPosition.MoveDown();
}

void Mouse::moveLeft() {
	mPosition.MoveLeft();
}

void Mouse::moveRight() {
	mPosition.MoveRight();
}

void Mouse::readCell(Coord cellCoord)
{
	// Hardware code to check if cell is wall


}

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
                completeMaze.markCellSouthWall(mPosition);
            }
        }
        else if (cellCoord.GetRow() > mPosition.GetRow())
        {
            completeMaze.getCell(cellCoord).setNorthWall(cell.hasNorthWall());
            completeMaze.getCell(mPosition).setSouthWall(cell.hasNorthWall());
            if (cell.hasNorthWall())
            {
                completeMaze.markCellNorthWall(mPosition);
            }
        }
    }
}

void Mouse::visitCell()
{
	completeMaze.getCell(mPosition).setVisited(true);
    completeMaze.markCellVisited(mPosition);
}


void Mouse::floodFill()
{
	
}

void Mouse::floodFill(Maze maze)
{
	long DELAY = 5;

	Coord current, start(15, 0);
	Cell currentCell;

	stack <Coord> cellsToCheck;
	stack <Coord> previousCells;

	cellsToCheck.push(start);

	do
	{
		// Flood Fill Complete
		if (cellsToCheck.empty())
		{
			return;
		}

		// Get the next cell to explore
		current = cellsToCheck.top();
		cellsToCheck.pop();

		currentCell = completeMaze.getCell(current);

		// While loop corrects position of Mouse until it's on the next explored Point
		while (current != getPosition())
		{
			// Move Mouse towards next explored point if adjacent

            if (isNextTo(current) && isAccessibleTo(currentCell))
            {
                moveToCell(current);
            }
			else
			{
				// Backtrack mouse to the last cell it visited
				Coord prev = previousCells.top();
				moveToCell(prev);
				if (!prev.isNextTo(current))
				{
					previousCells.pop();
				}
                if (prev.isNextTo(current) && !completeMaze.getCell(prev).isAccessibleTo(currentCell))
                {
                    previousCells.pop();
                }
			}
			completeMaze.printMaze(mPosition);
            this_thread::sleep_for(chrono::milliseconds(DELAY));
			//system("pause");
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

        completeMaze.printMaze(mPosition);
        this_thread::sleep_for(chrono::milliseconds(DELAY));
		//system("pause");
	} while (!cellsToCheck.empty());
}

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

void Mouse::solveMaze()
{
    
}


stack <Coord> Mouse::getNeighbors()
{
	// Hardware code
	stack <Coord> neighbors;

	return neighbors;
}

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