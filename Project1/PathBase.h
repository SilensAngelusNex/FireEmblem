#pragma once
#include <list>
#include "logic_pair.h"
#include "GridCell.h"

template<typename Cell>
class PathBase {
protected:
	using CostCell = logic_pair<int, logical_reference_wrapper<Cell>>;
	using List = typename std::list<CostCell>;
	List _path;
	Cell& _head;	
	PathBase(Cell& head);
public:
	PathBase() = delete;
	//Iterator
	using iterator = typename List::iterator;
	using const_iterator = typename List::const_iterator;
	iterator begin() { return _path.begin(); }
	const_iterator begin() const { return _path.begin(); }
	const_iterator cbegin() const { return _path.cbegin(); }
	iterator end() { return _path.end(); }
	const_iterator end() const { return _path.end(); }
	const_iterator cend() const { return _path.cend(); }
protected:
	//Helper Methods
	iterator position(const Cell& end) { return std::find_if(_path.begin(), _path.end(), [&](const CostCell& a) -> bool { return a.second == end; }); }
	iterator position(ID id) { return std::find_if(_path.begin(), _path.end(), [&](const CostCell& a) -> bool { return a.second.get()._id == id; }); }
	const_iterator position(const Cell& end) const { return std::find_if(_path.begin(), _path.end(), [&](const CostCell& a) -> bool { return a.second.get() == end; }); }
	const_iterator position(ID id) const { return std::find_if(_path.begin(), _path.end(), [&](const CostCell& a) -> bool { return a.second.get()._id == id; }); }
public:

	//Modifiers
	void push_back(Cell& tail);
	void pop_back();
	void trimPath(const Cell& end);
	void trimPath(ID end_id);

	PathBase & operator+(const PathBase & path);

	//Element Access
	Cell& back();
	const Cell& back() const;

	//Capacity
	//bool empty() const { return _path.empty(); }
	bool contains(const Cell& cell) const;
	bool contains(ID id) const;
	size_t size() const {	return _path.size() + 1; }
};

template<typename Cell>
PathBase<Cell>::PathBase(Cell& head) :
	_head(head)
{}

template<typename Cell>
void PathBase<Cell>::push_back(Cell & tail) {
	_path.emplace_back(0, tail);
}
template<typename Cell>
void PathBase<Cell>::pop_back() {
	Expects(!_path.empty());
	_path.pop_back();
}
template<typename Cell>
Cell& PathBase<Cell>::back() {
	if (_path.empty()) {
		return _head;
	}
	return _path.back().second;

}

template<typename Cell>
const Cell& PathBase<Cell>::back() const {
	if (_path.empty()) {
		return _head;
	}
	return _path.back().second;

}
template<typename Cell>
bool PathBase<Cell>::contains(const Cell & cell) const {
	return _head == cell || position(cell) != cend();
}
template<typename Cell>
bool PathBase<Cell>::contains(ID id) const {
	return _head._id == id || position(id) != cend();
}
template<typename Cell>
void PathBase<Cell>::trimPath(const Cell & end) {
	Expects(contains(end));
	if (end == _head) {
		_path.clear();
		return;
	}
	while (_path.back().second != end) {
		pop_back();
	}
}
template<typename Cell>
void PathBase<Cell>::trimPath(ID end_id) {
	Expects(contains(end_id));
	if (end_id == _head._id) {
		_path.clear();
		return;
	}
	while (_path.back().second.get()._id != end_id) {
		pop_back();
	}
}
template<typename Cell>
PathBase<Cell> & PathBase<Cell>::operator+(const PathBase & path) {
	Expects(back() == path._head);
	for (auto& pair : path) {
		push_back(pair.second);
	}
	return *this;
}