#pragma once
#include "SolutionSet.h"

/*
Miko�aj Sty�, 209773
Reprezentuje map� miast z wagami przej��
*/
class Map
{
public:
	unsigned size;
	unsigned** matrix;

	Map(unsigned size)
	{
		this->size = size;
		matrix = new unsigned*[size];
		for (unsigned row = 0; row < size; row++)
		{
			matrix[row] = new unsigned[size];
			for (unsigned col = 0; col < size; col++)
			{
				matrix[row][col] = SolutionSet::INF;
			}
		}
	}

	Map(unsigned size, unsigned **matrix)
	{
		this->size = size;
		this->matrix = matrix;
	}

	~Map(void)
	{
		for (unsigned row = 0; row < size; row++)
		{
			delete[] matrix[row];
		}
		delete[] matrix;
	}

};