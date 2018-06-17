#include "Range.h"

#include <map>

SingleRange::SingleRange() :
	SingleRange(Movement(), Distances())
{}

SingleRange::SingleRange(std::vector<int> distances) :
	SingleRange(Movement(MobilityType::values::PROJECTILE), Distances(distances))
{}

SingleRange::SingleRange(MobilityType type, std::vector<int> distances) :
	SingleRange(Movement(type), Distances(distances))
{}


SingleRange::SingleRange(Movement move, Distances dist) :
	_type(move),
	_range(dist)
{}

bool SingleRange::operator==(const SingleRange & rhs) const {
	return _range == rhs._range && _type == rhs._type;
}
bool SingleRange::operator!=(const SingleRange & rhs) const {
	return _range != rhs._range || _type != rhs._type;
}
bool SingleRange::operator<=(const SingleRange & rhs) const {
	return _range <= rhs._range;
}
bool SingleRange::operator>=(const SingleRange & rhs) const {
	return _range >= rhs._range;
}
bool SingleRange::operator<(const SingleRange & rhs) const {
	return _range < rhs._range;
}
bool SingleRange::operator>(const SingleRange & rhs) const {
	return _range > rhs._range;
}

auto SingleRange::operator[](MobilityType t) {
	return _type[t];
}
bool SingleRange::operator[](MobilityType t) const {
	return _type[t];
}

auto SingleRange::operator[](size_t distance) {
	return _range[distance];
}
bool SingleRange::operator[](size_t distance) const {
	return _range[distance];
}