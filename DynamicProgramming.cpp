#pragma once

#include <iostream>
#include "Map.h"
#include "TspDp.h"


int main(void) {
	printf("Hello!\n");
	unsigned** map = new unsigned*[4]{
			new unsigned[4] {SolutionSet::INF, 2, 9, 10},
			new unsigned[4] { 1, SolutionSet::INF, 6, 4},
			new unsigned[4] { 15, 7, SolutionSet::INF, 8},
			new unsigned[4] { 6, 3, 12, SolutionSet::INF}
	};
	Map* baseMap = new Map(4, map);
	TspDp* dp = new TspDp(baseMap);
	ubyte* result = dp->solve();
	for (ubyte vertex = 0; vertex < baseMap->size; vertex++)
	{
		std::cout << vertex << " - ";
	}
	delete dp;
	delete baseMap;
	return 0;
}