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
	static const uinteger INF = UINT32_MAX; //INF - zazwyczaj oznacza brak kraw�dzi
	static const ubyte V_INF = UINT8_MAX; //brak wierzcho�ka

	class Solution
	{
	public:
		uinteger value; //warto��, na pocz�tku INF
		uinteger lastVertex; //wierzcho�ek, kt�ry "wyprowadza" podrozwi�zanie do po��czenia z kolejnym
		Solution()
		{
			value = INF;
			lastVertex = V_INF;
		}
	};


	class SolutionListItem
	{
	public:
		SolutionListItem* next;
		Solution* item;
		ubyte vertex;

		SolutionListItem()
		{
			next = nullptr;
			item = nullptr;
			vertex = V_INF;
		}

		~SolutionListItem()
		{
			delete item;
			item = nullptr;
			next = nullptr;
		}
	};

	SolutionListItem* solutionsArray;

	SolutionSet(byte size)
	{
		this->size = size;
		auto requiredSize = 1 << (size - 1);
		solutionsArray = new SolutionListItem[requiredSize];
	}

	~SolutionSet(void)
	{
		delete[] solutionsArray;
	}

	Solution* getSolution(uinteger map, ubyte vertex)
	{
		SolutionListItem* item = solutionsArray + map;
		SolutionListItem* prev = nullptr;
		while(item != nullptr && item->vertex != vertex)
		{
			prev = item;
			item = item->next;
		}
		if(item == nullptr)
		{
			SolutionListItem* newItem = new SolutionListItem();
			newItem->vertex = vertex;
			newItem->item = new Solution();
			prev->next = newItem;
			item = newItem;
		}
		return item->item;
	}
private:
	byte size;
};
