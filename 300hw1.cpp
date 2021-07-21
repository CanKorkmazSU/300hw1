#include <iostream>
#include "Stack.h"
#include "Maze.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;



int main()
{
	int K, M, N;
	cout << "enter K,M,N" << endl;
	cin >> K >> M >> N;
	vector<Maze> mazeVec(K);

	for (int i = 0; i < K; i++) {
		mazeVec[i]= Maze(M,N);
	}

	ofstream myOfStream;

	for (int i = 0; i < K; i++) {
		myOfStream.open(("Maze_" + to_string(i) + ".txt").c_str());
		mazeVec[i].PrintFunction();
	}


}

