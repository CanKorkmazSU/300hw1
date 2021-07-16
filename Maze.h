#pragma once
#include <vector>
#include "Stack.h"
#include "Stack.cpp"
#include <string>

using namespace std;


struct Cell {
	int l, r, u, d;
	int coorX, coorY;
	Cell() :l(1), r(1), u(1), d(1), coorX(0), coorY(0) {}
	Cell(int cor1, int cor2):l(1), r(1), u(1), d(1) ,coorX(cor1), coorY(cor2){}
};


class Maze
{
public:
	Maze(int X, int Y);

	bool CellApplicable(Cell& checkCell, string direction);
	
	void AddToStackMain(Cell & checkedCell);
	bool StackCheckerDetail(Cell & toBeChecked);
	void FillOriginalAgain();
	void PrintFunction();

	void ProcessCell(int cor1, int cor2, string direction);

private:
	int K, M, N, entryX, entryY;
	
	int curX, curY;

	vector<vector<Cell>>  tryVec;
	Stack<Cell> mainStack, sideStack;
};


// 