#pragma once

#include <iostream>
#include "Map.h"
#include "TspDp.h"


int main(void) {
	printf("Hello!\n");
	uinteger** map = new uinteger*[4]{
			new uinteger[4] {SolutionSet::INF, 2, 9, 10},
			new uinteger[4] { 1, SolutionSet::INF, 6, 4},
			new uinteger[4] { 15, 7, SolutionSet::INF, 8},
			new uinteger[4] { 6, 3, 12, SolutionSet::INF}
	};
	Map* baseMap = new Map(4, map);
	TspDp* dp = new TspDp(baseMap);
	ubyte* result = dp->solve();
	for (ubyte vertex = 0; vertex < baseMap->size; vertex++)
	{
		std::cout << static_cast<int>(result[vertex]) << " - ";
	}
	std::getchar();
	delete dp;
	delete baseMap;
	return 0;
}