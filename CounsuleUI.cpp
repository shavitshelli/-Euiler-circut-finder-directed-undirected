#include "CounsuleUI.h"


bool CounsuleUI::getInfoFromUser()
{
	int n, m;
	char answer;
	cout << "Is the graph directed: y/n" << endl;
	cin >> answer >> n >> m;
	if (n <= 0 || m <= 0)
	{
		cout << "invalid input";
		return 0;
	}
	switch (answer) {
	case 'y':
		getVerticesForDirectedGraph(n, m);
		break;
	case 'n':
		getVerticesForUnDirectedGraph(n, m);
		break;
	default:
		cout << "invalid input";
		return 0;
	}
	return 0;
}

bool CounsuleUI::getVerticesForDirectedGraph(int size, int NumOfEdges)
{
	DirectedGraph g1(size);
	int vertix1, vertix2;
	for (int i = 0; i < NumOfEdges; i++)
	{
		cin >> vertix1 >> vertix2;
		if (vertix1 > size || vertix2 > size || vertix1 <= 0 || vertix2 <= 0)
		{
			cout << "invalid input";
			return 0;
		}
		g1.AddEdge(vertix1, vertix2);
	}
	g1.isEulerian();
}
bool CounsuleUI::getVerticesForUnDirectedGraph(int size, int NumOfEdges)
{
	UndirectedGraph g1(size);
	int vertix1, vertix2;
	for (int i = 0; i < NumOfEdges; i++)
	{
		cin >> vertix1 >> vertix2;
		if (vertix1 > size || vertix2 > size || vertix1 <= 0 || vertix2 <= 0)
		{
			cout << "invalid input";
			return 0;
		}
		g1.AddEdge(vertix1, vertix2);
	}
	g1.isEulerian();
}

