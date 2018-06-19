#include "Range.h"

#include <map>

Range::Range() :
	Range(MobilitySet(), DistanceSet())
{}

Range::Range(std::vector<int> distances) :
	Range(MobilitySet(MobilityType::values::PROJECTILE), DistanceSet(distances))
{}

Range::Range(MobilityType type, std::vector<int> distances) :
	Range(MobilitySet(type), DistanceSet(distances))
{}


Range::Range(MobilitySet move, DistanceSet dist) :
	_type(move),
	_range(dist)
{}

bool Range::operator==(const Range & rhs) const {
	return _range == rhs._range && _type == rhs._type;
}
bool Range::operator!=(const Range & rhs) const {
	return _range != rhs._range || _type != rhs._type;
}
bool Range::operator<=(const Range & rhs) const {
	return _range <= rhs._range;
}
bool Range::operator>=(const Range & rhs) const {
	return _range >= rhs._range;
}
bool Range::operator<(const Range & rhs) const {
	return _range < rhs._range;
}
bool Range::operator>(const Range & rhs) const {
	return _range > rhs._range;
}

auto Range::operator[](MobilityType t) {
	return _type[t];
}
bool Range::operator[](MobilityType t) const {
	return _type[t];
}

auto Range::operator[](size_t distance) {
	return _range[distance];
}
bool Range::operator[](size_t distance) const {
	return _range[distance];
}