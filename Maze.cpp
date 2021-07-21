#include "Maze.h"
#include "Stack.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>
using namespace std;


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
		while (numBroken < 1) {
			c = rand() % 3;
			if (c == 0 ) {
				CellApplicable(tryVec[curX][curY], "left");
				continue;
			}
			else if (c == 1) {
				CellApplicable(tryVec[curX][curY], "up");
				continue;

			}
			else if (c == 2) {
				CellApplicable(tryVec[curX][curY], "right");
				continue;

			}
			else if (c = 3) {
				CellApplicable(tryVec[curX][curY], "down");
				continue;

			}
		}
		while (numBroken != M * N - 1) {
			c = rand() % 3;
			if (c == 0 && existApplicableCell(curX, curY)) {
				CellApplicable(tryVec[curX][curY], "left");
				continue;
			}
			else if (c == 1 && existApplicableCell(curX, curY)) {
				CellApplicable(tryVec[curX][curY], "up");
				continue;

			}
			else if (c == 2 && existApplicableCell(curX, curY)) {
				CellApplicable(tryVec[curX][curY], "right");
				continue;
			}
			else if (c = 3&& existApplicableCell(curX, curY)) {
				CellApplicable(tryVec[curX][curY], "down");
				continue;
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

//takes coordinates for target cell
bool Maze::StackCheckerDetail(int corX, int corY) // return true if target cell not visited, false otherwise
{
	Cell popped;
	while (!mainStack.isEmpty()) {
		popped = mainStack.topAndPop();
		sideStack.push(popped);
		if (!(corX == popped.coorX && corY == popped.coorY)) {
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

void Maze::PrintFunction()
{
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cout << "x= " << i << " y=" << j;;
		}
	}
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




