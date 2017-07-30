#include <StackArray.h>
#include <MultiStepper.h>
#include <AccelStepper.h>
#define HALFSTEP 8

// initialize the stepper library on pins 8 through 11:
#define motor1Pin1 4
#define motor1Pin2 5
#define motor1Pin3 6
#define motor1Pin4 7
#define motor2Pin1 43
#define motor2Pin2 45
#define motor2Pin3 47
#define motor2Pin4 49
#define ECHO1 3		// Right Sensors
#define TRIG1 2
#define ECHO2 9		// Left Sensors
#define TRIG2 8
#define ECHO3 23	// Front Sensors
#define TRIG3 22

void readSensors();
void readFront();
void readLeft();
void readRight();
long duration1, distance1, duration2, distance2, duration3, distance3;

const long WALL_DISTANCE_THRESHOLD = 100;

//Initialize with pin sequence using AccelStepper
AccelStepper stepper1(HALFSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepper2(HALFSTEP, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);

class Coord
{
	/*
	* The row of the Coordinate (x)
	*/
	unsigned char row;

	/*
	* The columns of the Coordinate (y)
	*/
	unsigned char col;

public:
	/*
	* Default Constructor of Set of Coordinates which sets Coordinates to start of Maze
	*/
	Coord::Coord()
	{
		row = 15;
		col = 0;
	}

	/*
	* Constructor that sets Coordinates to a gien row and column
	*/
	Coord::Coord(unsigned char row, unsigned char col) : row(row), col(col)
	{

	}

	/*
	* Destructor
	*/
	Coord::~Coord()
	{

	}

	/*
	* Returns the row of the Coordinate
	*/
	unsigned char Coord::GetRow() const
	{
		return row;
	}

	/*
	* Returns the column of the Coordinate
	*/
	unsigned char Coord::GetCol() const
	{
		return col;
	}

	/*
	* Modifies the row of the Coordinate
	*/
	void Coord::SetRow(unsigned char row) {
		this->row = row;
	}

	/*
	* Modifies the column of the Coordinate
	*/
	void Coord::SetCol(unsigned char col) {
		this->col = col;
	}

	/*
	* Indicates if the Coordinate is within the bounds of the Maze
	*/
	bool Coord::isInBounds()
	{
		// Board dimension is 16 x 16
		return row >= 0 && row < 16 && col >= 0 && col < 16;
	}

	/*
	* Indicates if the Coordinate is adjacent to another given set of Coordinates
	*/
	bool Coord::isNextTo(Coord coord)
	{
		if (row == coord.row)
		{
			return (col == (coord.col + 1)) || (col == (coord.col - 1));
		}
		if (col == coord.col)
		{
			return (row == (coord.row + 1)) || (row == (coord.row - 1));
		}
		return false;
	}

	/*
	* Indicates if the Coordinate is above another set of Coordinates
	*/
	bool Coord::isAbove(Coord coord)
	{
		return row == (coord.row - 1);
	}

	/*
	* Indicates if the Coordinate is below another set of Coordinates
	*/
	bool Coord::isBelow(Coord coord)
	{
		return row == (coord.row + 1);
	}

	/*
	* Indicates if the Coordinate is to the Left of another set of Coordinates
	*/
	bool Coord::isLeftOf(Coord coord)
	{
		return col == (coord.col - 1);
	}

	/*
	* Indicates if the Coordinate is to the Right of another set of Coordinates
	*/
	bool Coord::isRightOf(Coord coord)
	{
		return col == (coord.col + 1);

	}

	/*
	* Adjusts the Coordinates up one row
	*/
	void Coord::MoveUp() {
		row -= 1;
	}

	/*
	* Adjusts the Coordinates down one row
	*/
	void Coord::MoveDown() {
		row += 1;
	}

	/*
	* Adjusts the Coordinates left one column
	*/
	void Coord::MoveLeft() {
		col -= 1;
	}

	/*
	* Adjusts the Coordinates right one column
	*/
	void Coord::MoveRight() {
		col += 1;
	}

	/*
	* Overloaded Operator that tests if the Coordinate is equal to another set of Coordinates
	*/
	bool Coord::operator==(const Coord & coord) const
	{
		return (row == coord.row && col == coord.col);
	}

	/*
	* Overloaded Operator that test if the Coordinate is not equal to another set of Coordinates
	*/
	bool Coord::operator!=(const Coord & coord) const
	{
		return !(row == coord.row && col == coord.col);
	}
};

class Cell
{
private:
	/*
	* Indicator representing if the Cell has been visited
	*/
	bool mVisited;

	/*
	* Indicator representing if the Cell has a North Wall
	*/
	bool mNorthWall;

	/*
	* Indicator representing if the Cell has a South Wall
	*/
	bool mSouthWall;

	/*
	* Indicator representing if the Cell has an East Wall
	*/
	bool mEastWall;

	/*
	* Indicator representing if the Cell has a West Wall
	*/
	bool mWestWall;

	/*
	* The Coordinates of where the Cell Resides
	*/
	Coord cellCoord;

	/*
	* Distance of this Cell to the Center of the Maze
	*/
	unsigned char mDistance;

public:
	/*
	* Default Constructor of Cell that sets all indicators to False
	*/
	Cell::Cell()
	{
		mVisited = false;
		mNorthWall = false;
		mSouthWall = false;
		mWestWall = false;
		mEastWall = false;
	}

	/*
	* Constructor of Cell that sets its Coordinates and all indicators to False
	*/
	Cell::Cell(Coord coord)
	{
		cellCoord = coord;
		mVisited = false;
		mNorthWall = false;
		mSouthWall = false;
		mWestWall = false;
		mEastWall = false;
	}

	/*
	* Returns the state of visitation of the Cell
	*/
	bool Cell::isVisited() const
	{
		return mVisited;
	}

	/*
	* Returns whether the Cell has a North Wall or not
	*/
	bool Cell::hasNorthWall()
	{
		return mNorthWall;
	}

	/*
	* Returns whether the Cell has a South Wall or not
	*/
	bool Cell::hasSouthWall()
	{
		return mSouthWall;
	}
	/*
	* Returns whether the Cell has a East Wall or not
	*/
	bool Cell::hasEastWall()
	{
		return mEastWall;
	}
	/*
	* Returns whether the Cell has a West Wall or not
	*/
	bool Cell::hasWestWall()
	{
		return mWestWall;
	}

	/*
	* Returns the set of Coordinates of the Cell
	*/
	Coord Cell::getCoordinates()
	{
		return cellCoord;
	}

	/*
	* Returns the distance of the Cell to the Center
	*/
	unsigned char Cell::getDistance()
	{
		return mDistance;
	}

	/*
	* Modifies the status of the Cell's visitation
	*/
	void Cell::setVisited(bool isVisited)
	{
		mVisited = isVisited;
	}

	/*
	* Modifies the status of the Cell's North Wall
	*/
	void Cell::setNorthWall(bool boolean)
	{
		mNorthWall = boolean;
	}

	/*
	* Modifies the status of the Cell's South Wall
	*/
	void Cell::setSouthWall(bool boolean)
	{
		mSouthWall = boolean;
	}

	/*
	* Modifies the status of the Cell's East Wall
	*/
	void Cell::setEastWall(bool boolean)
	{
		mEastWall = boolean;
	}

	/*
	* Modifies the status of the Cell's West Wall
	*/
	void Cell::setWestWall(bool boolean)
	{
		mWestWall = boolean;
	}

	/*
	* Modifies the Cell's coordinates given a set of Coordinates
	*/
	void Cell::setCoordinates(Coord coord)
	{
		cellCoord = coord;
	}

	/*
	* Modifies the Cell's Distance to the Center
	*/
	void Cell::setDistance(unsigned char distance)
	{
		mDistance = distance;
	}

	/*
	* Checks if a given Cell is Accessible from the current Cell
	*/
	bool Cell::isAccessibleTo(Cell cell)
	{
		if (cellCoord.isAbove(cell.cellCoord))
		{
			return !cell.hasNorthWall();
		}
		if (cellCoord.isBelow(cell.cellCoord))
		{
			return !cell.hasSouthWall();
		}
		if (cellCoord.isLeftOf(cell.cellCoord))
		{
			return !cell.hasWestWall();
		}
		if (cellCoord.isRightOf(cell.cellCoord))
		{
			return !cell.hasEastWall();
		}
		return false;
	}
};

class Maze
{
private:
	/*
	* 16 x 16 grid of the Maze
	*/
	Cell cells[16][16];

public:
	/*
	* Create empty Maze
	*/
	Maze::Maze()
	{
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

	/*
	* Destructor
	*/
	Maze::~Maze()
	{

	}

	/*
	* Get a Cell given a set of Coordinates
	*/
	Cell & Maze::getCell(Coord cellCoord)
	{
		return cells[cellCoord.GetRow()][cellCoord.GetCol()];
	}

	/*
	* Returns true if all Cells in the Maze have been explored
	*/
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
};

class Mouse
{
private:

	/*
	* Representation of a mouse in lieu of the real thing.
	*/
	Maze completeMaze;

	/*
	* Coordinates from the goal of the maze to the starting position
	*/
	StackArray <Coord> solution;

	/*
	* Size of the board
	*/
	unsigned char mBoardSize;

	/*
	* Mouse's position
	*/
	Coord mPosition;

public:
	/*
	* Default Constructor
	*/
	Mouse::Mouse() : mBoardSize(16), mPosition(15, 0)
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
		return &completeMaze;
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
	void Mouse::moveUp()
	{
		mPosition.MoveUp();
		stepper1.move(50000);
		stepper2.move(50000);

		while (stepper1.distanceToGo() != 0)
		{
			stepper1.runSpeedToPosition();
			stepper2.runSpeedToPosition();
		}
		
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
	* Reads cell given a set of Coordinates (Must integrate with Hardware)
	*/
	void Mouse::readCell(Coord cellCoord)
	{
		// Hardware code to check if cell is wall
		if (mPosition.isAbove(cellCoord))
		{

		}
		else if (mPosition.isBelow(cellCoord))
		{
			
		}
		else if (mPosition.isLeftOf(cellCoord))
		{

		}
		else if (mPosition.isRightOf(cellCoord))
		{

		}

	}

	/*
	* Marks cell in the Mouse's current position as 'visited'
	*/
	void Mouse::visitCell()
	{
		completeMaze.getCell(mPosition).setVisited(true);
	}

	/*
	* Initiates Flood Fill process for Mouse
	*/
	void Mouse::floodFill()
	{
		Coord current, start(15, 0);
		Cell currentCell;

		bool trackSolution = true;

		// Used to mark the next unexplored cells for the Mouse to check
		StackArray <Coord> cellsToCheck;
		// Used to keep track of previous cells visited by the Mouse (For Backtracking)
		StackArray <Coord> previousCells;

		// Push the starting position of mouse as the first cell for the Mouse to check
		cellsToCheck.push(start);

		do
		{
			// Flood Fill Complete
			if (cellsToCheck.isEmpty())
			{
				return;
			}
			// Stop updating solution stack if goal is found
			if (isInGoal())
			{
				trackSolution = false;
			}

			// Get the next cell to explore
			current = cellsToCheck.peek();
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
					Coord prev = previousCells.peek();
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
			}

			// Mark cell as visited
			visitCell();

			StackArray <Coord> neighbors = getNeighbors();

			while (!neighbors.isEmpty())
			{
				// Add neighbors as next cells to check
				Coord next = neighbors.peek();
				cellsToCheck.push(next);
				neighbors.pop();
			}

			// Mark current position as last cell visited by Mouse
			previousCells.push(current);

			// Add the current cell to the solution stack
			if (trackSolution)
			{
				solution.push(current);
			}

		} while (!cellsToCheck.isEmpty());
	}

	/*
	* Runs the Solution Course through the Mouse
	*/
	void Mouse::solveMaze()
	{
		StackArray <Coord> solutionCopy = solution;
		StackArray <Coord> course;

		while (!solutionCopy.isEmpty())
		{
			Coord next = solutionCopy.peek();
			course.push(next);
			solutionCopy.pop();
		}

		setPosition(15, 0);

		while (!course.isEmpty())
		{
			Coord next = course.peek();
			course.pop();
			moveToCell(next);
			visitCell();
		}

	}

	/*
	* Gets the neighboring coordinates of the Mouse and returns viable cells to visit
	*/
	StackArray <Coord> Mouse::getNeighbors()
	{
		StackArray <Coord> neighbors;

		Coord front(mPosition.GetRow() - 1, mPosition.GetCol());
		Coord left(mPosition.GetRow(), mPosition.GetCol() - 1);
		Coord right(mPosition.GetRow(), mPosition.GetCol() + 1);

		readFront();

		if (distance3 > WALL_DISTANCE_THRESHOLD)
		{
			neighbors.push(front);
		}
		else
		{
			completeMaze.getCell(front).setSouthWall(true);
			completeMaze.getCell(mPosition).setNorthWall(true);
		}
		
		readLeft();

		if (distance2 > WALL_DISTANCE_THRESHOLD)
		{
			neighbors.push(left);
		}
		else
		{
			completeMaze.getCell(left).setEastWall(true);
			completeMaze.getCell(mPosition).setWestWall(true);
		}

		readRight();

		if (distance1 > WALL_DISTANCE_THRESHOLD)
		{
			neighbors.push(right);
		}
		else
		{
			completeMaze.getCell(right).setWestWall(true);
			completeMaze.getCell(mPosition).setEastWall(true);
		}

		return neighbors;
	}
};

// Initialize Mouse
Mouse mouse;



void setup()
{
	pinMode(ECHO1, INPUT);
	pinMode(TRIG1, OUTPUT);
	pinMode(ECHO2, INPUT);
	pinMode(TRIG2, OUTPUT);
	pinMode(ECHO3, INPUT);
	pinMode(TRIG3, OUTPUT);
	stepper1.setAcceleration(1500);
	stepper1.setMaxSpeed(100000.0);
	stepper1.setSpeed(5000.0);
	stepper2.setAcceleration(1500);
	stepper2.setMaxSpeed(100000.0);
	stepper2.setSpeed(5000.0);

	// mouse.floodFill();
}

void loop()
{
	stepper1.setAcceleration(1500);
	stepper1.setMaxSpeed(100000.0);
	stepper1.setSpeed(100000.0);
	stepper2.setAcceleration(1500);
	stepper2.setMaxSpeed(100000.0);
	stepper2.setSpeed(100000.0);

	Serial.print("S1 - Speed: ");
	Serial.println(stepper1.speed());
	Serial.print("S2 - Speed: ");
	Serial.println(stepper2.speed());	
	
	stepper1.runSpeed();
	stepper2.runSpeed();
	// mouse.solveMaze();
}

void readSensors()
{
	
}

void readFront()
{
	digitalWrite(TRIG3, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG3, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG3, LOW);
	duration3 = pulseIn(ECHO3, HIGH);
	distance3 = duration3 / 29.1;
}

void readLeft()
{
	digitalWrite(TRIG2, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG2, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG2, LOW);
	duration2 = pulseIn(ECHO2, HIGH);
	distance2 = duration2 / 29.1;
}

void readRight()
{
	digitalWrite(TRIG1, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG1, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG1, LOW);
	duration1 = pulseIn(ECHO1, HIGH);
	distance1 = duration1 / 29.1;
}