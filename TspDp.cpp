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
	solutions = nullptr;
}

void TspDp::loadKnownSolutions() const //£aduje znane rozwiazania, czyli zbiory jednoelementowe
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

inline bool TspDp::isSet(uinteger vertexMap, ubyte vertex) const //czy bit jest ustawiony - do odczytu zawartosci zbioru
{
	return !(!(vertexMap & (1 << (vertex - 1))));
}

ubyte* TspDp::getSolution(ubyte vertex) //backtracking do znalezienia kolejnoœci wierzcho³ków
{
	ubyte* result = new ubyte[map->size];
	uinteger currentSet = finalSolutionIndex();
	SolutionSet::Solution* solution;
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

//pomocnicza funkcja do obliczania zbioru pe³nego
inline uinteger TspDp::finalSolutionIndex() const
{
	return ((1 << (map->size - 1)) - 1);
}

//wylicza rozwi¹zanie, leniwie rozwi¹zauj¹c podrozwi¹zania
ubyte* TspDp::loadFinal()
{
	uinteger fullSet = finalSolutionIndex();
	ubyte bestVertex = SolutionSet::V_INF;
	uinteger bestCost = SolutionSet::INF;
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		uinteger cost = load(fullSet, vertex) + map->matrix[vertex][0];
		if (bestCost > cost)
		{
			bestVertex = vertex;
			bestCost = cost;
		}
	}
	return getSolution(bestVertex);
}

ubyte* TspDp::solve()
{
	loadKnownSolutions();
	return loadFinal();
}

//Leniwie ³aduje rozwi¹zania, czyli je¿eli nie zosta³o jeszcze utworzone - tworzy
uinteger TspDp::load(uinteger vertexMap, ubyte endVertex)
{
	SolutionSet::Solution* solution = solutions->getSolution(vertexMap, endVertex);
	if(!isLoaded(solution))
	{
		ubyte bestVertex = SolutionSet::V_INF;
		uinteger bestCost = SolutionSet::INF;
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
