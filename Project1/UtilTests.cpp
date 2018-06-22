#include <vector>
#include <set>
#include <memory>
#include "IterableBitset.h"
#include "UtilTests.h"
#include "Enum.h"
#include "EnumContainer.h"
#include "UniquePtrIterator.h"

bool bitsetTest() {
	constexpr int size = 10;
	std::array<bool, size> init_array{true, true, false, true, false, true, false, false, false, true};
	std::vector<int> init_vec;
	for (int i = 0; i < size; ++i) {
		if (init_array[i]) {
			init_vec.push_back(i);
			
		}
	}

	IterableBitset<size> set1(init_array);
	IterableBitset<size> set2(init_vec);

	std::vector<int> result1;
	for (int i : set1) {
		result1.push_back(i);
		std::cout << i << " ";
	}
	std::cout << std::endl;

	std::vector<int> result2;
	for (int i : set2) {
		result2.push_back(i);
		std::cout << i << " ";
	}
	std::cout << std::endl;

	return init_vec == result1 && init_vec == result2;
}

bool enumTest1() {
	enum class myenum { A, B, C, D, ENUM_END };
	using MyEnum = Enum<myenum>;

	std::vector<int> expected { 0, 1, 2, 3 };
	std::vector<int> result;

	for (MyEnum e : MyEnum::list) {
		size_t e_pos = MyEnum::positionOf(e);
		result.push_back(e_pos);
		std::cout << e_pos << " ";
	}
	std::cout << std::endl;
	return expected == result;
}

bool enumTest2() {
	enum class myenum { A, B, C, D, ENUM_END };
	using MyEnum = Enum<myenum>;
	using EnumSet = EnumContainer<bool, MyEnum>;

	EnumSet none;

	std::set<MyEnum> a_s = { MyEnum::values::A };
	std::set<MyEnum> c_s = { MyEnum::values::C };
	std::set<MyEnum> d_s = { MyEnum::values::D };

	EnumSet a = a_s;
	EnumSet c = c_s;
	EnumSet d = d_s;

	std::set<MyEnum> ab_s = { MyEnum::values::A, MyEnum::values::B };
	std::set<MyEnum> cd_s = { MyEnum::values::C, MyEnum::values::D };
	std::set<MyEnum> da_s = { MyEnum::values::A, MyEnum::values::D };

	EnumSet ab = ab_s;
	EnumSet cd = cd_s;
	EnumSet da = da_s;

	std::set<MyEnum> bd_s = { MyEnum::values::B, MyEnum::values::D };
	EnumSet bd = bd_s;

	std::set<MyEnum> abc_s = { MyEnum::values::A, MyEnum::values::B, MyEnum::values::C };
	std::set<MyEnum> dab_s = { MyEnum::values::A, MyEnum::values::B, MyEnum::values::D };

	EnumSet abc = abc_s;
	EnumSet dab = dab_s;

	std::set<MyEnum> all_s = { MyEnum::values::A, MyEnum::values::B, MyEnum::values::C, MyEnum::values::D };

	EnumSet all = all_s;

	bool and_works = (((abc & d) == none) && ((da & ab) == a) && ((cd & c) == c));
	bool or_works = (((abc | d) == all) && ((da | ab) == dab) && ((cd | c) == cd));
	bool xor_works = (((abc ^ d) == all) && ((da ^ ab) == bd) && ((cd & c) == d));

	return and_works && or_works && xor_works;
}

bool enumTest() {
	return enumTest1() && enumTest2();
}

bool iterTest() {

	std::vector<int> result;
	std::vector<int> expected = { 1, 2, 3, 4 };

	std::vector<std::unique_ptr<int>> ints;
	
	ints.push_back(std::make_unique<int>(1));
	ints.push_back(std::make_unique<int>(2));
	ints.push_back(std::make_unique<int>(3));
	ints.push_back(std::make_unique<int>(4));

	std::cout << "Iterators: ";
	for (unique_ptr_iter<std::vector<std::unique_ptr<int>>::iterator, int> it = ints.begin(); it != ints.end(); ++it) {
		result.push_back(*it);
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
	return result == expected;
}