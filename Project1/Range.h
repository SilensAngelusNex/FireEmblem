#pragma once

#include <vector>
#include <map>

#include "IterableBitset.h"
#include "MobilityList.h"

class RangeUtil {
protected:
	constexpr static int MAX_RANGE = 32;

	using Distances = IterableBitset<MAX_RANGE>;
	using Movement = MobilityList<bool>;

};


class SingleRange : protected RangeUtil {
public:
	Movement _type;
	Distances _range;

	SingleRange(Movement move, Distances dist);

	bool operator==(const SingleRange& rhs);
	bool operator!=(const SingleRange& rhs);
	bool operator<(const SingleRange& rhs);
};