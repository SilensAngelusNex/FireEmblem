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
