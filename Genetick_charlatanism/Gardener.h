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
	void setGenNum(int genNum) { _itNum = genNum; }
	void setPosX(int x) { _gardenerPos.at(0) = x; }
	int getPosX() { return _gardenerPos.at(0); }
	void setPosY(int y) { _gardenerPos.at(1) = y; }
	int getPosY() { return _gardenerPos.at(1); }
	void setPositions(int x, int y) {
		_gardenerPos.at(0) = x; _gardenerPos.at(1) = y;
	}
	void setGarden(std::vector<std::vector<int>> gardenState) { _gardenState = gardenState; }
	void obstacleHandler();

private:
	std::vector<std::vector<int>> _gardenState;
	std::vector<unsigned int> _gardenerPos; // [x, y]
	unsigned int _itNum;
	bool _ringOut = false;
	bool _obstacle = false;
};