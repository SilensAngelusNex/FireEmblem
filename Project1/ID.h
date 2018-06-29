#pragma once
#include <map>

#include "logic_pair.h"

class ID :
	private std::pair<size_t, size_t>{
private:

	using std::pair<size_t, size_t>::pair;
	using std::pair<size_t, size_t>::operator=;
	using std::pair<size_t, size_t>::swap;
	using std::pair<size_t, size_t>::first;
	using std::pair<size_t, size_t>::second;
public:
	bool operator==(const ID& other) const {
		return first == other.first && second == other.second;
	}

	bool operator!=(const ID& other) const {
		return first != other.first || second != other.second;
	}

	bool operator<(const ID& other) const {
		bool a = first < other.first;
		bool b = second < other.second;
		bool c = first == other.first;
		return a | (c && b);
	}
	bool operator>(const ID& other) const {
		bool a = first > other.first;
		bool b = second > other.second;
		bool c = first == other.first;
		return a | (c && b);
	}
	bool operator>=(const ID& other) const {
		bool a = first < other.first;
		bool b = second < other.second;
		bool c = first == other.first;
		return !(a | (c && b));
	}
	bool operator<=(const ID& other) const {
		bool a = first > other.first;
		bool b = second > other.second;
		bool c = first == other.first;
		return !(a | (c && b));
	}

	friend class Grid;
};

using CostID = logic_pair<int, ID>;
using id_cost_map = std::map<ID, CostID>;


