#pragma once

class Edge
{
public:
	const int NO_EDGE = -1;
	unsigned start;
	unsigned end;
	int cost;

	Edge(unsigned start, unsigned end) : Edge(start, end, NO_EDGE)
	{
		
	}

	Edge(unsigned start, unsigned end, int cost)
	{
		this-> start = start;
		this-> end = end;
		this-> cost = cost;
	}
};
