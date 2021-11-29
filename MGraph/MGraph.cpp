#include "MGraph.h";

//ͨ����̬���鴴��ͼ
//vΪ����vertexֵ�����飬nΪvertex��������eΪedege������
MGraph::MGraph(char v[], int n, int e)
{
	//����vertex��������edge������
	this->vertexNum = n;
	this->arcNum = e;

	//����v[]�ﴢ������ݣ�Ϊvertex[]��ֵ
	for (int i = 0; i < this->vertexNum; i++)
	{
		this->vertex[i] = v[i];
	}

	//��ʼ��matrix
	for (int i = 0; i < this->vertexNum; i++)
	{
		for (int j = 0; j < this->vertexNum; j++)
		{
			arc[i][j] = 0;
		}
	}
	//��дmatrix������graph
	BuildGraph();
}

//����edgeΪmatrix����ֵ�������������vertex�ı�ţ��������������vertex֮������һ��edge������matrix�϶�Ӧλ������1.
void MGraph::BuildGraph()
{
	int vertex1, vertex2;
	for (int i = 0; i < this->arcNum; i++)
	{
		cout << "������Ҫ����ڱߵ�����vertex�ı�ţ�" << endl;
		cin >> vertex1 >> vertex2;
		this->arc[vertex1][vertex2] = 1;
		this->arc[vertex2][vertex1] = 1;
	}

}

//չʾgraph��matrix
void MGraph::displayGraph()
{
	cout << "��ӡgraph����" << endl;
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
	cout << "������vertex��������" << endl;
	cin >> vertexNum;
	char *myVertex = new char[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "������vertex��ֵ��" << endl;
		cin >> myVertex[i];
	}
	cout << "������arc��������" << endl;
	cin >> arcNum;

	MGraph mg(myVertex, vertexNum, arcNum);
	mg.displayGraph();

	system("pause");
	return 0;
}