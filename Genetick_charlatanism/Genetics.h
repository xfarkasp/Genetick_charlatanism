#pragma once
#include <vector>

struct Gene
{
	bool elitism;
	int genNumber;
	int value;
	std::vector<std::vector<int>> gardenState;
};

class Genetics {
public:
	Genetics(std::vector<std::vector<int>> gardenState);
	int fitnessFunction(std::vector<std::vector<int>> gardenState);
	void mutateGene(Gene gen);
	void crossGenes(Gene gen1, Gene gen2);
	void initFirstGen(std::vector<std::vector<int>> gardenState);

private:
	int _currGen;
	std::vector<std::vector<Gene>> _generations;
};