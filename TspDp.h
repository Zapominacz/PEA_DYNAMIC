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
	bool isSet(uinteger vertexMap, ubyte vertex);
	uinteger load(uinteger vertexMap, ubyte vertex);
	ubyte* getSolution(ubyte vertex);
	uinteger finalSolutionIndex();
	ubyte* loadFinal();
public:
	TspDp(Map* map);
	~TspDp(void);
	ubyte* solve();
	
};