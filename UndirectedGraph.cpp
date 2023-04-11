#include "UndirectedGraph.h"


UndirectedGraph::UndirectedGraph(int V)
{
	adjacency.resize(V);
	IteratorVector.resize(V);
	this->NumOfVertices = V;

	for (int i = 0; i < V; i++)
	{
		adjacency[i].push_back(Edge(-1));
	}
}

void UndirectedGraph::AddEdge(int u, int v)
{
	u--;
	v--;
	adjacency[u].push_back(Edge(v));
	adjacency[v].push_back(Edge(u));

	if (adjacency[u].size() == 2)//if its the first value added we need to make dummy head point to it 

		adjacency[u].front().parallelEdge = &(*(++adjacency[u].begin()));

	adjacency[u].back().parallelEdge = &adjacency[v].back();//we always push to the list end 

	if (adjacency[v].size() == 2)//if its the first value added we need to make dummy head point to it 
	
		adjacency[v].front().parallelEdge = &(*(++adjacency[v].begin()));
	
	adjacency[v].back().parallelEdge = &adjacency[u].back();//we always push to the list end 
}

void UndirectedGraph::DeleteEdge(int u, int v)
{
	u--;
	v--;
	adjacency[u].remove(v);
	adjacency[v].remove(u);

}

void UndirectedGraph::NeighborsList(int u)
{
	u--;
	for (auto i = ++adjacency[u].begin(); i != adjacency[u].end(); i++)
	{
		cout << (*i).Vnum+1 << " ";
	}
}

bool UndirectedGraph::AreNeighbors(int u, int v)
{
	u--;
	for (auto i = adjacency[u].begin(); i != adjacency[u].end(); i++)
	{
		if ((*i).Vnum == v - 1)
			return true;
	}
	return false;
}

void UndirectedGraph::DFSConnectionCheck(int v, bool* visited)
{
	visited[v] = true;
	list<Edge>::iterator i;

	for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
	{
		int place = (*i).Vnum;
		if (place>0 && !visited[place])
		{
			DFSConnectionCheck(place, visited);
		}
	}
}


bool UndirectedGraph::isGraphConnected()
{
	bool* visited = new bool[NumOfVertices];
	int i;
	for (i = 0; i < NumOfVertices; i++)
		visited[i] = false;

	//fills the visited array 
	DFSConnectionCheck(0, visited);

	// if all vertices are visited so graph is connected 
	for (i = 0; i < NumOfVertices; i++)
		if (visited[i] == false)
			return false;

	return true;
}

bool UndirectedGraph::isAllVertexeswithEvevDegree()
{
	for (int i = 0; i < NumOfVertices; i++)
	{
		if (adjacency[i].size() % 2 - 1 != 0)// if there is a vertex with odd degree graph is not euiler because of dummy head we take off 1 
			return false;
	}
	return true;
}

bool UndirectedGraph::isEulerian()
{
	if (isGraphConnected() == false|| isAllVertexeswithEvevDegree() == false)// if there graph is not connected graph is not euiler
	{
		cout << "The graph is not aulerian" << endl;;
		return false;
	}
	cout << "The graph is aulerian"<<endl;
	printEulerianCircle();
	return true;
}

list<int> UndirectedGraph::FindCircuit(int v , bool flag)
{
	list<int> tempListToReturn;
	int thisVertex = v;
	int NextVertex;
	tempListToReturn.push_back(thisVertex);
	while (IteratorVector[v] != adjacency[v].end())
	{
		(*IteratorVector[thisVertex]).CanWeGoThroghThisEdge = false;//mark this edge 
		(*IteratorVector[thisVertex]).parallelEdge->CanWeGoThroghThisEdge = false;//mark paralel edge 
		NextVertex = (*IteratorVector[thisVertex]).Vnum;
		tempListToReturn.push_back(NextVertex);
		while ((*IteratorVector[thisVertex]).CanWeGoThroghThisEdge == false)//check if we stand on an edge that we already stood on 
		{
			(IteratorVector[thisVertex])++;
			if (IteratorVector[thisVertex] == adjacency[thisVertex].end())//check we do not exceed the limit
				break;
		}
		while ((*IteratorVector[NextVertex]).CanWeGoThroghThisEdge == false)//check if we stand on an edge that we already stood on 
		{
			(IteratorVector[NextVertex])++;
			if (IteratorVector[NextVertex] == adjacency[NextVertex].end())//check we do not exceed the limit
				break;
		}
		thisVertex = NextVertex;
	}
	if (flag == true)//aka first time we use find circuit 
		return tempListToReturn;//return full list
	tempListToReturn.pop_front();
	return tempListToReturn;
}

void UndirectedGraph::printEulerianCircle()
{
	initIteratorVector();
	list<int> EulerianCircle = makeEulerianCircle();
	int printCorrect = 0;
	for (list<int>::iterator i = EulerianCircle.begin(); i != EulerianCircle.end(); i++)
	{
		if (printCorrect == 0)
			cout << "(" ;
		cout << *i+1;
		if (printCorrect != EulerianCircle.size()-1)
			cout << ",";
		else 
			cout << ")";
		printCorrect++;
	}
}

list<int> UndirectedGraph::makeEulerianCircle()
{
	list<int> EulerianCircle = FindCircuit(0, true);
	list<int>::iterator currEulerianCircleIterator = EulerianCircle.begin();
	list<int>::iterator nextEulerianCircleIterator = ++EulerianCircle.begin();
	list<int>::iterator tempIterator;
	while (currEulerianCircleIterator != EulerianCircle.end())
	{
		int i = *currEulerianCircleIterator;
		if (IteratorVector[i] == adjacency[i].end())
		{
			currEulerianCircleIterator++;
			nextEulerianCircleIterator++;
		}
		if (nextEulerianCircleIterator == EulerianCircle.end())
			break;
		i = *currEulerianCircleIterator;
		list<int> tempEulerianCircle = FindCircuit(i, false);
		EulerianCircle.splice(nextEulerianCircleIterator, tempEulerianCircle);
		tempIterator = currEulerianCircleIterator;
		nextEulerianCircleIterator = ++currEulerianCircleIterator;
		currEulerianCircleIterator = tempIterator;
	}
	return EulerianCircle;
}

void UndirectedGraph::initIteratorVector()
{
	for (int i = 0; i < NumOfVertices; i++)
	{
		IteratorVector[i] = ++adjacency[i].begin();
	}

}
