#include "Gardener.h"

Gardener::Gardener(std::vector<std::vector<int>> gardenState, unsigned int genNum) {
	_genNum = genNum;
	_gardenState = gardenState;
	_gardenerPos.push_back(0);
	_gardenerPos.push_back(0);
}

bool Gardener::goUp() {
	//reached end of the garden
	std::cout << (_gardenerPos.at(0) - 1) << std::endl;
	if (_gardenerPos.at(0) - 1 <= 0) {
		_ringOut = true;
		_gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) = _genNum;
		return false;
	}
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) != 0)
		return false;
	else {
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) = _genNum;
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
		_gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) = _genNum;
		return false;
	}
	// if there is an obsticle in the way down, return false to traverseGarden()
	if (_gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) != 0)
		return false;
	else {
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) = _genNum;
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
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) = _genNum;
		return false;
	}
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) != 0)
		return false;
	else {
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) = _genNum;
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
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) = _genNum;
		return false;
	}
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) != 0)
		return false;
	else {
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) = _genNum;
		printGarden();
	}
	
	_gardenerPos.at(1)--;
	return true;
}

std::vector<std::vector<int>> Gardener::traverse() {

	_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1)) = _genNum;

	while (_ringOut != true) {
		printGarden();

		if (_gardenerPos.at(0) == 0)
			while (goDown())
				continue;
			
		else if (_gardenerPos.at(0) == _gardenState.size() - 1)
			while(goUp())
				continue;

		else if (_gardenerPos.at(1) == _gardenState.at(0).size() - 1)
			while(goLeft())
				continue;

		else if (_gardenerPos.at(1) == 0)
			while(goRight())
				continue;
	}
	printGarden();
	_ringOut = false;
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