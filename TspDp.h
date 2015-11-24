#pragma once
#include "SolutionSet.h"
#include "Map.h"

class TspDp
{
private:
	Map* map;
	SolutionSet* solutions;
	bool isLoaded(SolutionSet::Solution* solution);
public:
	TspDp(Map* map);
	~TspDp(void);
	ubyte* getSolution(SolutionSet::Solution finalSolution);
	ubyte* solve();
};