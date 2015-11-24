#pragma once
#include "SolutionSet.h"
#include "Map.h"

class TspDp
{
private:
	Map* map;
	SolutionSet* solutions;
	bool isLoaded(SolutionSet::Solution* solution);
	void loadKnownSolutions();
	SolutionSet::Solution* load(uinteger vertexMap);
	ubyte* getSolution();
	uinteger finalSolutionIndex();
	void loadFinal();
public:
	TspDp(Map* map);
	~TspDp(void);
	ubyte* solve();
	
};