#pragma once

#include <vector>
#include <map>

#include "IterableBitset.h"
#include "MobilityList.h"

class Range {
public:
	constexpr static int MAX_RANGE = 32;
	constexpr static int MOVE_RATIO = 10;
	using DistanceSet = IterableBitset<MAX_RANGE>;

	MobilitySet _type;
	DistanceSet _range;

	Range();
	Range(std::vector<int> distances);
	Range(MobilityType type, std::vector<int> distances);
	Range(MobilitySet move, DistanceSet dist);

	constexpr bool hasDistance(int dist) const { 
		Expects(dist >= 0 && MAX_RANGE * MOVE_RATIO > dist);
		return _range[(dist + MOVE_RATIO - 1) / MOVE_RATIO]; 
	}
	int maxRange() const {
		for (int i = MAX_RANGE - 1; i >= 0; i--) {
			if (_range[i]) {
				return i * MOVE_RATIO;
			}
		}
		return 0;
	}

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