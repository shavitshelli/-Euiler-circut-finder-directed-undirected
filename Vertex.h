#ifndef EDGE__H
#define EDGE__H
#include<iostream>
using namespace std;


class Edge
{
public:
	int Vnum;
	bool CanWeGoThroghThisEdge;
	Edge* parallelEdge;// for a normal edge will point to the paralle for dummy head will point to the first edge that was not used  
	Edge(int num) :parallelEdge(nullptr) { Vnum = num; CanWeGoThroghThisEdge = true; };
	~Edge() = default;
	bool operator==(const Edge& other) const
	{
		return Vnum == other.Vnum;
	}
};

#endif // !EDGE__H

