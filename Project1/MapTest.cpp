#include <iostream>

#include "Tests.h"
#include "Unit.h"
#include "FairDice.h"
#include "MoveHelper.h"
#include "CellPath.h"
#include "Party.h"
#include "GridCell.h"
#include "CellPath.h"

bool test::runMapTest() {
	std::cout << "Map test start:" << std::endl;

	FairDice<100> d;
	UnitData mia_data = { "Mia", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	UnitData ike_data = { "Ike", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	auto unit_vec = std::vector<UnitData>();
	unit_vec.push_back(mia_data);
	unit_vec.push_back(ike_data);
	PartyData data1 = { "Greil Mercenaries", unit_vec};
	PartyData data2 = { "Daein" };
	std::vector<PartyData> party_vec = std::vector<PartyData>();
	party_vec.push_back(data1);
	party_vec.push_back(data2);

	Map map = Map(20, 20, party_vec); // create a 20 x 20 map
	auto move_helper = MoveHelper(map);
	Party& party = map._parties.front();
	Party& party2 = map._parties.back();
	
	Unit& mia = party.getUnit(0);
	Unit& ike = party.getUnit(1);
	map.insertUnit(mia, map.getGridCell(10, 10));
	std::vector <GridCell*> cells = move_helper.getAccesibleCells(mia);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getAllAttackableCells(mia);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	map.insertUnit(ike, map.getGridCell(10, 11));
	cells = move_helper.getAccesibleCells(mia);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getAllAttackableCells(mia);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	std::cout << "How many cells are adjacent to Mia: " << map.getGridCell(mia).getAdjacentCells().size() << std::endl;
	party2.insertUnit(ike);
	cells = move_helper.getAccesibleCells(mia);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getAllAttackableCells(mia);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	std::cout << "How many cells are adjacent to Mia: " << map.getGridCell(mia).getAdjacentCells().size() << std::endl;
	CellPath path = move_helper.getShortestPath(mia, map.getGridCell(11, 11));
	move_helper.canWalk(mia, path);
	std::cout << "Can Mia move to (11, 11)?: " << move_helper.canWalk(mia, path) << std::endl;
	move_helper.walkPath(mia, path);
	std::cout << "Attempted to walk" << std::endl;
	std::cout << "Is Mia at (11, 11)?" << (map.getGridCell(mia) == map.getGridCell(11, 11)) << std::endl;
	
	return true;
}
