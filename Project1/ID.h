#pragma once
#include <utility>
#include <map>
#include <queue>

template<typename T1, typename T2>
class logic_pair :
	public std::pair<T1, T2> {
public:
	using std::pair<T1, T2>::pair;
	using std::pair<T1, T2>::operator=;
	using std::pair<T1, T2>::swap;
	using std::pair<T1, T2>::first;
	using std::pair<T1, T2>::second;

	bool operator==(const logic_pair& other) const {
		return first == other.first && second == other.second;
	}

	bool operator!=(const logic_pair& other) const {
		return first != other.first || second != other.second;
	}

	bool operator<(const logic_pair& other) const {
		bool a = first < other.first;
		bool b = second < other.second;
		bool c = first == other.first;
		return a | (c && b);
	}
	bool operator>(const logic_pair& other) const {
		bool a = first > other.first;
		bool b = second > other.second;
		bool c = first == other.first;
		return a | (c && b);
	}

	bool operator>=(const logic_pair& other) const {
		bool a = first < other.first;
		bool b = second < other.second;
		bool c = first == other.first;
		return !(a | (c && b));
	}
	bool operator<=(const logic_pair& other) const {
		bool a = first > other.first;
		bool b = second > other.second;
		bool c = first == other.first;
		return !(a | (c && b));
	}

};

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


