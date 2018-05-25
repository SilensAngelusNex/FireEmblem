#include "Map.h"



Map::Map(int _width, int _height) : _grid(_width, std::vector<GridCell>(_height, GridCell()))
{
}


Map::~Map()
{
}

std::vector<CellPath> getUnitMoveableTiles(Tile* tile)
{

}