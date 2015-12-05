#pragma once
#include "TspDp.h"

inline bool TspDp::isLoaded(SolutionSet::Solution* solution)
{
	return solution->value != SolutionSet::INF;
}

TspDp::TspDp(Map* map)
{
	this->map = map;
	solution = nullptr;
	solutions = new SolutionSet(map->size);
}

TspDp::~TspDp(void)
{
	delete solutions;
	solutions = nullptr;
	if(solution != nullptr)
	{
		delete solution;
		solution = nullptr;
	}
}

void TspDp::loadKnownSolutions() const
{
	SolutionSet::Solution* currSolution = solutions->getSolution(0);
	currSolution->lastVertex = 0;
	currSolution->value = 0;
}

inline bool TspDp::isNotSet(uinteger vertexMap, ubyte vertex) const
{
	return !(vertexMap & (1 << (vertex - 1)));
}

ubyte* TspDp::getSolution()
{
	if(solution == nullptr) {
		this->solution = new ubyte[map->size];
		uinteger currentSet = finalSolutionIndex();
		for (ubyte city = map->size; city > 0; city--)
		{
			ubyte vertex = solutions->getSolution(currentSet)->lastVertex;
			solution[city - 1] = vertex;
			currentSet ^= (1 << (vertex - 1));
		}
	}
	return solution;
}

inline uinteger TspDp::finalSolutionIndex() const
{
	return ((1 << (map->size - 1)) - 1);
}

void TspDp::loadSolutions() const
{
	using namespace std;
	uinteger finalSolution = finalSolutionIndex();
	for (uinteger solution = 0x00000001; solution < finalSolution; solution++)
	{
		SolutionSet::Solution* currentSolution = solutions->getSolution(solution);
		uinteger bestCost = SolutionSet::INF;
		ubyte bestVertex = SolutionSet::V_INF;
		for (ubyte vertex = 1; vertex < map->size; vertex++)
		{
			if (!isNotSet(solution, vertex))
			{
				uinteger currentSet = solution ^ (1 << (vertex - 1));
				SolutionSet::Solution* prevSolution = solutions->getSolution(currentSet);
				uinteger tmpCost = prevSolution->value + map->matrix[prevSolution->lastVertex][vertex];
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
}

void TspDp::loadFinal()
{
	uinteger fullSet = finalSolutionIndex();
	ubyte bestVertex = SolutionSet::V_INF;
	uinteger bestCost = SolutionSet::INF;
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		uinteger currentSet = fullSet ^ (1 << (vertex - 1));
		SolutionSet::Solution* solution = solutions->getSolution(currentSet);
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
	loadSolutions();
	loadFinal();
	ubyte* solution = getSolution();
	return solution;
}
