#pragma once

#include <vector>
#include <map>

#include "IterableBitset.h"
#include "MobilityList.h"

class RangeUtil {
public:
	constexpr static int MAX_RANGE = 32;

	using Distances = IterableBitset<MAX_RANGE>;
	using Movement = MobilityList<bool>;
};

class Range : protected RangeUtil {
public:
	Movement _type;
	Distances _range;

	Range();
	Range(std::vector<int> distances);
	Range(MobilityType type, std::vector<int> distances);
	Range(Movement move, Distances dist);

	bool operator==(const Range& rhs) const;
	bool operator!=(const Range& rhs) const;
	bool operator<=(const Range& rhs) const;
	bool operator>=(const Range& rhs) const;
	bool operator<(const Range& rhs) const;
	bool operator>(const Range& rhs) const;

	auto operator[](MobilityType t);
	bool operator[](MobilityType t) const;

	auto operator[](size_t distance);
	bool operator[](size_t distance) const;
};