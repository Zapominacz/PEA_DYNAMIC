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
	bool isNotSet(uinteger vertex_map, ubyte vertex) const;
	ubyte* getSolution();
	uinteger finalSolutionIndex() const;
	void loadSolutions() const;
	void loadFinal();
	ubyte* solution;
public:
	TspDp(Map* map);
	~TspDp(void);
	ubyte* solve();
	
};