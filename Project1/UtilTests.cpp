#include <vector>
#include "IterableBitset.h"
#include "UtilTests.h"
#include "Enum.h"
#include "EnumContainer.h"

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

bool enumTest() {
	enum class myenum { A, B, C, D, ENUM_END };
	using MyEnum = Enum<myenum>;

	std::vector<int> expected { 0, 1, 2, 3 };
	std::vector<int> result;

	for (MyEnum e : MyEnum::list) {
		int e_pos = MyEnum::positionOf(e);
		result.push_back(e_pos);
		std::cout << e_pos << " ";
	}
	std::cout << std::endl;
	return expected == result;
}
