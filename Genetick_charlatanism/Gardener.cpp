#include "Gardener.h"
#include <random>

Gardener::Gardener(std::vector<std::vector<int>> gardenState, unsigned int genNum) {
	_itNum = genNum;
	_deadCount = 0;
	_gardenState = gardenState;
	_gardenerPos.push_back(0);
	_gardenerPos.push_back(0);
}

bool Gardener::goUp() {
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenerPos.at(0) - 1 >= 0 && _gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) != 0) {
		_obstacle = true;
		return false;
	}

	//reached end of the garden
	if (_gardenerPos.at(0) - 1 <= 0) {
		_ringOut = true;
		if (_gardenerPos.at(0) - 1 >= 0)
			_gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) = _itNum;
		return true;
	}
	
	else {
		_lastAction = "UP";
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0) - 1).at(_gardenerPos.at(1)) = _itNum;
		_validMove = true;
		//printGarden();
		_gardenerPos.at(0)--;
	}
	
	
	return true;
}

bool Gardener::goDown() {
	// if there is an obsticle in the way down, return false to traverseGarden()
	if (_gardenerPos.at(0) + 1 < _gardenState.size() && _gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) != 0) {
		_obstacle = true;
		return false;
	}

	//reached end of the garden
	if (_gardenerPos.at(0) + 1 >= _gardenState.size() - 1) {
		_ringOut = true;
		if(_gardenerPos.at(0) + 1 <= _gardenState.size() - 1)
			_gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) = _itNum;
		return true;
	}
	
	else {
		_lastAction = "DOWN";
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0) + 1).at(_gardenerPos.at(1)) = _itNum;
		_validMove = true;
		//printGarden();
		_gardenerPos.at(0)++;
	}
	
	return true;
}

bool Gardener::goRight() {
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenerPos.at(1) + 1 < _gardenState.at(_gardenerPos.at(0)).size() && _gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) != 0) {
		_obstacle = true;
		return false;
	}

	//reached end of the garden
	if (_gardenerPos.at(1) + 1 >= _gardenState.at(_gardenerPos.at(0)).size() - 1) {
		_ringOut = true;
		if (_gardenerPos.at(1) + 1 <= _gardenState.at(_gardenerPos.at(0)).size() - 1)
			_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) = _itNum;
		return true;
	}
	
	else {
		_lastAction = "RIGHT";
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) + 1) = _itNum;
		_validMove = true;
		//printGarden();
		_gardenerPos.at(1)++;
	}
	
	return true;
}

bool Gardener::goLeft() {
	// if there is an obsticle in the way up, return false to traverseGarden()
	if (_gardenerPos.at(1) - 1 >= 0 &&_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) != 0) {
		_obstacle = true;
		return false;
	}

	//reached end of the garden
	if (_gardenerPos.at(1) - 1 <= 0) {
		_ringOut = true;
		if (_gardenerPos.at(1) - 1 >= 0)
			_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) = _itNum;
		return true;
	}
	
	else {
		_lastAction = "LEFT";
		// change empty position to the number of current movement iteration value, to visualize gardener movement
		_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1) - 1) = _itNum;
		_validMove = true;
		//printGarden();
		_gardenerPos.at(1)--;
	}
	
	
	return true;
}

void Gardener::obstacleHandler() {
	while (_validMove && !_ringOut) {
		_validMove = false;
		if (_lastAction != "UP" && goDown()) {
			while (goDown()) {
				if (_ringOut)
					return;
			}
		}
		else if (_lastAction != "DOWN" && goUp()) {
			while (goUp()) {
				if (_ringOut)
					return;
			}
		}
		else if (_lastAction != "LEFT" && goRight()) {
			while (goRight()) {
				if (_ringOut)
					return;
			}
		}
		else if (_lastAction != "RIGHT" && goLeft()) {
			while (goLeft()) {
				if (_ringOut)
					return;
			}
		}
	}
	if (!_ringOut) {
		//std::cout << " monk is trapped!" << std::endl;
		_deadCount++;
		_deadlock = true;
	}
}

std::vector<std::vector<int>> Gardener::traverse() {

	if (_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1)) != 0)
		return _gardenState;

	_gardenState.at(_gardenerPos.at(0)).at(_gardenerPos.at(1)) = _itNum;
	if (_gardenerPos.at(0) == 0)
		_lastAction = "DOWN";
	else if (_gardenerPos.at(0) == _gardenState.size()-1)
		_lastAction = "UP";
	else if (_gardenerPos.at(1) == _gardenState.at(_gardenerPos.at(0)).size() - 1)
		_lastAction = "LEFT";
	else if (_gardenerPos.at(1) == 0)
		_lastAction = "RIGHT";
	
	while (!_ringOut && !_deadlock) {
		//printGarden();

		if (_obstacle) {
			obstacleHandler();
		}

		else if (_gardenerPos.at(0) == 0)
			while (goDown()) {
				if (_ringOut)
					break;
			}

		else if (_gardenerPos.at(0) == _gardenState.size() - 1)
			while (goUp()) {
				if (_ringOut)
					break;
			}

		else if (_gardenerPos.at(1) == _gardenState.at(0).size() - 1)
			while (goLeft()) {
				if (_ringOut)
					break;
			}

		else if (_gardenerPos.at(1) == 0)
			while (goRight()) {
				if (_ringOut)
					break;
			}
		else
			break;
	}
	//printGarden();
	_obstacle = false;
	_ringOut = false;
	_deadlock = false;
	_validMove = true;
	_lastAction = " ";
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