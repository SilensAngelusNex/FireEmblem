#include "Range.h"

#include <map>

Range::Range() :
	Range(Movement(), Distances())
{}

Range::Range(std::vector<int> distances) :
	Range(Movement(MobilityType::values::PROJECTILE), Distances(distances))
{}

Range::Range(MobilityType type, std::vector<int> distances) :
	Range(Movement(type), Distances(distances))
{}


Range::Range(Movement move, Distances dist) :
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