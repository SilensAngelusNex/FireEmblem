#include <iostream>

#include "Tests.h"
#include "AttributeList.h"
#include "Enum.h"
#include "WeaponList.h"


void enumTest() {
	enum class myenum { A, B, C, D, ENUM_END };
	using MyEnum = Enum<myenum>;

	for (MyEnum e : MyEnum::list) {
		std::cout << MyEnum::positionOf(e) << std::endl;
	}
}

int main(int  /*argc*/, char ** /*argv*/) {

	if (runAttributeListTests()) {
		std::cout << "All passed!" << std::endl;
	}

	if (runWeaponListTests()) {
		std::cout << "Passed!" << std::endl;
	}

	if (test::runDiceTest()) {
		std::cout << "All passed!" << std::endl;
	}
	if (test::runUnitTest()) {
		std::cout << "All passed!" << std::endl;
	}
	enumTest();
	return 0;
}