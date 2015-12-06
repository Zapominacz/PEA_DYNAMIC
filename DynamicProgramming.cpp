#pragma once

#include <iostream>
#include <fstream>
#include "Map.h"
#include "TspDp.h"
#include "MapLoader.h"
#include "MapGenerator.h"
#include <ctime>

const bool TEST = false;

void test() 
{
	using namespace std;
	MapGenerator* generator = new MapGenerator();
	unsigned sizes[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	unsigned sizesLenght = 17;
	unsigned repeats = 100;
	ofstream file;
	file.open("results.txt", ios_base::app);
	for (unsigned size = 0; size < sizesLenght; size++)
	{
		double average = 0;
		for (unsigned repeat = 0; repeat < repeats; repeat++)
		{
			Map* map = generator->generate(sizes[size]);
			TspDp* dp = new TspDp(map);
			clock_t begin = clock();
			ubyte* result = dp->solve();
			clock_t end = clock();
			unsigned sum = 0;
			for (ubyte vertex = 0; vertex < map->size - 1; vertex++)
			{
				unsigned weight = map->matrix[result[vertex]][result[vertex + 1]];
				sum += weight;
			}
			unsigned weight = map->matrix[result[map->size - 1]][result[0]];
			sum += weight;
			cout << "Suma: " << sum << endl;
			double elapsed_secs = double(end - begin);
			average += elapsed_secs;
			delete dp;
		}
		average /= sizesLenght;
		file << sizes[size] << '\t' << average << endl;
	}
	file.close();
	delete generator;
}

void presentation()
{
	using namespace std;
	cout << "ATSP Dynamicznie" << endl;
	MapLoader* loader = new MapLoader();
	while (true)
	{
		Map* map = loader->load();
		if (map != nullptr) {
			TspDp* dp = new TspDp(map);
			ubyte* result = dp->solve();
			cout << "Wynik: " << endl;
			unsigned sum = 0;
			for (ubyte vertex = 0; vertex < map->size - 1; vertex++)
			{
				unsigned weight = map->matrix[result[vertex]][result[vertex + 1]];
				sum += weight;
				cout << static_cast<int>(result[vertex]) << " -(" << weight << ")-> ";
			}
			unsigned weight = map->matrix[result[map->size - 1]][result[0]];
			sum += weight;
			cout << static_cast<int>(result[map->size - 1]) << " -(" << weight << ")-> " << static_cast<int>(result[0]) << endl;
			cout << "Suma: " << sum << endl;
			delete dp;
		}
	}
	delete loader;
}

int main(void) {
	if (TEST) {
		test();
	} 
	else {
		presentation();
	}
	return 0;
}