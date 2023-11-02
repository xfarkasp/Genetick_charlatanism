#include "Genetics.h"
#include "Gardener.h"
#include <memory>

Genetics::Genetics(std::vector<std::vector<int>> gardenState) {
	_currGen = 1;
	initFirstGen(gardenState);
};

void Genetics::initFirstGen(std::vector<std::vector<int>> gardenState){
	std::unique_ptr<Gardener> monk = std::make_unique<Gardener>(gardenState, _currGen);
	std::vector<Gene> currentGen;
	// start from top
	for (size_t i = 0; i < gardenState.at(0).size(); i++) {
		Gene gen;
		gen.genNumber = _currGen;
		gen.gardenState = monk->traverse();
		currentGen.push_back(gen);
		//move monks starting position
		monk->setPosY(monk->getPosX() + 1);
		monk->setPosX(0);
		monk->setGarden(gardenState); // reset garden to get new variation
	}
}