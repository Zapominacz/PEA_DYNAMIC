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

ubyte* TspDp::getSolution(SolutionSet::Solution finalSolution)
{
	SolutionSet::Solution tmpSolution = finalSolution;
	while(tmpSolution.vertexBitmask.any())
	{
		//TODO..
	}
}

ubyte* TspDp::solve()
{
	load(finalSolution)
	ubyte* solution = getSolution(finalSolution);
	return solution;
}

