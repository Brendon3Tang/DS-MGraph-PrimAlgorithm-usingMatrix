#include "MGraph.h";

//ͨ����̬���鴴��ͼ
//vΪ����vertexֵ�����飬nΪvertex��������eΪedege������
MGraph::MGraph(int v[], int n, int e)
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

	//��ʼ��visited
	cleanVisited();
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

void MGraph::DFSTraverse(int v)
{
	//��ʼ��visited����
	cleanVisited();

	//�����Ѱ���Ϊv�Ķ���
	DFS(v);

	//ѭ������visited���飬����л�δvisit�Ķ��㣬���Ըö���Ϊ������DFS
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
	//����ҵ��ĵ�һ���ڵ㣬�����ýڵ��bool����Ϊtrue
	cout << vertex[v] << " ";
	visited[v] = true;

	//�ھ����е�ǰ�������һ����Ѱ���뵱ǰ������������������
	for (int i = 0; i < vertexNum; i++)
	{
		//����ö������������������㣨arc[v][i]==1���һ�δvisit���Ķ��㣬��ݹ����ڶ���
		if (arc[v][i] == 1 && visited[i] == false)
		{
			DFS(i);
		}
	}
}

void MGraph::BFSTraverse(int v)
{
	//��ʼ��visited����
	cleanVisited();

	BFS(v);

	//ѭ������visited���飬����л�δvisit�Ķ��㣬���Ըö���Ϊ������BFS
	for (int i = 0; i < vertexNum; i++)
	{
		if (visited[i] == false)
			BFS(i);
	}
}

void MGraph::BFS(int v)
{
	//�����ǰ���㣬��������push��queue��
	cout << vertex[v] << " ";
	visited[v] = true;
	myQueue.push(vertex[v]);

	//������в�Ϊ����ѭ�����е����п�Ϊֹ
	while (!myQueue.empty())
	{
		v = myQueue.front();//�����׵�ֵ������ı�ţ�����v
		myQueue.pop();//pop���׵�ֵ

		//ѭ���ö����ھ����ж�Ӧ���У��ҵ���ö�����������������
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
	cout << "������vertex��������" << endl;
	cin >> vertexNum;
	int *myVertex = new int[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "������vertex��ֵ��" << endl;
		cin >> myVertex[i];
	}
	cout << "������arc��������" << endl;
	cin >> arcNum;

	MGraph mg(myVertex, vertexNum, arcNum);
	mg.displayGraph();

	int start;
	cout << "׼����ʼ�������DFS����������ʼ����ı�ţ�";
	cin >> start;
	mg.DFSTraverse(start);
	cout << endl;

	cout << "׼����ʼ�������BFS����������ʼ����ı�ţ�";
	cin >> start;
	mg.BFSTraverse(start);

	system("pause");
	return 0;
}