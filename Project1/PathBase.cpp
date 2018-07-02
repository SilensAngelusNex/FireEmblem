#include "PathBase.h"
#include "GridCell.h"

PathBase::PathBase(const GridCell& head) :
	_head(&head)
{}

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


void PathBase::push_back(const GridCell & tail) {
	_path.emplace_back(0, tail);
}

void PathBase::pop_back() {
	Expects(!empty());
	_path.pop_back();
}

const GridCell& PathBase::back() const {
	Expects(!empty());
	return _path.back().second;

}

bool PathBase::contains(const GridCell & cell) const{
	return *_head == cell || position(cell) != cend();
}

bool PathBase::contains(ID id) const {
	return _head->_id == id || position(id) != cend();
}

void PathBase::trimPath(const GridCell & end) {
	while (!_path.empty() && back() != end ) {
		pop_back();
	}	
}

void PathBase::trimPath(ID end_id) {
	while (!_path.empty() && back()._id != end_id) {
		pop_back();
	}
}

PathBase & PathBase::operator+(const PathBase & path) {
	Expects(back() == *path._head);
	for (auto& pair : path) {
		push_back(pair.second);
	}
	return *this;
}