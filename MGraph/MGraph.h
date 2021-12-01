#pragma once
#include <iostream>
#include <queue>
using namespace std;

const int MAX_VERTEX = 10;

class MGraph
{
private:
	int vertex[MAX_VERTEX];
	int arc[MAX_VERTEX][MAX_VERTEX];
	int vertexNum, arcNum;
	bool visited[MAX_VERTEX];
	queue<int> myQueue;

	void BuildGraph();

	void DFS(int v);

	void BFS(int v);

	void cleanVisited();

public:
	MGraph(int v[], int n, int e);

	void displayGraph();

	void DFSTraverse(int v);

	void BFSTraverse(int v);
};