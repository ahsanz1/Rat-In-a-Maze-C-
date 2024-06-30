#include"Array.h"
#include"Stack.h"
#include<conio.h>
#include<cstdlib>
#include<ctime>
using namespace std;

void mazeMenu()
{
	cout << "\t\t\t\t\t\tRAT IN A MAZE" << endl;
	cout << "\t\t\t\t\t\tPRESS P TO START TRAVERSING" << endl;
	cout << "\t\t\t\t\t\tPress G to Generate a New Maze" << endl;
	cout << "\t\t\t\t\t\tPress D to Double the Maze" << endl;
	cout << "\t\t\t\t\t\tPress E to EXIT!" << endl;
}

class Maze
{
private:
	Array<char> mazeArray;
	Stack<char> stackArray;

public:
	Maze(int, int);
	void generateMaze();
	void printMaze();
	void generateHurdels();
	void play();
	void doubleMaze();
	int getValidPosition(int, int);
	void insert(int, char);
	void insertRatnCheese();

};

Maze::Maze(int x, int y) : mazeArray(x, y) , stackArray(x*y + x*y)
{
}

void Maze::insert(int offset, char value)
{
	mazeArray.insert(offset, value);
}

void Maze::doubleMaze()
{
	mazeArray.extend();                  //double the maze
	generateMaze();                    //generate maze acc to new dimensions(placing boundries of 0's)
	generateHurdels();

	int offset = mazeArray.CalculateOffset(1, 1);     //to place R at beginning of new maze

	mazeArray.GetArray()[offset] = 'R';
	offset = mazeArray.CalculateOffset(mazeArray.GetRows() - 2, mazeArray.GetCols() - 2);
	mazeArray.GetArray()[offset] = 'C';      //to place C at the end of new maze
}

int Maze::getValidPosition(int x, int y)
{
	int vPosition;

	if (mazeArray.CalculateOffset(x, y + 1) != '0')
		return vPosition = mazeArray.CalculateOffset(x, y + 1);

	if (mazeArray.CalculateOffset(x, y - 1) != '0')
		return vPosition = mazeArray.CalculateOffset(x, y - 1);

	if (mazeArray.CalculateOffset(x - 1, y) != '0')
		return vPosition = mazeArray.CalculateOffset(x - 1, y);

	if (mazeArray.CalculateOffset(x + 1, y) != '0')
		return vPosition = mazeArray.CalculateOffset(x + 1, y);

	/*else
		return -99;*/
}

void Maze::play()
{
	char ch;
	mazeMenu();
	printMaze();

	ch = _getch();

	while (ch != 'e')
	{
		system("cls");
		if (ch == 'g')
		{
			this->generateMaze();
			insertRatnCheese();
			generateHurdels();
		}

		else if (ch == 'd')
		{
			this->doubleMaze();
		}
		
		else if (ch == 'p')
		{
			int newRow, newCol;
			char *mazePtr = mazeArray.GetArray();
			mazePtr[mazeArray.CalculateOffset(1, 1)] = 'R';
			stackArray.push(mazeArray.CalculateOffset(1, 1));

			while (stackArray.stackTop() != mazeArray.CalculateOffset(mazeArray.GetRows() - 2, mazeArray.GetCols() - 2))
			{

				newRow = mazeArray.getRowNo(stackArray.stackTop());
				newCol = mazeArray.getColNo(stackArray.stackTop());

				if (stackArray.stackTop() != '0')
				{
					stackArray.push(getValidPosition(newRow, newCol));
				}

			} 

			Maze solMaze(mazeArray.GetRows() - 1, mazeArray.GetCols() - 1);
			solMaze.generateMaze();

			while (!stackArray.isEmpty())
			{
				solMaze.insert(stackArray.stackTop(), '.');
				stackArray.pop();
			}

			solMaze.printMaze();

			
		}


		mazeMenu();
		printMaze();
		ch = _getch();
	}
}

void Maze::generateHurdels()
{
	int hRow, hCol, offset;
	for (int i = 0; i < mazeArray.GetMaxSize() / 8; i++)     //greater the divisor, lesser the hurdles
	{
		hRow = rand() % (mazeArray.GetCols());          //calculating row and col where hurdle has to be placed
		hCol = rand() % (mazeArray.GetRows());       //then calculating appropriate index in linear array
		offset = mazeArray.CalculateOffset(hRow, hCol);

		if (offset > 0 && offset < mazeArray.GetMaxSize())
			mazeArray.GetArray()[offset] = '0';         //offset to place hurdle should be between 0 and maxSize of linear array
	}
}

void Maze::generateMaze()
{
	char* mArray = mazeArray.GetArray();

	for (int i = 0; i < mazeArray.GetCols(); i++)
	{
		mArray[i] = '0';
	}

	int offset = mazeArray.CalculateOffset(1, 1);
	int colCheck = 0;
	int rightBoundryCheck = mazeArray.GetRows();           //check to place 0's on the right
														   //offset-1 cuz offset calculated was 1 more than required
	for (int i = offset - 1; i < mazeArray.GetMaxSize() - mazeArray.GetCols(); i += mazeArray.GetCols())
	{
		for (int j = i; colCheck < mazeArray.GetCols(); j++, colCheck++)  //colCheck cuz a row has to be printed col times
		{

			if (j % mazeArray.GetRows() == 0)
				mArray[j] = '0';                   //to place 0's at the start of each row
			else if (j % mazeArray.GetRows() + 1 == rightBoundryCheck)
				mArray[j] = '0';                    //to place 0's at the end of each row
			else
				mArray[j] = ' ';                    //spaces in between 0's boundries of maze, for a time being
		}
		colCheck = 0;
	}

	for (int i = mazeArray.GetMaxSize() - mazeArray.GetCols(); i < mazeArray.GetMaxSize(); i++)
	{
		mArray[i] = '0';
	}                                                      //where Cheese is placed
}

void Maze::insertRatnCheese()
{
	int offset = mazeArray.CalculateOffset(1, 1);
	mazeArray.GetArray()[offset] = 'R';
	offset = mazeArray.CalculateOffset(mazeArray.GetRows() - 2, mazeArray.GetCols() - 2); //bottom right corner of maze
	mazeArray.GetArray()[offset] = 'C';
}

void Maze::printMaze()
{
	cout << mazeArray;
}
