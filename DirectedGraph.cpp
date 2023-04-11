#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int V)
{
	adjacency.resize(V);
	IteratorVector.resize(V);
	this->NumOfVertices = V;
	this->indegree = new int[V];
	this->outdegree = new int[V];
	for (int i = 0; i < V; i++)
	{
		adjacency[i].push_back(Edge(-1));
		outdegree[i]=0;
		indegree[i]=0;
	}
}

DirectedGraph:: DirectedGraph(DirectedGraph&& other)
{
	this->NumOfVertices = other.NumOfVertices;
	this->adjacency = other.adjacency;
	this->indegree = other.indegree;
	other.indegree = nullptr;
	this->outdegree = other.outdegree;
	other.outdegree = nullptr;
}

DirectedGraph::~DirectedGraph()
{
	delete[]outdegree;
	delete[]indegree;

}
void DirectedGraph::AddEdge(int u, int v)
{
	u--;
	v--;
	adjacency[u].push_back(Edge(v));
	// Edge from u to v is an addition to u outdegree and v indegree 
	outdegree[u]++;
	indegree[v]++;
}

void DirectedGraph::DeleteEdge(int u, int v)
{
	u--;
	v--;
	adjacency[u].remove(v);
}

void DirectedGraph::NeighborsList(int u)
{
	u--;
	for (auto i = ++adjacency[u].begin(); i != adjacency[u].end(); i++)
	{
		cout << (*i).Vnum + 1 << " ";
	}
}

bool DirectedGraph::AreNeighbors(int u, int v)
{
	u--;
	for (auto i = adjacency[u].begin(); i != adjacency[u].end(); i++)
	{
		if ((*i).Vnum == v - 1)
			return true;
	}
	return false;
}

bool DirectedGraph::checkInDegreeEqualsOutDegree()
{
	bool isInDegreeEqualsOutDegree = true;

	for (int i = 0; i < this->NumOfVertices; i++)
	{
		if (indegree[i] != outdegree[i])
		{
			isInDegreeEqualsOutDegree = false;
		}
	}
	return isInDegreeEqualsOutDegree;
}

bool DirectedGraph::isEulerian()
{
	if (isThereAStromgConnectionInTheGarph() == false || checkInDegreeEqualsOutDegree() == false)
	{
		cout << "The graph is not aulerian" << endl;;
		return false;
	}
	cout << "The graph is aulerian" << endl;
	printEulerianCircle();
	return true;
}

bool DirectedGraph::isThereAStromgConnectionInTheGarph()
{
	bool isThereAStromgConnection = isGraphConnected();

	if (isThereAStromgConnection)
	{
		DirectedGraph transpose = createTranspose();

		isThereAStromgConnection = transpose.isGraphConnected();
	}

	return isThereAStromgConnection;
}

void DirectedGraph::DFSConnectionCheck(int v, bool* visited)
{
	visited[v] = true;
	list<Edge>::iterator i;

	for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
	{
		int place = (*i).Vnum;
		if (place > 0 && !visited[place])
		{
			DFSConnectionCheck(place, visited);
		}
	}
}


bool DirectedGraph::isGraphConnected()
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

DirectedGraph DirectedGraph::createTranspose()
{
	DirectedGraph resGraph(this->NumOfVertices);
	int realVnumVal, realCurrVal;
	for (int i = 0; i < this->NumOfVertices; i++)
	{
		list<Edge>::iterator currVer = ++adjacency[i].begin();
		list<Edge>::iterator endItr = adjacency[i].end();

		while (currVer != endItr)
		{
			realVnumVal = (*currVer).Vnum + 1;
			realCurrVal = i + 1;
			resGraph.AddEdge(realVnumVal, realCurrVal);
			++currVer;
		}
	}

	return resGraph;
}

list<int> DirectedGraph::FindCircuit(int v, bool flag)
{
	list<int> tempListToReturn;
	int thisVertex = v;
	int NextVertex;
	tempListToReturn.push_back(thisVertex);
	while (indegree[v]!=0)//if indegree==0 we fount the closure of the circle
	{
		(*IteratorVector[thisVertex]).CanWeGoThroghThisEdge = false;//mark this edge 
		NextVertex = (*IteratorVector[thisVertex]).Vnum;
		tempListToReturn.push_back(NextVertex);
		while ((*IteratorVector[thisVertex]).CanWeGoThroghThisEdge == false)//check if we stand on an edge that we already stood on 
		{
			(IteratorVector[thisVertex])++;
			if (IteratorVector[thisVertex] == adjacency[thisVertex].end())//check we do not exceed the limit
				break;
		}
		while (IteratorVector[NextVertex] != adjacency[NextVertex].end()&&
			(*IteratorVector[NextVertex]).CanWeGoThroghThisEdge == false)//check if we stand on an edge that we already stood on 
		{
			(IteratorVector[NextVertex])++;
			if (IteratorVector[NextVertex] == adjacency[NextVertex].end())//check we do not exceed the limit
				break;
		}
		indegree[NextVertex]--;
		thisVertex = NextVertex;
	}
	if (flag == true)//aka first time we use find circuit 
		return tempListToReturn;//return full list
	tempListToReturn.pop_front();//return list without first element 
	return tempListToReturn;
}

void DirectedGraph::printEulerianCircle()
{
	initIteratorVector();
	list<int> EulerianCircle = makeEulerianCircle();
	int printCorrect = 0;
	for (list<int>::iterator i = EulerianCircle.begin(); i != EulerianCircle.end(); i++)
	{
		if (printCorrect == 0)
			cout << "(";
		cout << *i + 1;
		if (printCorrect != EulerianCircle.size() - 1)
			cout << ",";
		else
			cout << ")";
		printCorrect++;
	}
}

list<int> DirectedGraph::makeEulerianCircle()
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

void DirectedGraph::initIteratorVector()
{
	for (int i = 0; i < NumOfVertices; i++)
	{
		IteratorVector[i] = ++adjacency[i].begin();
	}
}