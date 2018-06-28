#include <iostream>

#include "Tests.h"
#include "Unit.h"
#include "FairDice.h"
#include "MoveHelper.h"
#include "CellPath.h"
#include "Party.h"
#include "GridCell.h"
#include "CellPath.h"
#include "GridMap.h"

bool test::runMapTest() {
	std::cout << "Grid test start:" << std::endl;

	FairDice<100> d;
	UnitData mia_data = { "Mia", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	UnitData ike_data = { "Ike", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	UnitPtr mia = std::make_unique<Unit>(mia_data);
	UnitPtr ike = std::make_unique<Unit>(ike_data);
	auto unit_vec = std::vector<UnitData>();
	unit_vec.push_back(mia_data);
	unit_vec.push_back(ike_data);
	PartyData data1 = { "Greil Mercenaries" };
	PartyData data2 = { "Daein" };
	std::vector<PartyData> party_vec = std::vector<PartyData>();
	party_vec.push_back(data1);
	party_vec.push_back(data2);

	GridMap map = GridMap(20, 20, party_vec); // create a 20 x 20 map
	auto move_helper = MoveHelper(map);
	Party& party = map._parties.front();
	Party& party2 = map._parties.back();
	party.insertUnit(std::move(mia));
	party.insertUnit(std::move(ike));

	auto it = party.begin();
	Unit& mia2 = **it++;
	UnitPtr& ike2 = *it;

	map.insertUnit(mia2, map[10][10]);
	std::vector <CellRef> cells = move_helper.getAccesibleCells(mia2);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getAllAttackableCells(mia2);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	map.insertUnit(*ike2, map[10][11]);
	cells = move_helper.getAccesibleCells(mia2);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getAllAttackableCells(mia2);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	std::cout << "How many cells are adjacent to Mia: " << map[mia2].getAdjacentCellIDs().size() << std::endl;
	party2.insertUnit(party.dropUnit(*ike2));
	cells = move_helper.getAccesibleCells(mia2);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getAllAttackableCells(mia2);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	std::cout << "How many cells are adjacent to Mia: " << map[mia2].getAdjacentCellIDs().size() << std::endl;
	/*CellPath path = move_helper.getShortestPath(mia2, map[11][11]);
	move_helper.canWalk(mia2, path);
	std::cout << "Can Mia move to (11, 11)?: " << move_helper.canWalk(mia2, path) << std::endl;
	move_helper.walkPath(mia2, path);
	std::cout << "Attempted to walk" << std::endl;
	std::cout << "Is Mia at (11, 11)?" << (map[mia2] == map[11][11]) << std::endl;;
	*/
	
	return true;
}
