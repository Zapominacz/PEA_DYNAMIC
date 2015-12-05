#pragma once
#include "SolutionSet.h"
#include "Map.h"

class TspDp
{
private:
	Map* map;
	SolutionSet* solutions;
	bool isLoaded(SolutionSet::Solution* solution);
	void loadKnownSolutions() const;
	bool isSet(uinteger vertex_map, ubyte vertex) const;
	ubyte* getSolution(ubyte vertex);
	uinteger load(uinteger vertexMap, ubyte vertex);
	uinteger finalSolutionIndex() const;
	ubyte* loadFinal();
public:
	TspDp(Map* map);
	~TspDp(void);
	ubyte* solve();
};