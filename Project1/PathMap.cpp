#include "PathMap.h"
#include "Grid.h"
#include "ID.h"
#include "GridCell.h"
#include <map>



PathMap::PathMap(Grid& map) : 
	std::map<const ID, CellCost>()//,
	//_map(map)
{}

PathMap::PathMap(const Grid& map) :
	std::map<const ID, CellCost>()//,
{}