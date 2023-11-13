#include "Genetics.h"
#include "Gardener.h"
#include <memory>
#include <random>

Genetics::Genetics(std::vector<std::vector<int>> gardenState) {
	_gardenState = gardenState;
	evolution();
};

void Genetics::initFirstGen(){
	
	std::vector<Gene> firstGen;
	int rows[2] = { 0, _gardenState.size() - 1 };
	int cols[2] = { 0, _gardenState.at(0).size() - 1 };

	// Create a random number generator engine
	std::random_device rd;  // Used to seed the generator
	std::mt19937 gen(rd()); // Mersenne Twister engine

	for (size_t i = 0; i < POP_SIZE; i++) {
		//create a gene struct
		Gene currGene;
		currGene.id = geneNumbering++;
		// Define a random distribution for integers in a specified range (e.g., 1 to 100)
		std::uniform_int_distribution<int> distribution(1, 2);
		std::uniform_int_distribution<int> elementSelector(0, 1);
		std::uniform_int_distribution<int> randomCol(0, _gardenState.at(0).size() - 1);
		std::uniform_int_distribution<int> randomRow(0, _gardenState.size() - 1);

		int randomValue = distribution(gen);
		for (size_t j = 0; j < _gardenState.at(0).size() * 2; j++) {
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
		currGene.fitnessValue = fitnessFunction(currGene);
		firstGen.push_back(currGene);
	}
	_generations.push_back(firstGen);
}

int Genetics::fitnessFunction(Gene gen) {
	int score = 0;
	std::vector<std::vector<int>> changedGarden;
	std::unique_ptr<Gardener> monk = std::make_unique<Gardener>(_gardenState, 1);
	for (auto it : gen.startingPositions) {
		monk->setPositions(it.first, it.second);
		changedGarden = monk->traverse();
	}
	
	int notVisitedCount = 0;
	for (auto& it : changedGarden) {
		for (auto& element : it) {
			if (element > 0)
				score++;
			if (element == 0)
				notVisitedCount++;
		}
	}
	if (notVisitedCount == 0 && monk->getDeadCount() == 0) {
		std::cout << "solution found in gen: " << _generations.size() << std::endl;
		monk->printGarden();
		exit(0);
	}

	score -= monk->getDeadCount() * 10;
	return score;
}

Gene Genetics::roullete(std::vector<Gene> generation) {
	// Calculate the total fitness of the population
	int totalFitness = 0;
	for (const auto& individual : generation) {
		totalFitness += individual.fitnessValue;
	}

	// Generate a random number between 0 and the total fitness
	std::random_device rd;  // Used to seed the generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<int> distribution(0, totalFitness);
	int randInt = distribution(gen);

	// Select an individual based on the random value
	int cumulativeFitness = 0;
	for (const auto& individual : generation) {
		cumulativeFitness += individual.fitnessValue;
		if (cumulativeFitness >= randInt) {
			return individual;
		}
	}
}

void Genetics::evolution() {
	initFirstGen(); // initialize first generation of genes
	for (size_t i = 0; i < MAX_GENERATIONS; i++) {
		createNewGen(_generations.at(i));
	}
}

// Comparison function to sort genes by fitness (from best to worst)
bool compareByFitness(const Gene& gene1, const Gene& gene2) {
	return gene1.fitnessValue > gene2.fitnessValue; // Sorting in descending order
}

void Genetics::createNewGen(std::vector<Gene> generation) {
	std::vector<Gene> newGeneration;
	std::sort(generation.begin(), generation.end(), compareByFitness);
	newGeneration.push_back(generation.at(0));
	size_t originalGenSize = generation.size();
	for (size_t i = 0; i < 2; i++) {
		Gene chosenOne = roullete(generation);
		newGeneration.push_back(chosenOne);

		// Find and remove the struct based on the condition
		for (auto it = generation.begin(); it != generation.end(); ++it) {
			if (it->id == chosenOne.id) {
				generation.erase(it);
				break; 
			}
		}
		
	}
	std::sort(newGeneration.begin(), newGeneration.end(), compareByFitness);
	
	std::vector<Gene> crossedGenes;
	std::pair<Gene, Gene> offsprings;

	offsprings = crossGenes(newGeneration.at(0), newGeneration.at(1));
	crossedGenes.push_back(offsprings.first);
	crossedGenes.push_back(offsprings.second);
	
	std::random_device rd;  // Used to seed the generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<int> distribution(0, newGeneration.size() - 1);
	for (size_t i = 2; i < (POP_SIZE /2); i++) {
		int randGen1 = distribution(gen);
		int randGen2 = distribution(gen);
		while (randGen1 != randGen2) {
			randGen2 = distribution(gen);
		}

		offsprings = crossGenes(newGeneration.at(randGen1), newGeneration.at(randGen2));
		crossedGenes.push_back(offsprings.first);
		crossedGenes.push_back(offsprings.second);
	}

	for (auto& it : crossedGenes)
		newGeneration.push_back(it);

	for (auto& it : newGeneration) {
		mutateGene(it,0.1);
		it.id = geneNumbering++;
		it.genNumber = _generations.size();
		it.fitnessValue = fitnessFunction(it);
		
	}
	_generations.push_back(newGeneration);
}


std::pair<Gene, Gene> Genetics::crossGenes(Gene parent1, Gene parent2) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(1, parent1.startingPositions.size() - 1); // Choose a random crossover point

	int crossoverPoint = distribution(gen);

	Gene offspring1, offspring2;

	//first half of crossing
	for (size_t i = 0; i < crossoverPoint; i++) {
		offspring1.startingPositions.push_back(parent1.startingPositions.at(i));
		offspring2.startingPositions.push_back(parent2.startingPositions.at(i));
	}
	//second half of crossing
	for (size_t i = 0; i < (parent1.startingPositions.size()) - crossoverPoint; i++) {
		offspring1.startingPositions.push_back(parent2.startingPositions.at(i));
		offspring2.startingPositions.push_back(parent1.startingPositions.at(i));
	}
	
	return std::make_pair(offspring1, offspring2);
}

void Genetics::mutateGene(Gene& gene, double mutationRate) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	for (auto& movement : gene.startingPositions) {
		if (distribution(gen) < mutationRate) {
			// Mutate the movement (e.g., change it to a random valid movement)

			int rows[2] = { 0, _gardenState.size() - 1 };
			int cols[2] = { 0, _gardenState.at(0).size() - 1 };

			// Create a random number generator engine
			std::random_device rd;  // Used to seed the generator
			std::mt19937 gen(rd()); // Mersenne Twister engine

			// Define a random distribution for integers in a specified range (e.g., 1 to 100)
			std::uniform_int_distribution<int> distribution(1, 2);
			std::uniform_int_distribution<int> elementSelector(0, 1);
			std::uniform_int_distribution<int> randomCol(0, _gardenState.at(0).size() - 1);
			std::uniform_int_distribution<int> randomRow(0, _gardenState.size() - 1);

			int randomValue = distribution(gen);
				
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

			movement = randomStartPos; // Implement getRandomValidMovement() as needed
		}
	}
}