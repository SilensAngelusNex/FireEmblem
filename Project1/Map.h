#pragma once
#include <vector>
#include "Unit.h"
#include "Tile.h"
#include "CellPath.h"
#include "GridCell.h"

class Map
{
private:
	std::vector<std::vector<GridCell>> _grid;
	std::vector<Unit> _units;

public:
	Map(int _width, int _height);
	~Map();

};

