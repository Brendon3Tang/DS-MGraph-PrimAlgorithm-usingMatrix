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
			arc[i][j] = 0;
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
	int vertex1, vertex2;
	for (int i = 0; i < this->arcNum; i++)
	{
		cout << "请输入要添加邻边的两个vertex的编号：" << endl;
		cin >> vertex1 >> vertex2;
		this->arc[vertex1][vertex2] = 1;
		this->arc[vertex2][vertex1] = 1;
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

	system("pause");
	return 0;
}