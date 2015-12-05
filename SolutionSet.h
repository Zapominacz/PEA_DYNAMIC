#pragma once
#include <iostream>
#include <fstream>
#include <bitset>

typedef uint8_t ubyte;
typedef int8_t byte;
typedef int32_t integer;
typedef uint32_t uinteger;

class SolutionSet
{
public:
	static const uinteger INF = UINT32_MAX; //INF - zazwyczaj oznacza brak krawêdzi
	static const ubyte V_INF = UINT8_MAX; //brak wierzcho³ka

	class Solution
	{
	public:
		uinteger value; //wartoœæ, na pocz¹tku INF
		uinteger lastVertex; //wierzcho³ek, który "wyprowadza" podrozwi¹zanie do po³¹czenia z kolejnym
		Solution()
		{
			value = INF;
			lastVertex = V_INF;
		}
	};

	class SubsetSolution
	{
	public:
		Solution* solutions;
		uinteger size;
		uinteger from;

		SubsetSolution()
		{
			size = 0;
			solutions = nullptr;
			from = 0;
		}

		~SubsetSolution(void)
		{
			delete[] solutions;
			solutions = nullptr;
			best = nullptr;
		}

		Solution* getSolution(unsigned sol)
		{
			return solutions + sol;
		}
	};

	SubsetSolution* solutionsArray;

	SolutionSet(byte size)
	{
		this->size = size;
		unsigned requiredSize = 1 << (size - 1);
		solutionsArray = new SubsetSolution[requiredSize];
	}

	~SolutionSet(void)
	{
		delete[] solutionsArray;
	}

	SubsetSolution* getSolution(uinteger index)
	{
		return solutionsArray + index;
	}

private:
	byte size;
};