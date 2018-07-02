#pragma once
#include <list>
#include "logic_pair.h"
#include "GridCell.h"


class PathBase {
protected:
	using CostCell = logic_pair<int, GridCell::Ref>;
	using List = std::list<CostCell>;
	List _path;
	PathBase() = default;
public:
	//Iterator
	using iterator = List::iterator;
	using const_iterator = List::const_iterator;
	iterator begin() { return _path.begin(); }
	const_iterator cbegin() const { return _path.cbegin(); }
	iterator end() { return _path.end(); }
	const_iterator cend() const { return _path.cend(); }
protected:
	//Helper Methods
	iterator position(const GridCell& end);
	iterator position(ID id);
	const_iterator position(const GridCell& end) const;
	const_iterator position(ID id) const;
public:

	//Modifiers
	void push_back(GridCell& tail);
	void pop_back();
	void trimPath(const GridCell& end);
	void trimPath(ID end_id);

	//Element Access
	GridCell& front();
	GridCell& back();
	const GridCell& front() const;
	const GridCell& back() const;

	//Capacity
	bool empty() const { return _path.empty(); }
	bool contains(const GridCell& cell) const;
	bool contains(ID id) const;
	size_t size() const {	return _path.size(); }



};

