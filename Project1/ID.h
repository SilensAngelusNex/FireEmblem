#pragma once
#include <utility>
#include <map>
#include <queue>


class ID :
	private std::pair<size_t, size_t>{
private:
	using std::pair<size_t, size_t>::pair;
	using std::pair<size_t, size_t>::operator=;
	using std::pair<size_t, size_t>::swap;
	using std::pair<size_t, size_t>::first;
	using std::pair<size_t, size_t>::second;
public:
	friend class Grid;
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
};

using CostID = std::pair<int, ID>;
using id_cost_map = std::map<ID, CostID>;

//TODO(Torrey): Place these somewhere private in GridMap
inline auto comp = [](const CostID& lhs, const CostID& rhs) { return lhs.first < rhs.first; };
using PathQueue = std::priority_queue<CostID, std::vector<CostID>, decltype (comp)>;
