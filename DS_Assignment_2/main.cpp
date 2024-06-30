//#include<iostream>
#include"Maze.h"
using namespace std;

void main()
{
	srand(time(NULL));
	int rows, cols;

	cout << "Enter Number of Rows and Columns of Maze: " << endl;
	cin >> rows >> cols;

	Maze MazeObj(rows, cols);
	MazeObj.generateMaze();

	MazeObj.play();
	
	system("pause");
}
