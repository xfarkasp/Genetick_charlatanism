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
	void setGenNum(int genNum) { _genNum = genNum; }
	void setPosX(int x) { _gardenerPos.at(0) = x; }
	int getPosX() { return _gardenerPos.at(0); }
	void setPosY(int y) { _gardenerPos.at(1) = y; }
	int getPosY() { return _gardenerPos.at(1); }
	void setGarden(std::vector<std::vector<int>> gardenState) { _gardenState = gardenState; }

private:
	std::vector<std::vector<int>> _gardenState;
	std::vector<unsigned int> _gardenerPos; // [x, y]
	unsigned int _genNum;
	bool _ringOut = false;
};