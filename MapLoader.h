#pragma once
#include "Map.h"

class MapLoader
{
private:
	Map* lastLoaded;
	void cleanUp();
public:
	MapLoader(void);
	~MapLoader(void);
	Map* load();
	Map* getLastLoaded();
};