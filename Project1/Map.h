#pragma once
#include <vector>
#include "Unit.h"
#include "Tile.h"
#include "CellPath.h"
#include "GridCell.h"

/**
Map class. Holds a Matrix of GridCells and all of the units. Should be initialized at the start of each chapter.
*/
class Map
{
private:
	std::vector<std::vector<GridCell>> _grid;
	std::vector<Unit> _units;

public:
	Map(int _width, int _height);
	~Map();

};

