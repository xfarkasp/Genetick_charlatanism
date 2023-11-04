#pragma once
#include <vector>

struct Gene
{
	int id;
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
	std::pair<Gene, Gene> crossGenes(Gene gen1, Gene gen2);
	void initFirstGen();
	Gene roullete(std::vector<Gene> generation);
	void evolution();
	void createNewGen(std::vector<Gene> generation);
	void mutateGene(Gene& gene, double mutationRate);

private:
	int _currGen;
	const size_t MAX_GENERATIONS = 10000000;
	std::vector<std::vector<Gene>> _generations;
	std::vector<std::vector<int>> _gardenState;
	int geneNumbering = 0;
};