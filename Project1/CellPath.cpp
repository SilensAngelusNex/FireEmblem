#include "CellPath.h"

CellPath::CellPath(GridCell & head) : CellPath(head, MobilityList<bool>({ true })) {};

CellPath::CellPath(GridCell & head, const MobilityList<bool> traversal_vector) :
	_traversal_vector(traversal_vector)
{
	_path.emplace_back(0, &head);
}

CellPath::CellPath(std::list<GridCell*> path, const MobilityList<bool> traversal_vector) : CellPath(*path.front(), traversal_vector) {
	path.pop_front();
	for (GridCell* cell : path) {
		addTail(*cell);
	}
}

void CellPath::addTail(GridCell & tail) {
	Expects(_path.back().second->isAdjacent(tail, _traversal_vector));
	_path.emplace_back(getCost() + getTail().getEdge(tail).value().getCost(_traversal_vector).value(), &tail);
}

int CellPath::getCost() {
	return _path.back().first;
}

GridCell & CellPath::getTail() {
	return *_path.back().second;
}
GridCell & CellPath::getHead() {
	return *_path.front().second;
}

int CellPath::getCost() const {
	return _path.back().first;
}

const GridCell & CellPath::getTail() const {
	return *_path.back().second;
}

const GridCell & CellPath::getHead() const {
	return *_path.front().second;
}