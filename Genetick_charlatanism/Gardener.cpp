#include "Gardener.h"
#include <random>

Gardener::Gardener(std::vector<std::vector<int>> gardenState, unsigned int genNum) {
	_itNum = genNum;
	_gardenState = gardenState;
	_gardenerPos.push_back(0);
	_gardenerPos.push_back(0);
}

bool Gardener::goUp() {
	//reached end of the garden
	std::cout << (_gardenerPos.at(0) - 1) << std::endl;
	if (_gardenerPos.at(0) - 1 <= 0) {
		_ringOut = true;
		_gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) = _itNum;
		return false;
	}
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) != 0) {
		_obstacle = true;
		return false;
	}
	else {
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) = _itNum;
		printGarden();
	}
	
	_gardenerPos.at(0)--;
	return true;
}

bool Gardener::goDown() {
	//reached end of the garden
	std::cout << (_gardenerPos.at(0) + 1) << std::endl;
	if (_gardenerPos.at(0) + 1 >= _gardenState.size() - 1) {
		_ringOut = true;
		_gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) = _itNum;
		return false;
	}
	// if there is an obsticle in the way down, return false to traverseGarden()
	if (_gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) != 0) {
		_obstacle = true;
		return false;
	}
	else {
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) = _itNum;
		printGarden();
	}
	
	_gardenerPos.at(0)++;
	return true;
}

bool Gardener::goRight() {
	//reached end of the garden
	std::cout << (_gardenerPos.at(1) + 1) << std::endl;
	if (_gardenerPos.at(1) + 1 >= _gardenState.at(_gardenerPos.at(0)).size() - 1) {
		_ringOut = true;
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) = _itNum;
		return false;
	}
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) != 0) {
		_obstacle = true;
		return false;
	}
	else {
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) = _itNum;
		printGarden();
	}
	
	_gardenerPos.at(1)++;

	return true;
}

bool Gardener::goLeft() {
	//reached end of the garden
	std::cout << (_gardenerPos.at(1) - 1) << std::endl;
	if (_gardenerPos.at(1) - 1 <= 0) {
		_ringOut = true;
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) = _itNum;
		return false;
	}
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) != 0) {
		_obstacle = true;
		return false;
	}
	else {
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) = _itNum;
		printGarden();
	}
	
	_gardenerPos.at(1)--;
	return true;
}

void Gardener::obstacleHandler() {
	// Create a random number generator engine
	std::random_device rd;  // Used to seed the generator
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<int> directionRandomizer(0, 3);
	int randomValue = directionRandomizer(gen);

	if (randomValue == 0) {
		while (goDown())
			continue;
	}
	else if (randomValue == 1) {
		while (goUp())
			continue;
	}
	else if (randomValue == 2) {
		while (goRight())
			continue;
	}
	else if (randomValue == 3) {
		while (goLeft())
			continue;
	}
	else {
		std::cout << " monk is trapped!";
	}
}

std::vector<std::vector<int>> Gardener::traverse() {

	if (_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1)) != 0)
		return _gardenState;

	_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1)) = _itNum;
	
	while (_ringOut != true) {
		printGarden();

		if (_obstacle) {
			obstacleHandler();
		}

		else if (_gardenerPos.at(0) == 0)
			while (goDown())
				continue;

		else if (_gardenerPos.at(0) == _gardenState.size() - 1)
			while (goUp())
				continue;

		else if (_gardenerPos.at(1) == _gardenState.at(0).size() - 1)
			while (goLeft())
				continue;

		else if (_gardenerPos.at(1) == 0)
			while (goRight())
				continue;
		else
			break;
	}
	printGarden();
	_obstacle = false;
	_ringOut = false;
	_itNum++;
	return _gardenState;
}

void Gardener::printGarden() {
	for (auto rows : _gardenState) {
		for (auto element : rows) {
			if (element == -1 || element > 9)
				std::cout << element << " ";
			else
				std::cout << element << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}