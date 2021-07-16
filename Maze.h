#pragma once
#include <vector>
#include "Stack.h"
#include "Stack.cpp"

using namespace std;


struct Cell {
	int a, b, c, d;
	int coorX, coorY;
	Cell() :a(1), b(1), c(1), d(1), coorX(0), coorY(0) {}
	Cell(int cor1, int cor2):a(1), b(1), c(1), d(1) ,coorX(cor1), coorY(cor2){}
};


class Maze
{
public:
	Maze(int X, int Y);
	
	bool CellApplicable(Cell & checkCell);
	void AddToStackMain(Cell & checkedCell);

	//Maze & MazeGenerator(int x, int y);

private:
	int K, M, N, entryX, entryY;
	
	int curX, curY;

	vector<vector<Cell>>  tryVec;
	Stack<Cell> mainStack, sideStack;
};
