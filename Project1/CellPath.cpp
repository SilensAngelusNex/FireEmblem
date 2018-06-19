#include "CellPath.h"
#include "CellEdge.h"
#include "GridCell.h"

CellPath::CellPath(GridCell & head) : CellPath(head, MobilitySet({ true })) {};

CellPath::CellPath(GridCell & head, const MobilitySet traversal_vector) :
	_traversal_vector(traversal_vector)
{
	_path.emplace_back(0, head);
}

CellPath::CellPath(std::list<CellWrap> path, const MobilitySet traversal_vector) : CellPath(path.front(), traversal_vector) {
	path.pop_front();
	for (GridCell& cell : path) {
		addTail(cell);
	}
}

void CellPath::addTail(GridCell & tail) {
	Expects(getTail().isAdjacent(tail, _traversal_vector));
	_path.emplace_back(getCost() + getTail().getEdge(tail).value().getCost(_traversal_vector).value(), tail);
}

int CellPath::getCost() {
	return _path.back().first;
}

GridCell & CellPath::getTail() {
	return _path.back().second;
}
GridCell & CellPath::getHead() {
	return _path.front().second;
}

int CellPath::getCost() const {
	return _path.back().first;
}

const GridCell & CellPath::getTail() const {
	return _path.back().second;
}

const GridCell & CellPath::getHead() const {
	return _path.front().second;
}