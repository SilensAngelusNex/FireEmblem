#include "PathBase.h"

PathBase::iterator PathBase::position(const GridCell & end) {
	return std::find_if(_path.begin(), _path.end(), [&](const CostCell& a) -> bool { return a.second == end; });
}
PathBase::iterator PathBase::position(ID id) {
	return std::find_if(_path.begin(), _path.end(), [&](const CostCell& a) -> bool { return a.second.get()._id == id; });
}

PathBase::const_iterator PathBase::position(const GridCell & end)  const {
	return std::find_if(_path.begin(), _path.end(), [&](const CostCell& a) -> bool { return a.second == end; });
}
PathBase::const_iterator PathBase::position(ID id) const {
	return std::find_if(_path.begin(), _path.end(), [&](const CostCell& a) -> bool { return a.second.get()._id == id; });
}


void PathBase::push_back(GridCell & tail) {
	_path.emplace_back(0, tail);
}

void PathBase::pop_back() {
	Expects(!empty());
	_path.pop_back();
}

GridCell & PathBase::front() {
	Expects(!empty());
	return _path.front().second;

}

const GridCell & PathBase::front() const {
	Expects(!empty());
	return _path.front().second;

}
GridCell& PathBase::back() {
	Expects(!empty());
	return _path.back().second;

}

const GridCell& PathBase::back() const {
	Expects(!empty());
	return _path.back().second;

}

bool PathBase::contains(const GridCell & cell) const{
	return position(cell) != cend();
}

bool PathBase::contains(ID id) const {
	return position(id) != cend();
}

void PathBase::trimPath(const GridCell & end) {
	Expects(contains(end));
	while (back() != end) {
		pop_back();
	}	
}

void PathBase::trimPath(ID end_id) {
	Expects(contains(end_id));
	while (back()._id != end_id) {
		pop_back();
	}
}