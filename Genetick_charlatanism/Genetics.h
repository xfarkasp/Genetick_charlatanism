#pragma once
#include <vector>

struct Gene
{
	bool elitism;
	int genNumber;
	int fitnessValue;
	//std::vector<std::vector<int>> gardenState;
	std::vector<std::pair<int, int>> startingPositions;
};

class Genetics {
public:
	Genetics(std::vector<std::vector<int>> gardenState);
	int fitnessFunction(Gene gen);
	void mutateGene(Gene gen);
	void crossGenes(Gene gen1, Gene gen2);
	void initFirstGen();

private:
	int _currGen;
	std::vector<std::vector<Gene>> _generations;
	std::vector<std::vector<int>> _gardenState;
};