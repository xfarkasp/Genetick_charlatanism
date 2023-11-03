#include "Genetics.h"
#include "Gardener.h"
#include <memory>
#include <random>

Genetics::Genetics(std::vector<std::vector<int>> gardenState) {
	_currGen = 1;
	initFirstGen(gardenState);
};

void Genetics::initFirstGen(std::vector<std::vector<int>> gardenState){
	std::unique_ptr<Gardener> monk = std::make_unique<Gardener>(gardenState, _currGen);
	std::vector<Gene> firstGen;
	int rows[2] = { 0, gardenState.size() - 1 };
	int cols[2] = { 0, gardenState.at(0).size() - 1 };

	// Create a random number generator engine
	std::random_device rd;  // Used to seed the generator
	std::mt19937 gen(rd()); // Mersenne Twister engine

	for (size_t i = 0; i < gardenState.at(0).size(); i++) {
		//create a gene struct
		Gene currGene;
		// Define a random distribution for integers in a specified range (e.g., 1 to 100)
		std::uniform_int_distribution<int> distribution(1, 2);
		std::uniform_int_distribution<int> elementSelector(0, 1);
		std::uniform_int_distribution<int> randomCol(0, gardenState.at(0).size() - 1);
		std::uniform_int_distribution<int> randomRow(0, gardenState.size() - 1);

		int randomValue = distribution(gen);
		for (size_t j = 0; j < gardenState.at(0).size(); j++) {
			std::pair<int, int> randomStartPos;
			if (randomValue == 1) {

				//randomly pics top or bottom row
				randomStartPos.first = rows[elementSelector(gen)];
				//randomly pics a col to start
				randomStartPos.second = randomCol(gen);
			}
			else if (randomValue == 2) {
				//randomly pics top or bottom row
				randomStartPos.first = randomRow(gen);
				//randomly pics a col to start
				randomStartPos.second = cols[elementSelector(gen)];
			}
			currGene.startingPositions.push_back(randomStartPos);
		}
		
		firstGen.push_back(currGene);
	}
	_generations.push_back(firstGen);

}