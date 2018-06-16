#include "Range.h"

#include <map>

SingleRange::SingleRange(Movement move, Distances dist) :
	_type(move),
	_range(dist)
{}

bool SingleRange::operator==(const SingleRange & rhs) {
	return _range == rhs._range && _type == rhs._type;
}

bool SingleRange::operator!=(const SingleRange & rhs)
{
	return !(*this == rhs);
}

bool SingleRange::operator<(const SingleRange & rhs) {
	return _range < rhs._range;
}

Range::Range(std::vector<SingleRange> ranges) {
	for (SingleRange range : ranges) {
		for (MobilityType type : MobilityType::list) {
			if (range._type[type]) {
				_matrix[type] &= range._range;
			}
		}
	}
}

Range::operator std::vector<SingleRange>() {
	std::map<Movement, Distances> map = *this;

	std::vector<SingleRange> result;
	for (const auto&[move, range] : map) {
		result.emplace_back(move, range);
	}
	return result;
}

Range::operator std::map<RangeUtil::Movement, RangeUtil::Distances>() {
	std::map<Movement, Distances> result;

	for (size_t i = 0; i < MAX_RANGE; ++i) {
		Movement m;
		for (MobilityType t : MobilityType::list) {
			m[t] = m[t] && _matrix[t][i];
		}

		result[m] &= Distances(i);
	}
	result.erase(Movement());

	return result;
}
