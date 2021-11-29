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

public:
	MGraph(char v[], int n, int e);

	void BuildGraph();

	void displayGraph();

	void DFSTraverse(int v);

	void BFSTraverse(int v);
};