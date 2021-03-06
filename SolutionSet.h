#pragma once
#include <iostream>
#include <bitset>

typedef uint8_t ubyte;
typedef int8_t byte;
typedef int32_t integer;
typedef uint32_t uinteger;

class SolutionSet
{
public:
	static const uinteger INF = UINT32_MAX; //INF - zazwyczaj oznacza brak krawędzi
	static const ubyte V_INF = UINT8_MAX; //brak wierzchołka

	class Solution
	{
	public:
		uinteger value; //wartość, na początku INF
		uinteger lastVertex; //wierzchołek, który "wyprowadza" podrozwiązanie do połączenia z kolejnym
		Solution()
		{
			value = INF;
			lastVertex = V_INF;
		}
	};

	Solution* solutionsArray;

	SolutionSet(byte size)
	{
		this->size = size;
		auto requiredSize = 1 << (size - 1);
		solutionsArray = new Solution[requiredSize];
	}

	~SolutionSet(void)
	{
		delete[] solutionsArray;
	}

	Solution* getSolution(uinteger index)
	{
		return solutionsArray + index;
	}
	
private:
	byte size;
};
