#include "MGraph.h";

//通过静态数组创建图
//v为包含vertex值的数组，n为vertex的数量，e为edege的数量
MGraph::MGraph(int v[], int n, int e)
{
	//设置vertex的数量于edge的数量
	this->vertexNum = n;
	this->arcNum = e;

	//根据v[]里储存的数据，为vertex[]赋值
	for (int i = 0; i < this->vertexNum; i++)
	{
		this->vertex[i] = v[i];
	}

	//初始化matrix
	for (int i = 0; i < this->vertexNum; i++)
	{
		for (int j = 0; j < this->vertexNum; j++)
		{
			arc[i][j] = MY_INFINITY;
		}
	}
	//填写matrix，构造graph
	BuildGraph();

	//初始化visited
	cleanVisited();
}

//根据edge为matrix填上值，如果输入两个vertex的编号，则可以在这两个vertex之间增加一条edge，并在matrix上对应位置填入1.
void MGraph::BuildGraph()
{
	int vertex1, vertex2, weight;
	for (int i = 0; i < this->arcNum; i++)
	{
		cout << "请输入要添加邻边的两个vertex的编号，并输入权值：" << endl;
		cin >> vertex1 >> vertex2 >> weight;
		this->arc[vertex1][vertex2] = weight;
		this->arc[vertex2][vertex1] = weight;
	}

}

//展示graph的matrix
void MGraph::displayGraph()
{
	cout << "打印graph矩阵：" << endl;
	for (int i = 0; i < this->vertexNum; i++)
	{
		cout << "\t" << this->vertex[i];
	}
	cout << endl;
	for (int i = 0; i < this->vertexNum; i++)
	{
		cout << this->vertex[i] << "\t";
		for (int j = 0; j < this->vertexNum; j++)
		{
			cout << this->arc[i][j] << "\t";
		}
		cout << endl;
	}
}

void MGraph::DFSTraverse(int v)
{
	//初始化visited数组
	cleanVisited();

	//深度搜寻编号为v的顶点
	DFS(v);

	//循环整个visited数组，如果有还未visit的顶点，则以该顶点为起点继续DFS
	for (int i = 0; i < vertexNum; i++)
	{
		if ( visited[i] == false)
		{
			DFS(i);
		}
		
	}
}

void MGraph::DFS(int v)
{
	//输出找到的第一个节点，并将该节点的bool设置为true
	cout << vertex[v] << " ";
	visited[v] = true;

	//在矩阵中当前顶点的这一行中寻找与当前顶点相连的其他顶点
	for (int i = 0; i < vertexNum; i++)
	{
		//如果该顶点有相连的其他顶点（arc[v][i]==1）且还未visit过的顶点，则递归相邻顶点
		if (arc[v][i] == 1 && visited[i] == false)
		{
			DFS(i);
		}
	}
}

void MGraph::BFSTraverse(int v)
{
	//初始化visited数组
	cleanVisited();

	BFS(v);

	//循环整个visited数组，如果有还未visit的顶点，则以该顶点为起点继续BFS
	for (int i = 0; i < vertexNum; i++)
	{
		if (visited[i] == false)
			BFS(i);
	}
}

void MGraph::BFS(int v)
{
	//输出当前顶点，并将顶点push到queue里
	cout << vertex[v] << " ";
	visited[v] = true;
	myQueue.push(vertex[v]);

	//如果队列不为空则循环运行到队列空为止
	while (!myQueue.empty())
	{
		v = myQueue.front();//将队首的值（顶点的编号）传给v
		myQueue.pop();//pop队首的值

		//循环该顶点在矩阵中对应的行，找到与该顶点相连的其他顶点
		for (int i = 0; i < vertexNum; i++)
		{
			if (arc[v][i] == 1 && visited[i] == false)
			{
				myQueue.push(vertex[i]);
				cout << vertex[i] << " ";	
				visited[i] = true;
			}
		}
		
	}
}

void MGraph::cleanVisited()
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		visited[i] = false;
	}
}

/*prim算法：https://www.bilibili.com/video/BV1Ua4y1i7tf?from=articleDetail
shortEdge是一个包含了adjVex与lowCost的数组。该数组存储了vertex[]数组中所有的点到adjVex点的最短边长lowCost。
即：当adjVex是顶点0时，在vertex[]中的顶点0、1、2、3...n到0的最短距离是shortEdge[].lowCost*/
void MGraph::Prim(int start)
{
	int min;
	//初始化shortEdge,使adjVex的顶点是算法的起始点，而lowCost的值是所有其他顶点到起始点adjVex的距离,并且将start点放入集合U中（将lowCost设置为0）
	for (int i = 0; i < vertexNum; i++)
	{
		shortEdge[i].adjVex = start;
		shortEdge[i].lowCost = arc[start][i];
	}
	shortEdge[start].lowCost = 0;

	cout << "输出起点从V" << start << "开始的最小生成树：" << endl;
	for (int j = 0; j < vertexNum - 1; j++)
	{
		//找到距离起始顶点距离最短的顶点后，返回该顶点的序号给min，并将该顶点的lowCost设置为0，表示将该顶点放入集合U中
		min = getMinCost(shortEdge);
		outputPrim(min, shortEdge[min]);//传入最短距离顶点的编号min作为结束顶点，shortEdge[min].adjVex作为起始点，shortEdge[min].lowCost作为权值
		shortEdge[min].lowCost = 0;
		/*更新shortEdge表：将adjVex移动到下一个距离当前顶点最近的顶点，并在arc[]中检测该顶点到剩余顶点的距离，如果小于当前储存在shortEdge[]中的值，
		则更新shortEdge[]中的lowCost(权值)与adjVex(起点的编号)*/
		for (int k = 0; k < vertexNum; k++)
		{
			if (shortEdge[k].lowCost != 0 && shortEdge[k].lowCost > arc[min][k])
			{
				shortEdge[k].adjVex = min;
				shortEdge[k].lowCost = arc[min][k];
			}	
		}
	}
}

void MGraph::outputPrim(int endVertex, ShortEdgeArr myArr)
{
	cout << "（" << myArr.adjVex << ", " << endVertex << "）" << myArr.lowCost << endl;
}

//该函数返回shortEdge中的lowCost中最小的值。即找到当前顶点与最近的一个顶点之间的距离(不为0)
int MGraph::getMinCost(ShortEdgeArr myArr[])
{
	int min = MY_INFINITY;
	int index = 0;
	
	for (int i = 0; i < vertexNum; i++)
	{
		if (myArr[i].lowCost != 0 && myArr[i].lowCost < min)
		{
			min = myArr[i].lowCost;
			index = i;
		}
	}

	return index;
}

int main()
{
	
	int vertexNum, arcNum = 0;
	cout << "请输入vertex的数量：" << endl;
	cin >> vertexNum;
	int *myVertex = new int[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "请输入vertex的值：" << endl;
		cin >> myVertex[i];
	}
	cout << "请输入arc的数量：" << endl;
	cin >> arcNum;

	MGraph mg(myVertex, vertexNum, arcNum);
	mg.displayGraph();

	int start;
	cout << "准备开始深度搜索DFS，请输入起始顶点的编号：";
	cin >> start;
	mg.DFSTraverse(start);
	cout << endl;

	cout << "准备开始广度搜索BFS，请输入起始顶点的编号：";
	cin >> start;
	mg.BFSTraverse(start);
	cout << endl;

	cout << "准备开始寻找最小生成树，请输入起始顶点的编号：";
	cin >> start;
	mg.Prim(start);

	system("pause");
	return 0;
}