#pragma once
#include "TspDp.h"

bool TspDp::isLoaded(SolutionSet::Solution* solution)
{
	return solution->value != SolutionSet::INF;
}

TspDp::TspDp(Map* map)
{
	this->map = map;
	solutions = new SolutionSet(map->size);
}

TspDp::~TspDp()
{
	delete solutions;
}

void TspDp::loadKnownSolutions()
{
	SolutionSet::Solution* currSolution = solutions->getSolution(0);
	currSolution->lastVertex = 1;
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

ubyte* TspDp::getSolution()
{
	ubyte* solution = new ubyte[map->size];
	uinteger currentSet = finalSolutionIndex();
	for (ubyte city = 0; city < map->size; city++)
	{
		ubyte vertex = solutions->getSolution(currentSet)->lastVertex;
		solution[city] = vertex;
		currentSet ^= (1 << (vertex - 1));
	}
	return solution;
}

inline uinteger TspDp::finalSolutionIndex()
{
	return (1 << (map->size - 1) - 1);
}

void TspDp::loadFinal()
{
	uinteger fullSet = finalSolutionIndex();
	SolutionSet::Solution* best = nullptr;
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		uinteger currentSet = fullSet ^ (1 << (vertex - 1));
		SolutionSet::Solution* solution = load(currentSet);
		if(best == nullptr || best->value > solution->value)
		{
			best = solution;
		}
	}
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
	
	return currentSolution;
}

