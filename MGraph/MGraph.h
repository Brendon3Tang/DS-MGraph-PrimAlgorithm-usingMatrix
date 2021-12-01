#pragma once
#include <iostream>
using namespace std;

const int MAX_VERTEX = 10;

class MGraph
{
private:
	char vertex[MAX_VERTEX];
	int arc[MAX_VERTEX][MAX_VERTEX];
	int vertexNum, arcNum;
	bool visited[MAX_VERTEX];

	void BuildGraph();

	void DFS(int v);

	void cleanVisited();

public:
	MGraph(char v[], int n, int e);

	void displayGraph();

	void DFSTraverse(int v);

	void BFSTraverse(int v);
};