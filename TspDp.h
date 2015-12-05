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
	bool isNotSet(uinteger vertex_map, ubyte vertex);
	SolutionSet::Solution* load(uinteger vertexMap);
	ubyte* getSolution();
	uinteger finalSolutionIndex();
	void loadFinal();
	ubyte* solution;
public:
	TspDp(Map* map);
	~TspDp(void);
	ubyte* solve();
	
};