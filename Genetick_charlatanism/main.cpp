#include <iostream>
#include <vector>
#include "Gardener.h"
#include "Genetics.h"
using namespace std;

int main() {

	std::vector<std::vector<int>> garden;
	/*for (size_t i = 0; i < 10; i++) {
		std::vector<int> row;
		for (size_t j = 0; j < 12; j++) {
			if (i == 1 && j == 5 ||
				i == 2 && j == 1 ||
				i == 3 && j == 4 ||
				i == 4 && j == 2 ||
				i == 6 && j == 8 ||
				i == 6 && j == 9) {
				row.push_back(-1);
				std::cout << row.at(j) << " ";
			}
			else {
				row.push_back(0);
				std::cout << row.at(j) << "  ";
			}
		}
		std::cout << std::endl;
		garden.push_back(row);
	}*/
	for (size_t i = 0; i < 6; i++) {
		std::vector<int> row;
		for (size_t j = 0; j < 10; j++) {
			if (i == 3 && j == 4 ||
				i == 3 && j == 5) {
				row.push_back(-1);
				std::cout << row.at(j) << " ";
			}
			else {
				row.push_back(0);
				std::cout << row.at(j) << "  ";
			}
		}
		std::cout << std::endl;
		garden.push_back(row);
	}
	std::cout << std::endl;

	std::unique_ptr<Genetics> genetics = std::make_unique<Genetics>(garden);


}