#include "Vertex.h"
#include <list>
#include <vector>
using namespace std;


class UndirectedGraph
{
    int NumOfVertices;
    vector<list<Edge>> adjacency;    // The adjacency lists for each vertix
    vector<list<Edge>::iterator > IteratorVector;

public:
    UndirectedGraph(int V);

    ~UndirectedGraph() = default;

    void AddEdge(int u, int v);

    void DeleteEdge(int u, int v);

    void NeighborsList(int u);

    bool AreNeighbors(int u, int v);

    bool isGraphConnected();

    void DFSConnectionCheck(int v, bool* visited);

    bool isEulerian();

    list<int> FindCircuit(int v , bool flag);

    void printEulerianCircle();

    list<int> makeEulerianCircle();

    void initIteratorVector();

    bool isAllVertexeswithEvevDegree();

};