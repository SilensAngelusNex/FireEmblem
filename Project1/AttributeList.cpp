#include <iostream>

#include "AttributeList.h"


bool runAttributeListTests() {
	bool last_passed = true;
	bool all_passed = true;

	//Test constructors
	AttributeList::array init = { 0, 1, 2, 3, 4, 5, 6, 7 };
	AttributeList f;
	AttributeList a(init);
	AttributeList b(a);

	for (AttribType j : AttribType::list) {
		int i = j.pos();
		if ((a[j] != i) || (b[j] != i) || (f[j] != 0)) {
			last_passed = false;
			if (a[j] != i) {
				std::cout << "Array constructor failed." << std::endl;
			}
			if (b[j] != i) {
				std::cout << "Ref constructor failed." << std::endl;
			}
			if (f[j] != 0) {
				std::cout << "Default constructor failed." << std::endl;
			}
		}
	}

	if (last_passed) {
		std::cout << "Constructors passed." << std::endl;
}
	all_passed = all_passed && last_passed;
	last_passed = true;

	//Test arithmetic
	AttributeList c = a + b;
	AttributeList d = a - b;
	AttributeList e = c - a;

	for (AttribType j : AttribType::list) {
		int i = j.pos();
		if ((c[j] != 2 * i) || (d[j] != 0 * i) || (e[j] != i)) {
			last_passed = false;
			if (c[j] != 2 * i) {
				std::cout << "Addition failed." << std::endl;
			}
			if (d[j] != 0 * i) {
				std::cout << "Subtraction failed." << std::endl;
			}
			if (e[j] != i) {
				std::cout << "Addition and/or subtraction failed." << std::endl;
			}
		}
	}

	if (last_passed) {
		std::cout << "Arithmetic passed." << std::endl;
}
	all_passed = all_passed && last_passed;
	last_passed = true;

	//Test equality checks
	if ((f != d) || (d != f)) {
		last_passed = false;
		std::cout << "Equality check A failed." << std::endl;
	}
	if ((e != b) || (b != e)) {
		last_passed = false;
		std::cout << "Equality check B failed." << std::endl;
	}
	if (c.operator!=(c)) {
		last_passed = false;
		std::cout << "Equality check C failed." << std::endl;
	}
	if ((a != b) || (b != a)) {
		last_passed = false;
		std::cout << "Equality check D failed." << std::endl;
	}
	if ((a == c) || (c == a)) {
		last_passed = false;
		std::cout << "Equality check E failed." << std::endl;
	}
	if ((b == d) || (d == b)) {
		last_passed = false;
		std::cout << "Equality check F failed." << std::endl;
	}
	if (last_passed) {
		std::cout << "Equality checks passed." << std::endl;
}
	all_passed = all_passed && last_passed;

	return all_passed;
}