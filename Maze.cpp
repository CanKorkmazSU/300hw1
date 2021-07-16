#include "Maze.h"
#include "Stack.h"
#include <vector>
#include <string>
using namespace std;

Maze::Maze(int X, int Y) {
	M = X, N = Y;
	curX = 0, curY = 0;
	tryVec.resize(M, vector<Cell>());

	for (int i = 0; i < M; i++) {
		tryVec[i].resize(N, Cell());
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			tryVec[i][j].coorX = i;
			tryVec[i][j].coorY = j;
		}
	}

}

bool Maze::CellApplicable(Cell& checkCell, string direction)
{
	if (direction == "up"&& checkCell.coorY+1<N) {
		if (StackCheckerDetail(tryVec[checkCell.coorX][checkCell.coorY + 1])) {
			AddToStackMain(tryVec[checkCell.coorX][checkCell.coorY + 1]);
			ProcessCell(checkCell.coorX, checkCell.coorY+1, direction);
			return true; }
	}
	else if (direction == "down" && checkCell.coorY -1 >=0) {
		if (StackCheckerDetail(tryVec[checkCell.coorX][checkCell.coorY - 1])) {
			AddToStackMain(tryVec[checkCell.coorX][checkCell.coorY - 1]);
			ProcessCell(checkCell.coorX, checkCell.coorY - 1, direction);
			return true;
		}
	}
	else if (direction == "left" && checkCell.coorX -1>=0) {
		if (StackCheckerDetail(tryVec[checkCell.coorX - 1][checkCell.coorY])) { 
			AddToStackMain(tryVec[checkCell.coorX-1][checkCell.coorY ]);
			ProcessCell(checkCell.coorX-1, checkCell.coorY , direction);
			return true; }
	}
	else if (direction == "right"&& checkCell.coorX +1 <M) {
		if (StackCheckerDetail(tryVec[checkCell.coorX + 1][checkCell.coorY])) {
			AddToStackMain(tryVec[checkCell.coorX+1][checkCell.coorY ]);
			ProcessCell(checkCell.coorX+1, checkCell.coorY , direction);
			return true;
		}
	}

	return false;
}

void Maze::AddToStackMain(Cell& checkedCell)
{
}

bool Maze::StackCheckerDetail(Cell& toBeChecked) // return true if target cell not visited, false otherwise
{
	Cell popped;
	while (!mainStack.isEmpty()) {
		popped = mainStack.topAndPop();
		sideStack.push(popped);
		if (!(toBeChecked.coorX == popped.coorX && toBeChecked.coorY == popped.coorY)) {
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
}

void Maze::ProcessCell(int cor1, int cor2, string direction)
{
	if (direction == "up") {
		tryVec[cor1][cor2].u = 0;
		tryVec[cor1][cor2+1].d = 0;

	}
	else if (direction == "down") {
		tryVec[cor1][cor2].d = 0;
		tryVec[cor1][cor2 - 1].u = 0;
	}
	else if (direction == "right") {
		tryVec[cor1][cor2].r = 0;
		tryVec[cor1+1][cor2 ].l = 0;

	}
	else if (direction == "left") {
		tryVec[cor1][cor2].l = 0;
		tryVec[cor1 - 1][cor2].r = 0;
	}

}




