#include <iostream>
#include "Stack.h"
#include "Maze.h"
#include "Maze.cpp"
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


}

