#pragma once
#include "Map.h"

class MapGenerator
{
private:
	Map* lastGenerated;
	const unsigned MAX_SIZE = 100;
	void cleanUp();
public:
	MapGenerator(void);
	~MapGenerator(void);
	Map* generate(unsigned size);
	Map* getLastGenerated();
};