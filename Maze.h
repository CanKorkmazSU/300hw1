#pragma once

#include <vector>
#include "Stack.h"
#include <string>
#include <random>
#include <fstream>

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
	Maze(int X=3, int Y=3);

	bool CellApplicable(Cell& checkCell, const string& direction);
	bool OnlyCellApplicable(Cell& checkCell, const string& direction); // does nothing but return a bool

	
	//void AddToStackMain(Cell & checkedCell);
	bool StackCheckerDetail(int corX, int corY);
	void FillOriginalAgain();

	void PrintFunction(ofstream & toWrite);
	void PathFinding(ofstream & toWrite, int eX, int eY, int oX, int oY);

	//check whether any wall to break or not, return number of breakable wall
	int existApplicableCell(int corX, int corY);

	// call when no applicable cells exist to go, dont forget to update curX and curY, also process stacks
	void whenNoneApplicableCell(string prevDirection);

	void ProcessCells(int cor1, int cor2, string direction);
	int RandomReturn();



	// path finding functions and implementation
	int RandomReturnPathfinding();
	int existApplicableCellPathfinding(int corX, int corY);
	void whenNoneApplicableCellPathfinding();
	void PrintFunctionPathfinding(ofstream& toWrite);
	bool StackCheckerDetailPathfinding(int corX, int corY);
	void FillOriginalAgainPathfinding();
	bool OnlyCellApplicablePathfinding(Cell& checkCell, const string& direction);


private:
	//K-> number of mazes, M: Xcoordintte(columns), N: Ycoordinate(rows)
	int M , N, entryX, entryY, outX, outY;
	
	int curX , curY  , numBroken /*,pCurX, pCurY*/;

	vector<vector<Cell>>  tryVec; // holds cells
	Stack<Cell> mainStack, sideStack;
	Stack<string> stringStack, stringPopped;// for directions

	Stack<string> stringStackPath, stringPoppedPath;// for directions of second part
	Stack<Cell> pathStack1, pathStack2;

};


// to do *****
//
//implement the existApplicableCell and later path finding
//for existApplicableCell, you need prolly. to more functions; random

