#pragma once
#include "Map.h"
/*
Miko³aj Styœ, 209773
Generator intancji asymetrycznego problemu komiwoja¿era
*/
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