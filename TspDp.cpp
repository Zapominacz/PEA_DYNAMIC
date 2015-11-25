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
	SolutionSet::Solution* currSolution = solutions->getSolution(0);
	currSolution->lastVertex = 0;
	currSolution->value = 0;

	uinteger solution = 0x00000001;
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		currSolution = solutions->getSolution(solution);
		currSolution->lastVertex = vertex;
		currSolution->value = map->matrix[0][vertex];
		solution = solution << 1;
	}
}

inline bool TspDp::isNotSet(uinteger vertexMap, ubyte vertex)
{
	return !(vertexMap & (1 << (vertex - 1)));
}

ubyte* TspDp::getSolution()
{
	ubyte* solution = new ubyte[map->size];
	uinteger currentSet = finalSolutionIndex();
	for (ubyte city = map->size; city > 0; city--)
	{
		ubyte vertex = solutions->getSolution(currentSet)->lastVertex;
		solution[city - 1] = vertex;
		currentSet ^= (1 << (vertex - 1));
	}
	return solution;
}

inline uinteger TspDp::finalSolutionIndex()
{
	return ((1 << (map->size - 1)) - 1);
}

void TspDp::loadFinal()
{
	uinteger fullSet = finalSolutionIndex();
	ubyte bestVertex = SolutionSet::V_INF;
	uinteger bestCost = SolutionSet::INF;
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		uinteger currentSet = fullSet ^ (1 << (vertex - 1));
		SolutionSet::Solution* solution = load(currentSet);
		uinteger tmpCost = solution->value + map->matrix[solution->lastVertex][vertex];
		tmpCost += map->matrix[vertex][0];
		if(bestCost > tmpCost)
		{
			bestVertex = vertex;
			bestCost = tmpCost;
		}
	}
	SolutionSet::Solution* finalSet = solutions->getSolution(fullSet);
	finalSet->value = bestCost;
	finalSet->lastVertex = bestVertex;
}

ubyte* TspDp::solve()
{
	loadKnownSolutions();
	loadFinal();
	ubyte* solution = getSolution();
	return solution;
}

SolutionSet::Solution* TspDp::load(uinteger vertexMap)
{
	SolutionSet::Solution* currentSolution = solutions->getSolution(vertexMap);
	if(!isLoaded(currentSolution))
	{
		uinteger bestCost = SolutionSet::INF;
		ubyte bestVertex = SolutionSet::V_INF;
		for (ubyte vertex = 1; vertex < map->size; vertex++)
		{
			if(!isNotSet(vertexMap, vertex))
			{
				uinteger currentSet = vertexMap ^ (1 << (vertex - 1));
				SolutionSet::Solution* solution = load(currentSet);
				uinteger tmpCost = solution->value + map->matrix[solution->lastVertex][vertex];
				if (bestCost > tmpCost)
				{
					bestVertex = vertex;
					bestCost = tmpCost;
				}
			}
		}
		currentSolution->lastVertex = bestVertex;
		currentSolution->value = bestCost;
	}
	return currentSolution;
}

