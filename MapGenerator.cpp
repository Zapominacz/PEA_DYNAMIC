#pragma once
#include "MapGenerator.h"
#include <random>

void MapGenerator::cleanUp()
{
	if (lastGenerated != nullptr)
	{
		delete lastGenerated;
		lastGenerated = nullptr;
	}
}

MapGenerator::MapGenerator()
{
	lastGenerated = nullptr;
}

MapGenerator::~MapGenerator()
{
	cleanUp();
}

Map* MapGenerator::generate(unsigned size)
{
	using namespace std;
	cleanUp();
	lastGenerated = new Map(size);
	default_random_engine generator;
	uniform_int_distribution<unsigned> distribution(0, MAX_SIZE);
	for (unsigned row = 0; row < size; row++)
	{
		for (unsigned col = 0; col < size; col++)
		{
			if(col != row)
			{
				lastGenerated->matrix[row][col] = distribution(generator);
			}
		}
	}
	return lastGenerated;
}

Map* MapGenerator::getLastGenerated()
{
	return lastGenerated;
}
