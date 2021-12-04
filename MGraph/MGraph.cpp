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
			arc[i][j] = MY_INFINITY;
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
	int vertex1, vertex2, weight;
	for (int i = 0; i < this->arcNum; i++)
	{
		cout << "������Ҫ����ڱߵ�����vertex�ı�ţ�������Ȩֵ��" << endl;
		cin >> vertex1 >> vertex2 >> weight;
		this->arc[vertex1][vertex2] = weight;
		this->arc[vertex2][vertex1] = weight;
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

/*prim�㷨��https://www.bilibili.com/video/BV1Ua4y1i7tf?from=articleDetail
shortEdge��һ��������adjVex��lowCost�����顣������洢��vertex[]���������еĵ㵽adjVex�����̱߳�lowCost��
������adjVex�Ƕ���0ʱ����vertex[]�еĶ���0��1��2��3...n��0����̾�����shortEdge[].lowCost*/
void MGraph::Prim(int start)
{
	int min;
	//��ʼ��shortEdge,ʹadjVex�Ķ������㷨����ʼ�㣬��lowCost��ֵ�������������㵽��ʼ��adjVex�ľ���,���ҽ�start����뼯��U�У���lowCost����Ϊ0��
	for (int i = 0; i < vertexNum; i++)
	{
		shortEdge[i].adjVex = start;
		shortEdge[i].lowCost = arc[start][i];
	}
	shortEdge[start].lowCost = 0;

	cout << "�������V" << start << "��ʼ����С��������" << endl;
	for (int j = 0; j < vertexNum - 1; j++)
	{
		//�ҵ�������ʼ���������̵Ķ���󣬷��ظö������Ÿ�min�������ö����lowCost����Ϊ0����ʾ���ö�����뼯��U��
		min = getMinCost(shortEdge);
		outputPrim(min, shortEdge[min]);//������̾��붥��ı��min��Ϊ�������㣬shortEdge[min].adjVex��Ϊ��ʼ�㣬shortEdge[min].lowCost��ΪȨֵ
		shortEdge[min].lowCost = 0;
		/*����shortEdge����adjVex�ƶ�����һ�����뵱ǰ��������Ķ��㣬����arc[]�м��ö��㵽ʣ�ඥ��ľ��룬���С�ڵ�ǰ������shortEdge[]�е�ֵ��
		�����shortEdge[]�е�lowCost(Ȩֵ)��adjVex(���ı��)*/
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
	cout << "��" << myArr.adjVex << ", " << endVertex << "��" << myArr.lowCost << endl;
}

//�ú�������shortEdge�е�lowCost����С��ֵ�����ҵ���ǰ�����������һ������֮��ľ���(��Ϊ0)
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
	cout << endl;

	cout << "׼����ʼѰ����С����������������ʼ����ı�ţ�";
	cin >> start;
	mg.Prim(start);

	system("pause");
	return 0;
}