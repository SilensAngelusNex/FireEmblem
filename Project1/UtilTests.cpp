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

	IterableBitset<size> set(init_array);

	std::vector<int> result;
	for (int i : set) {
		result.push_back(i);
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return init_vec == result;
}

bool enumTest() {
	enum class myenum { A, B, C, D, ENUM_END };
	using MyEnum = Enum<myenum>;

	std::vector<int> expected { 1, 2, 3, 4 };
	std::vector<int> result;

	for (MyEnum e : MyEnum::list) {
		int e_pos = MyEnum::positionOf(e);
		result.push_back(e_pos);
		std::cout << e_pos << " ";
	}
	std::cout << std::endl;
	return expected == result;
}
