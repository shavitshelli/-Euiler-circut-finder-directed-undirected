#include "Vertex.h"
#include <list>
#include <vector>
using namespace std;


class DirectedGraph
{
    int NumOfVertices;
    vector<list<Edge>> adjacency;    // The adjacency lists for each vertix
    vector<list<Edge>::iterator > IteratorVector;
    int* indegree;
    int* outdegree;
public:
    DirectedGraph(int V);

    DirectedGraph(DirectedGraph&& other);

    ~DirectedGraph();

    void AddEdge(int u, int v);

    void DeleteEdge(int u, int v);

    void NeighborsList(int u);

    bool AreNeighbors(int u, int v);

    bool checkInDegreeEqualsOutDegree();

    bool isEulerian();

    bool isThereAStromgConnectionInTheGarph();

    bool isGraphConnected();

    void DFSConnectionCheck(int v, bool* visited);

    DirectedGraph createTranspose();

    list<int> FindCircuit(int v, bool flag);

    void printEulerianCircle();

    list<int> makeEulerianCircle();

    void initIteratorVector();
};