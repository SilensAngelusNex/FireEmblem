#include <iostream>

#include "Tests.h"
#include "Unit.h"
#include "FairDice.h"
#include "Map.h"

bool test::runMapTest() {
	std::cout << "Map test start:" << std::endl;

	FairDice<100> d;

	Unit mia("Mia", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1}));
	Unit ike("Ike", d, AttributeList({ 5, 1, 6, 7, 19, 5, 5, 0}));

	Map map = Map(20, 20); // create a 20 x 20 map
	map.insertUnit(&mia, &map.getGridCell(10, 10));
	std::vector <GridCell*> cells = map.getAccesibleCells(&mia);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = map.getAllAttackableCells(&mia);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	map.insertUnit(&ike, &map.getGridCell(10, 11));
	cells = map.getAccesibleCells(&mia);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = map.getAllAttackableCells(&mia);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	std::cout << "How many cells are adjacent to Mia: " << map.getGridCell(10, 10).getAdjacentCells().size() << std::endl;

	return true;
}
