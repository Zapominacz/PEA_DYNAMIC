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
	static const uinteger INF = UINT32_MAX; //INF - zazwyczaj oznacza brak krawêdzi
	static const ubyte V_INF = UINT8_MAX; //brak wierzcho³ka

	class Solution
	{
	public:
		uinteger value; //wartoœæ, na pocz¹tku INF
		ubyte lastVertex; //wierzcho³ek, który "wyprowadza" podrozwi¹zanie do po³¹czenia z kolejnym
		Solution()
		{
			value = INF;
			lastVertex = V_INF;
		}

		~Solution(void)
		{
			printf("loL?");
		}
	};

	Solution* solutionsArray;

	SolutionSet(byte size)
	{
		this->size = size;
		auto requiredSize = ((1 << (size - 1)) - 1);
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
