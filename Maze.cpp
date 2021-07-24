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
	
	int c = rand()%2;
	numBroken = 0;
	string direction;

	curX = 0, curY = 0;
	mainStack.push(tryVec[0][0]);
	
	if(M==1 && N==1) {
		return;
	}
	else if (M!=1 || N!=1) {
		while (numBroken < M * N -1) {
			if (curX == 0 && curY == 0) {
				switch (c) {
				case 0:  mainStack.topOfStack->element.u=0; mainStack.push(tryVec[curX][curY+1]); mainStack.topOfStack->element.d = 0;
					curY++; stringStack.push("up");
					tryVec[0][0].u = 0; tryVec[0][1].d = 0; numBroken++;  break;
				case 1: mainStack.topOfStack->element.r = 0; mainStack.push(tryVec[curX+1][curY]); mainStack.topOfStack->element.l = 0; curX++; stringStack.push("right");
					tryVec[0][0].r = 0; tryVec[1][0].l = 0; numBroken++; break;
				}
			}
			else if (existApplicableCell(curX, curY)) {
				c = RandomReturn();
				switch (c) {
				case 0: CellApplicable(tryVec[curX][curY], "left"); break;
				case 1: CellApplicable(tryVec[curX][curY], "right"); break;
				case 2: CellApplicable(tryVec[curX][curY], "up"); break;
				case 3: CellApplicable(tryVec[curX][curY], "down"); break;
				}
			}
			else {
				whenNoneApplicableCell(stringStack.top());
			}
		}
	}
}


// Checks if directed Cell can be added to stack, pushs if can be, returns false otherwise
bool Maze::CellApplicable(Cell& checkCell, const string & direction)
{
	if (direction == "up"&& checkCell.coorY+1<N) {
		if (StackCheckerDetail(checkCell.coorX,checkCell.coorY + 1)) {
			mainStack.topOfStack->element.u = 0;
			mainStack.push(tryVec[checkCell.coorX][checkCell.coorY + 1]);
			mainStack.topOfStack->element.d = 0;
			stringStack.push(direction);
			ProcessCells(checkCell.coorX, checkCell.coorY, direction);
			return true; }
	}
	else if (direction == "down" && checkCell.coorY -1 >=0) {
		if (StackCheckerDetail(checkCell.coorX,checkCell.coorY - 1)) {
			mainStack.topOfStack->element.d = 0;
			mainStack.push(tryVec[checkCell.coorX][checkCell.coorY - 1]);
			mainStack.topOfStack->element.u = 0;
			stringStack.push(direction);
			ProcessCells(checkCell.coorX, checkCell.coorY, direction);
			return true;
		}
	}
	else if (direction == "left" && checkCell.coorX -1>=0) {
		if (StackCheckerDetail(checkCell.coorX - 1,checkCell.coorY)) { 
			mainStack.topOfStack->element.l = 0;
			mainStack.push(tryVec[checkCell.coorX-1][checkCell.coorY ]);
			mainStack.topOfStack->element.r = 0;
			stringStack.push(direction);
			ProcessCells(checkCell.coorX, checkCell.coorY , direction);
			return true; 
		}
	}
	else if (direction == "right"&& checkCell.coorX +1 <M) {
		if (StackCheckerDetail(checkCell.coorX + 1,checkCell.coorY)) {
			mainStack.topOfStack->element.r = 0;
			mainStack.push(tryVec[checkCell.coorX+1][checkCell.coorY ]);
			mainStack.topOfStack->element.l = 0;
			stringStack.push(direction);
			ProcessCells(checkCell.coorX, checkCell.coorY , direction);
			return true;
		}
	}
	return false;
}

// doesnt alter any private value, only checks if the prev cell and direction is applicable
bool Maze::OnlyCellApplicable(Cell& checkCell, const string& direction)
{
	if (direction == "up" && checkCell.coorY + 1 < N) {
		if (StackCheckerDetail(checkCell.coorX, checkCell.coorY + 1)) {
			return true;
		}
		else return false;
	}
	else if (direction == "down" && checkCell.coorY - 1 >= 0) {
		if (StackCheckerDetail(checkCell.coorX, checkCell.coorY - 1)) {
		
			return true;
		}
		else return false;

	}
	else if (direction == "left" && checkCell.coorX - 1 >= 0) {
		if (StackCheckerDetail(checkCell.coorX - 1, checkCell.coorY)) {
			return true;
		}
		else return false;

	}
	else if (direction == "right" && checkCell.coorX + 1 < M) {
		if (StackCheckerDetail(checkCell.coorX + 1, checkCell.coorY)) {			
			return true;
		}
		else return false;
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
	if (corX - 1 >= 0 && StackCheckerDetail(corX - 1, corY))//left
		count++;
	if (corY - 1 >= 0 && StackCheckerDetail(corX, corY - 1))//down
		count++;
	if (corY + 1 < N && StackCheckerDetail(corX, corY + 1))
		count++;
	return count;
}

// what to do when no applicable cells exists, call this func
void Maze::whenNoneApplicableCell(string prevDirection)
{
	stringStack.pop();
	if (prevDirection == "left") {
		curX++;
		return;
	}
	else if (prevDirection == "right") {
		curX--;
		return;
	}
	else if (prevDirection == "up") {
		curY--;
		return;
	}
	else if (prevDirection == "down") {
		curY++;
		return;
	}
}

// process both cells(current and target approved) (wall stiuations) and change curX and curY
void Maze::ProcessCells(int cor1, int cor2, string direction)
{
	if (direction == "up") {
		tryVec[cor1][cor2].u = 0;
		tryVec[cor1][cor2+1].d = 0;
		curY++;
		numBroken++;
	}
	else if (direction == "down") {
		tryVec[cor1][cor2].d = 0;
		tryVec[cor1][cor2 - 1].u = 0;
		curY--;
		numBroken++;
	}
	else if (direction == "right") {
		tryVec[cor1][cor2].r = 0;
		tryVec[cor1+1][cor2 ].l = 0;
		curX++;
		numBroken++;
	}
	else if (direction == "left") {
		tryVec[cor1][cor2].l = 0;
		tryVec[cor1 - 1][cor2].r = 0;
		curX--;
		numBroken++;
	}
}
//random return generator in compliance with existing cell situation
int Maze::RandomReturn()
{
	int t = existApplicableCell(curX, curY),  c;
	if (t == 4) {
		return (rand() % 4);
	}
	else if (t==3){
		if (!OnlyCellApplicable(tryVec[curX][curY], "left")) {
			c = rand() % 3;
			switch (c) {
			case 0: return 1;
			case 1: return 2;
			case 2: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "right")) {
			c = rand() % 3;
			switch (c) {
			case 0: return 0; 
			case 1: return 2;
			case 2: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "up")) {
			c = rand() % 3;
			switch (c) {
			case 0: return 0;
			case 1: return 1;
			case 2: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "down")) {
			return (rand() % 3);
		}
		
	}
	else if (t == 2) {
		if (!OnlyCellApplicable(tryVec[curX][curY], "left") && !OnlyCellApplicable(tryVec[curX][curY], "right")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 2;
			case 1: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "left") && !OnlyCellApplicable(tryVec[curX][curY], "up")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 1; 
			case 1: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "left") && !OnlyCellApplicable(tryVec[curX][curY], "down")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 1;
			case 1: return 2;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "right") && !OnlyCellApplicable(tryVec[curX][curY], "up")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 0;
			case 1: return 3;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "right") && !OnlyCellApplicable(tryVec[curX][curY], "down")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 0;
			case 1: return 2;
			}
		}
		else if (!OnlyCellApplicable(tryVec[curX][curY], "up") && !OnlyCellApplicable(tryVec[curX][curY], "down")) {
			return (rand() % 2);
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
///  path finding part
/// </summary>

void Maze::PathFinding(ofstream & toWrite, int pEntryX, int pEntryY, int pOutX, int pOutY)
{
	entryX = pEntryX; entryY = pEntryY; outX = pOutX; outY = pOutY;

	curX = entryX; curY = entryY;
	mainPathStack.push(tryVec[curX][curY]);
	int c;
	while (curX != outX || curY != outY) {
		if (existApplicableCellPathfinding(curX, curY)) {
			c = RandomReturnPathfinding();
			switch (c) {
			case 0: 
				if (OnlyCellApplicablePathfinding(tryVec[curX][curY], "left")) {
				mainPathStack.push(tryVec[--curX][curY]);
				stringStackPath.push("left");
				}
				break;
			case 1:
				if (OnlyCellApplicablePathfinding(tryVec[curX][curY], "right")) {
				mainPathStack.push(tryVec[++curX][curY]);
				stringStackPath.push("right");
				}
				break;
			case 2: if (OnlyCellApplicablePathfinding(tryVec[curX][curY], "up")) {
				mainPathStack.push(tryVec[curX][++curY]);
				stringStackPath.push("up"); 
				}
				break;
			case 3: if (OnlyCellApplicablePathfinding(tryVec[curX][curY], "down")) {
				mainPathStack.push(tryVec[curX][--curY]);
				stringStackPath.push("down"); 
				}
				break;
			}
		}
		else whenNoneApplicableCellPathfinding();
	}
	PrintFunctionPathfinding(toWrite);
	toWrite.close();
}

// implementation completed but check again
int Maze::RandomReturnPathfinding() {

	int t = existApplicableCellPathfinding(curX, curY), c;
	
	if(t==3){
		if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "left")) {
			c = rand() % 3;
			switch (c) {
			case 0: return 1;
			case 1: return 2;
			case 2: return 3;
			}
		}
		else if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "right")) {
			c = rand() % 3;
			switch (c) {
			case 0: return 0;
			case 1: return 2;
			case 2: return 3;
			}
		}
		else if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "up")) {
			c = rand() % 3;
			switch (c) {
			case 0: return 0;
			case 1: return 1;
			case 2: return 3;
			}
		}
		else if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "down")) {
			return (rand() % 3);
		}
	}
	else if (t == 2) {
		if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "left") && !OnlyCellApplicablePathfinding(tryVec[curX][curY], "right")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 2;
			case 1: return 3;
			}
		}
		else if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "left") && !OnlyCellApplicablePathfinding(tryVec[curX][curY], "up")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 1;
			case 1: return 3;
			}
		}
		else if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "left") && !OnlyCellApplicablePathfinding(tryVec[curX][curY], "down")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 1;
			case 1: return 2;
			}
		}
		else if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "right") && !OnlyCellApplicablePathfinding(tryVec[curX][curY], "up")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 0;
			case 1: return 3;
			}
		}
		else if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "right") && !OnlyCellApplicablePathfinding(tryVec[curX][curY], "down")) {
			c = rand() % 2;
			switch (c) {
			case 0: return 1;
			case 1: return 2;
			}
		}
		else if (!OnlyCellApplicablePathfinding(tryVec[curX][curY], "up") && !OnlyCellApplicablePathfinding(tryVec[curX][curY], "down")) {
			return (rand() % 2);
		}
	}
	else if (t == 1) {
		if (OnlyCellApplicablePathfinding(tryVec[curX][curY], "left")) return 0; // 0 for left
		if (OnlyCellApplicablePathfinding(tryVec[curX][curY], "right")) return 1;
		if (OnlyCellApplicablePathfinding(tryVec[curX][curY], "up")) return 2;
		if (OnlyCellApplicablePathfinding(tryVec[curX][curY], "down")) return 3;// 3 for down

	}
	t = INT_MAX;
	//cout << "Error: t=100" << endl << endl;
	assert("Error t=100 \n\n", t != INT_MAX);
	return INT_MAX;
}

// return num of applicable cells, to which algo can advance in consideration with sameness as the reverse direciton
// implementation completed but check again,
// update: re-implemented, needs testing
int Maze::existApplicableCellPathfinding(int corX, int corY)
{
	int count = 0;
	if (corX + 1 < M && tryVec[corX][corY].r ==0 && StackCheckerDetailPathfinding(corX + 1, corY))
		count++;
	if (corX - 1 >= 0 && tryVec[corX][corY].l == 0 && StackCheckerDetailPathfinding(corX - 1, corY))
		count++;
	if (corY - 1 >= 0 && tryVec[corX][corY].d == 0 && StackCheckerDetailPathfinding(corX, corY - 1))
		count++;
	if (corY + 1 < N && tryVec[corX][corY].u == 0 && StackCheckerDetailPathfinding(corX, corY + 1))
		count++;

	return count;
}

// call if you diverge into wrong path
// implementation complete 
void Maze::whenNoneApplicableCellPathfinding()
{
	string prev= stringStackPath.topAndPop();;
	if (prev == "left") curX++;
	else if (prev == "right") curX--;
	else if (prev == "up") curY--;
	else if (prev == "down") curY++;
}

void Maze::PrintFunctionPathfinding(ofstream& toWrite)
{
	if (mainPathStack.isEmpty())
		return;
	else {
		int x, y;
		x = mainPathStack.topOfStack->element.coorX, y = mainPathStack.topOfStack->element.coorY;
		mainPathStack.pop();
		PrintFunctionPathfinding(toWrite);
		toWrite << x << " " << y << endl;
	}

}

// implementation failed, re-implement
// update: re-implemented, prolly working nwo
bool Maze::OnlyCellApplicablePathfinding(Cell& checkCell, const string& direction)
{
	if (direction == "up" &&  checkCell.coorY + 1 < N ) {
		if (tryVec[curX][curY].u == 0 &&  StackCheckerDetailPathfinding(checkCell.coorX, checkCell.coorY + 1)) {
			return true;
		}
		else return false;
	}
	else if (direction == "down" && checkCell.coorY - 1 >= 0 ) {
		if (tryVec[curX][curY].d == 0 && StackCheckerDetailPathfinding(checkCell.coorX, checkCell.coorY - 1)) {
			return true;
		}
		else return false;
	}
	else if (direction == "left" && checkCell.coorX - 1 >= 0 ) {
		if (tryVec[curX][curY].l == 0 && StackCheckerDetailPathfinding(checkCell.coorX - 1, checkCell.coorY)) {
			return true;
		}
		else return false;
	}
	else if (direction == "right" && checkCell.coorX + 1 < M ) {
		if (tryVec[curX][curY].r == 0 && StackCheckerDetailPathfinding(checkCell.coorX + 1, checkCell.coorY)) {
			return true;
		}
		else return false;
	}
	return false;
}

//implementation complete
bool Maze::StackCheckerDetailPathfinding(int corX, int corY)
{
	Cell popped;
	while (!mainPathStack.isEmpty()) {
		popped = mainPathStack.topAndPop();
		sidePathStack.push(popped);
		if ((corX == popped.coorX && corY == popped.coorY)) {
			FillOriginalAgainPathfinding();
			return false;
		}
	}
	FillOriginalAgainPathfinding();
	return true;
}

// implementation complete
void Maze::FillOriginalAgainPathfinding()
{
	Cell popped;
	while (!sidePathStack.isEmpty()) {
		popped = sidePathStack.topAndPop();
		mainPathStack.push(popped);
	}
}