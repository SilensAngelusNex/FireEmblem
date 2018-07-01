#include "Actions.h"

#include <gsl/gsl_assert>

Actions::Actions() :
	_used_move(0),
	_major_remaining(true),
	_minor_remaining(true),
	_independent_used()
{}

bool Actions::hasMajor() const {
	return _major_remaining;
}

bool Actions::hasMinor() const {
	return _minor_remaining || _major_remaining;
}

int Actions::moveUsed() const {
	return _used_move;
}

bool Actions::hasIndependent(ActionId action) const {
	return std::find(_independent_used.begin(), _independent_used.end(), action) == _independent_used.end();
}

const std::set<Actions::ActionId>& Actions::usedIndependents() const {
	return _independent_used;
}

void Actions::useMajor() {
	Expects(hasMajor());

	_major_remaining = false;
}

void Actions::useMinor() {
	Expects(hasMajor() || hasMinor());

	if (_minor_remaining) {
		_minor_remaining = false;
	} else {
		_major_remaining = false;
	}
}

void Actions::useMove(int used) {
	_used_move += used;
}

void Actions::useIndependent(ActionId used) {
	Expects(hasIndependent(used));

	_independent_used.insert(used);
}

void Actions::refresh() {
	_used_move = 0;
	_major_remaining = true;
	_minor_remaining = true;
	_independent_used.clear();
}
