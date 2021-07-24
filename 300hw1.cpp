#include <iostream>
#include "Stack.h"
#include "Maze.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
	int K, M, N, inX, inY, outX,outY, mazeID;
	cout << "Enter K, M, N" << endl;
	cin >> K >> M >> N;
	vector<Maze> mazeVec(K, Maze(M,N)); // to store all Mazes


	ofstream ofStreamPrint, ofStreamPath;

	for (int i = 0; i < K; i++) {
		ofStreamPrint.open(("Maze_" + to_string(i) + ".txt").c_str());
		mazeVec[i].PrintFunction(ofStreamPrint);
	}
	cout << "Enter a maze ID between 1 to "<< K << " inclusive to find a path: ";
	cin >> mazeID;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> inX >> inY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin>> outX >> outY;

	string outPathString = "Maze_" + to_string(mazeID) + "_path_" + to_string(inX) + "_"
		+ to_string(inY) + "_" + to_string(outX) + "_" + to_string(outY) + ".txt";

	ofStreamPath.open(outPathString.c_str());
	mazeVec[mazeID-1].PathFinding(ofStreamPath, inX, inY, outX, outY);
}