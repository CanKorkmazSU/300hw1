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
	vector<Maze> mazeVec; // to store all Mazes

	for (int i = 0; i < K; i++) {
		mazeVec[i]= Maze(M,N);
	}

	ofstream ofStreamPrint, ofStreamPath;

	for (int i = 0; i < K; i++) {
		ofStreamPrint.open(("Maze_" + to_string(i) + ".txt").c_str());
		mazeVec[i].PrintFunction(ofStreamPrint);
	}
	cout << "Enter a maze ID between 1 to "<< to_string(K) << "inclusive to find a path: ";
	cin >> mazeID;
	cout << "enter in and out: ";
	cin >> inX >> inY >> outX >> outY;

	string outPathString = "Maze_" + to_string(mazeID) + "_path_" + to_string(inX) + "_"
		+ to_string(inY) + "_" + to_string(outX) + "_" + to_string(outY) + ".txt";

	ofStreamPath.open(outPathString.c_str());
	mazeVec[mazeID-1].PathFinding(ofStreamPath);

}

