#pragma once

#include <vector>
#include <map>

#include "IterableBitset.h"
#include "MobilityList.h"

class Range {
public:
	constexpr static int MAX_RANGE = 32;
	using DistanceSet = IterableBitset<MAX_RANGE>;

	MobilitySet _type;
	DistanceSet _range;

	Range();
	Range(std::vector<int> distances);
	Range(MobilityType type, std::vector<int> distances);
	Range(MobilitySet move, DistanceSet dist);

	constexpr bool hasDistance(int dist) const { //TODO(Torrey): remove magic numbers, rename this
		Expects(dist >= 0 && MAX_RANGE > dist);
		return _range[(dist + 9) / 10]; 
	}
	int maxRange() const {
		for (int i = 1; i <= MAX_RANGE; i++) {
			if (_range[MAX_RANGE - i]) {
				return (MAX_RANGE - i) * 10;
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