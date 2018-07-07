#pragma once
#include <map>
#include <sstream>
#include "logic_pair.h"

class ID :	protected logic_pair<size_t, size_t> {
private:

	using logic_pair<size_t, size_t>::logic_pair;
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
		return a || (c && b);
	}
	bool operator>(const ID& other) const {
		bool a = first > other.first;
		bool b = second > other.second;
		bool c = first == other.first;
		return a || (c && b);
	}
	bool operator>=(const ID& other) const {
		bool a = first > other.first;
		bool b = second < other.second;
		bool c = first == other.first;
		return a || (c && !b);
	}
	bool operator<=(const ID& other) const {
		bool a = first < other.first;
		bool b = second > other.second;
		bool c = first == other.first;
		return a || (c && !b);
	}
	
	/*
	using logic_pair<size_t, size_t>::operator==;
	using logic_pair<size_t, size_t>::operator!=;
	using logic_pair<size_t, size_t>::operator<;
	using logic_pair<size_t, size_t>::operator>;
	using logic_pair<size_t, size_t>::operator<=;
	using logic_pair<size_t, size_t>::operator>=;
	*/

	//FOR TESTING REMOVE FROM FINAL BUILD
	friend std::ostream& operator<<(std::ostream &strm, const ID& a) {
		return strm << "[" << a.first << "," << a.second << "]";
	}
	friend class Grid;
	//friend class logic_pair<size_t, size_t>;
};

using CostID = logic_pair<int, ID>;


