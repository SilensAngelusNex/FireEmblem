#include <iostream>
#include <memory>

#include "Tests.h"
#include "Dice.h"
#include "FairDice.h"
#include "ListDice.h"


bool test::runDiceTest() {
	/*
	std::unique_ptr<Dice<100>> fair = std::make_unique<FairDice<100>>();
	std::vector<int> l{ 1,2,3,4,15,6 };
	std::unique_ptr<Dice<100>> fixed = std::make_unique<ListDice<100>>(l);

	std::cout << "Fair:" << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << fair->roll();
		if (i != 9) {
			std::cout << ", ";
		}
		else {
			std::cout << std::endl;
		}
	}

	std::cout << "Fixed:" << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << fixed->roll();
		if (i != 9) {
			std::cout << ", ";
		}
		else {
			std::cout << std::endl;
		}
	}
	*/

	return true;
}