#include <iostream>

#include "Tests.h"
#include "UtilTests.h"
#include "AttributeList.h"
#include "WeaponList.h"

int main(int  /*argc*/, char ** /*argv*/) {

	if (runAttributeListTests()) {
		std::cout << "AttributeList passed!" << std::endl;
	}
	if (runWeaponListTests()) {
		std::cout << "WeaponList passed!" << std::endl;
	}
	if (test::runDiceTest()) {
		std::cout << "Dice passed!" << std::endl;
	}
	if (test::runUnitTest()) {
		std::cout << "Unit passed!" << std::endl;
	}
	if (enumTest()) {
		std::cout << "Enum passed!" << std::endl;
	}
	if (bitsetTest()) {
		std::cout << "Bitset passed!" << std::endl;
	}
	if (test::runMapTest()) {
		std::cout << "All passed!" << std::endl;
	}
	enumTest();
	return 0;
}