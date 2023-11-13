#pragma once
#include <iostream>
#include <vector>

class Gardener {
public:
	Gardener(std::vector<std::vector<int>> gardenState, unsigned int genNum);
	bool goUp();
	bool goDown();
	bool goRight();
	bool goLeft();
	std::vector<std::vector<int>> traverse();
	void printGarden();
	void setPositions(int x, int y) {
		_gardenerPos.at(0) = x; _gardenerPos.at(1) = y;
	}
	void obstacleHandler();
	int getDeadCount(){ return _deadCount; }

private:
	std::vector<std::vector<int>> _gardenState;
	std::vector<int> _gardenerPos; // [x, y]
	unsigned int _itNum;
	int _deadCount;
	bool _ringOut = false;
	bool _obstacle = false;
	bool _deadlock = false;
	bool _validMove = true;
	std::string _lastAction = " ";
};