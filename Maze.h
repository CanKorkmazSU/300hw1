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
	
	//void AddToStackMain(Cell & checkedCell);
	bool StackCheckerDetail(int corX, int corY);
	void FillOriginalAgain();

	void PrintFunction();

	//check whether any wall to break or not
	int existApplicableCell(int corX, int corY);

	// call when no applicable cells exist to go
	void whenNoneApplicableCell();

	void ProcessCells(int cor1, int cor2, string direction);

private:
	//K-> number of mazes, M: Xcoordintte(columns), N: Ycoordinate(rows)
	int K, M , N, entryX, entryY;
	
	int curX, curY;

	vector<vector<Cell>>  tryVec;
	Stack<Cell> mainStack, sideStack;
	Stack<string> stringStack;
};


// to do *****
//
//implement the existApplicableCell and later path finding
//for existApplicableCell, you need prolly. to more functions; random

