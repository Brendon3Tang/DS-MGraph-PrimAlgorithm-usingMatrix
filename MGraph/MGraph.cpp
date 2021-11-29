#include "MGraph.h";

//通过静态数组创建图
//v为包含vertex值的数组，n为vertex的数量，e为edege的数量
MGraph::MGraph(char v[], int n, int e)
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

int main()
{
	
	int vertexNum, arcNum = 0;
	cout << "请输入vertex的数量：" << endl;
	cin >> vertexNum;
	char *myVertex = new char[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "请输入vertex的值：" << endl;
		cin >> myVertex[i];
	}
	cout << "请输入arc的数量：" << endl;
	cin >> arcNum;

	MGraph mg(myVertex, vertexNum, arcNum);
	mg.displayGraph();

	system("pause");
	return 0;
}