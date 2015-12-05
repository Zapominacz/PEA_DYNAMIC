#pragma once
#include "TspDp.h"

inline bool TspDp::isLoaded(SolutionSet::Solution* solution)
{
	return solution->value != SolutionSet::INF;
}

TspDp::TspDp(Map* map)
{
	this->map = map;
	solutions = new SolutionSet(map->size);
}

TspDp::~TspDp(void)
{
	delete solutions;
}

void TspDp::loadKnownSolutions()
{
	uinteger set = 0x00000001;
	SolutionSet::Solution* solution;
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		solution = solutions->getSolution(set, vertex);
		solution->value = map->matrix[0][vertex];
		solution->lastVertex = 0;
		set = set << 1;
	}
}

inline bool TspDp::isSet(uinteger vertexMap, ubyte vertex)
{
	return !(!(vertexMap & (1 << (vertex - 1))));
}

ubyte* TspDp::getSolution(ubyte vertex)
{
	ubyte* result = new ubyte[map->size];
	uinteger currentSet = finalSolutionIndex();
	SolutionSet::Solution* solution = nullptr;
	for (ubyte city = map->size - 1; city > 0; city--)
	{
		result[city] = vertex;
		solution = solutions->getSolution(currentSet, vertex);
		currentSet ^= (1 << (vertex - 1));
		vertex = solution->lastVertex;
	}
	result[0] = 0;
	return result;
}

inline uinteger TspDp::finalSolutionIndex()
{
	return ((1 << (map->size - 1)) - 1);
}

ubyte* TspDp::loadFinal()
{
	uinteger fullSet = finalSolutionIndex();
	ubyte bestVertex = SolutionSet::V_INF;
	uinteger bestCost = SolutionSet::INF;
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		uinteger cost = load(fullSet, vertex) + map->matrix[vertex][0];
		if(bestCost > cost)
		{
			bestVertex = vertex;
			bestCost = cost;
		}
	}

	//TODO koszt?
	return getSolution(bestVertex);
}

ubyte* TspDp::solve()
{
	loadKnownSolutions();
	return loadFinal();
}

uinteger TspDp::load(uinteger vertexMap, ubyte endVertex)
{
	SolutionSet::Solution* solution = solutions->getSolution(vertexMap, endVertex);
	if(!isLoaded(solution))
	{
		ubyte bestVertex = SolutionSet::V_INF;
		ubyte bestCost = SolutionSet::INF;
		vertexMap = vertexMap ^ (1 << (endVertex - 1));
		for (ubyte startVertex = 1; startVertex < map->size; startVertex++)
		{
			if(isSet(vertexMap, startVertex))
			{
				uinteger cost = load(vertexMap, startVertex) + map->matrix[startVertex][endVertex];
				if (bestCost > cost)
				{
					bestVertex = startVertex;
					bestCost = cost;
				}
			}
		}
		solution->lastVertex = bestVertex;
		solution->value = bestCost;
	}
	return solution->value;
}

