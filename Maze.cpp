#include "Maze.h"
#include "Stack.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>
using namespace std;

// reimplement maze creation with a function in a neat-er style if you want
Maze::Maze(int X , int Y) {
	M = X, N = Y;
	curX = 0, curY = 0;
	tryVec.resize(M, vector<Cell>());

	for (int i = 0; i < M; i++) {
		tryVec[i].resize(N, Cell());
	}
	// initializing a walled structure of cells, a Maze with walls around every cell
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			tryVec[i][j].coorX = i;
			tryVec[i][j].coorY = j;
		}
	}
	
	int c= rand() %3;
	numBroken = 0;
	string direction;

	curX = 0, curY = 0;

	if(M==1 && N==1) {
		return;
	}
	else if (M!=1 || N!=1) {
		c = rand() % 3;
		while (numBroken < M * N - 1) {
			if (existApplicableCell(curX, curX)) {
				c = RandomReturn();
				switch (c) {
				case 0: CellApplicable(tryVec[curX][curY], "left"); break;
				case 1: CellApplicable(tryVec[curX][curY], "right"); break;
				case 2: CellApplicable(tryVec[curX][curY], "up"); break;
				case 3: CellApplicable(tryVec[curX][curY], "down"); break;
				}
			}
			else {
				whenNoneApplicableCell(stringStack.topAndPop());
			}
		}
	}
}


// Checks if directed Cell can be added to stack, pushs if can be, returns false otherwise
bool Maze::CellApplicable(Cell& checkCell, const string & direction)
{
	if (direction == "up"&& checkCell.coorY+1<N) {
		if (StackCheckerDetail(checkCell.coorX,checkCell.coorY + 1)) {
			mainStack.push(tryVec[checkCell.coorX][checkCell.coorY + 1]);
			stringStack.push(direction);
			ProcessCells(checkCell.coorX, checkCell.coorY, direction);
			return true; }
	}
	else if (direction == "down" && checkCell.coorY -1 >=0) {
		if (StackCheckerDetail(checkCell.coorX,checkCell.coorY - 1)) {
			mainStack.push(tryVec[checkCell.coorX][checkCell.coorY - 1]);
			stringStack.push(direction);
			ProcessCells(checkCell.coorX, checkCell.coorY, direction);
			return true;
		}
	}
	else if (direction == "left" && checkCell.coorX -1>=0) {
		if (StackCheckerDetail(checkCell.coorX - 1,checkCell.coorY)) { 
			mainStack.push(tryVec[checkCell.coorX-1][checkCell.coorY ]);
			stringStack.push(direction);
			ProcessCells(checkCell.coorX, checkCell.coorY , direction);
			return true; 
		}
	}
	else if (direction == "right"&& checkCell.coorX +1 <M) {
		if (StackCheckerDetail(checkCell.coorX + 1,checkCell.coorY)) {
			mainStack.push(tryVec[checkCell.coorX+1][checkCell.coorY ]);
			stringStack.push(direction);
			ProcessCells(checkCell.coorX, checkCell.coorY , direction);
			return true;
		}
	}
	return false;
}

bool Maze::OnlyCellApplicable(Cell& checkCell, const string& direction)
{

	if (direction == "up" && checkCell.coorY + 1 < N) {
		if (StackCheckerDetail(checkCell.coorX, checkCell.coorY + 1)) {
			return true;
		}
	}
	else if (direction == "down" && checkCell.coorY - 1 >= 0) {
		if (StackCheckerDetail(checkCell.coorX, checkCell.coorY - 1)) {
		
			return true;
		}
	}
	else if (direction == "left" && checkCell.coorX - 1 >= 0) {
		if (StackCheckerDetail(checkCell.coorX - 1, checkCell.coorY)) {
		
			return true;
		}
	}
	else if (direction == "right" && checkCell.coorX + 1 < M) {
		if (StackCheckerDetail(checkCell.coorX + 1, checkCell.coorY)) {			
			return true;
		}
	}
	return false;
}

//takes coordinates for target cell, return true if target cell not visited, false otherwise
bool Maze::StackCheckerDetail(int corX, int corY) 
{
	Cell popped;
	while (!mainStack.isEmpty()) {
		popped = mainStack.topAndPop();
		sideStack.push(popped);
		if ((corX == popped.coorX && corY == popped.coorY)) {
			FillOriginalAgain();
			return false;
		}
	}
	FillOriginalAgain();
	return true;
}

void Maze::FillOriginalAgain()
{
	Cell popped;
	while (!sideStack.isEmpty()) {
		popped = sideStack.topAndPop();
		mainStack.push(popped);
	}
}

void Maze::PrintFunction(ofstream & toWrite)
{
	toWrite << M << " " << N << endl;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			toWrite << "x=" << i << " y=" << j << " l= " <<tryVec[i][j].l <<
				" r=" <<tryVec[i][j].r << " u=" << tryVec[i][j].u << " d=" << tryVec[i][j].d << endl;
		}
	}
	toWrite.close();
}

// returns count of ApplicableCells
int Maze::existApplicableCell(int corX, int corY)
{
	int count = 0;

	if (corX + 1 < M && StackCheckerDetail(corX + 1, corY))// right
		count++;
	else if (corX - 1 >= 0 && StackCheckerDetail(corX - 1, corY))//left
		count++;
	else if (corY - 1 >= 0 && StackCheckerDetail(corX, corY - 1))//down
		count++;
	else if (corY + 1 < N && StackCheckerDetail(corX, corY + 1))
		count++;
	return count;
}

// what to do when no applicable cells exists, call this func
void Maze::whenNoneApplicableCell(string prevDirection)
{
	if (prevDirection == "left") {
		curX++;
		return;
	}
	else if (prevDirection == "right") {
		curX--;
		return;
	}
	else if (prevDirection == "top") {
		curY--;
		return;
	}
	else if (prevDirection == "down") {
		curY++;
		return;
	}
}

// process both cells (wall stiuations) and change curX and curY
void Maze::ProcessCells(int cor1, int cor2, string direction)
{
	if (direction == "up") {
		tryVec[cor1][cor2].u = 0;
		tryVec[cor1][cor2+1].d = 0;
		curY++;
		numBroken++;
		stringStack.push(direction);
	}
	else if (direction == "down") {
		tryVec[cor1][cor2].d = 0;
		tryVec[cor1][cor2 - 1].u = 0;
		curY--;
		numBroken++;
		stringStack.push(direction);
	}
	else if (direction == "right") {
		tryVec[cor1][cor2].r = 0;
		tryVec[cor1+1][cor2 ].l = 0;
		curX++;
		numBroken++;
		stringStack.push(direction);
	}
	else if (direction == "left") {
		tryVec[cor1][cor2].l = 0;
		tryVec[cor1 - 1][cor2].r = 0;
		curX--;
		numBroken++;
		stringStack.push(direction);
	}
}

int Maze::RandomReturn()
{
	int t = existApplicableCell(curX, curY),  c;
	if (t == 4) {
		return (rand() % 3);
	}
	else if (t==3){
		if (!OnlyCellApplicable(tryVec[curX][curY], "left")) {
			return (rand() % 1 + 2);
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "right")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 0; 
			case 1: return 2;
			case 2: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "up")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 0;
			case 1: return 1;
			case 2: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "down")) {
			return (rand() % 2);
		}
		
	}
	else if (t == 2) {
		if (!OnlyCellApplicable(tryVec[curX][curY], "left") && !OnlyCellApplicable(tryVec[curX][curY], "right")) {
			return (rand() % 2 + 1);
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "left") && !OnlyCellApplicable(tryVec[curX][curY], "up")) {
			c = rand() % 1;
			switch (c) {
			case 0: return 1;
			case 1: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "left") && !OnlyCellApplicable(tryVec[curX][curY], "down")) {
			c = rand() % 1;
			switch (c) {
			case 0: return 1;
			case 1: return 2;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "right") && !OnlyCellApplicable(tryVec[curX][curY], "up")) {
			c = rand() % 1;
			switch (c) {
			case 0: return 0;
			case 1: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "right") && !OnlyCellApplicable(tryVec[curX][curY], "down")) {
			c = rand() % 1;
			switch (c) {
			case 0: return 1;
			case 1: return 2;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "up") && !OnlyCellApplicable(tryVec[curX][curY], "down")) {
			return (rand() % 1);
		}
	}
	else if (t == 1) {
		if (OnlyCellApplicable(tryVec[curX][curY], "left")) return 0;
		if (OnlyCellApplicable(tryVec[curX][curY], "right")) return 1;
		if (OnlyCellApplicable(tryVec[curX][curY], "up")) return 2;
		if (OnlyCellApplicable(tryVec[curX][curY], "down")) return 3;

	}
	t = 100;
	cout << "error: t=100"<< endl << endl ;
	assert(t!=100);
	return 100;
}



/// <summary>
///  path finding parth
/// </summary>

void Maze::PathFinding(ofstream & toWrite, int pEntryX, int pEntryY, int pOutX, int pOutY)
{
	entryX = pEntryX; entryY = pEntryY; outX = pOutX; outY = pOutY;

	curX = entryX; curY = entryY;
	pathStack1.push(tryVec[curX][curY]);


	



}


int Maze::RandomReturnPathfinding() {

}

// return num of applicable cells, to which algo can advance and whether it's the same as the reverse direciton
int Maze::existApplicableCellPathfinding(int corX, int corY)
{
	string prevDir;
	if (!stringStackPath.isEmpty()) {
		prevDir = stringStackPath.topAndPop();
		stringPoppedPath.push(prevDir);
	}

	return 0;
}

void Maze::whenNoneApplicableCellPathfinding(string prevDirection)
{
}

void Maze::ProcessCellsPathfinding(int cor1, int cor2, string direction)
{
}
