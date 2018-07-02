#include <iostream>

#include "Tests.h"
#include "Unit.h"
#include "FairDice.h"
#include "MoveHelper.h"
#include "AttackHelper.h"
//#include "CellPath.h"
#include "Party.h"
#include "GridCell.h"
#include "GridMap.h"
#include "Weapon.h"
#include "Swords.h"
#include "MovementPath.h"

bool test::runMapTest() {
	std::cout << "Grid test start:" << std::endl;

	FairDice<100> d;
	UnitData mia_data = { "Mia", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	UnitData ike_data = { "Ike", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	Unit::UniquePtr mia = std::make_unique<Unit>(mia_data);
	Unit::UniquePtr ike = std::make_unique<Unit>(ike_data);
	auto unit_vec = std::vector<UnitData>();
	unit_vec.push_back(mia_data);
	unit_vec.push_back(ike_data);
	PartyData data1 = { "Greil Mercenaries", {} };
	PartyData data2 = { "Daein" , {} };
	std::vector<PartyData> party_vec = std::vector<PartyData>();
	party_vec.push_back(data1);
	party_vec.push_back(data2);

	GridMap map = GridMap(20, 20, party_vec); // create a 20 x 20 map
	auto move_helper = MoveHelper(map);
//	auto attack_helper = AttackHelper(map);
	Party& party = map._parties.front();
	Party& party2 = map._parties.back();
	party.insertUnit(std::move(mia));
	party.insertUnit(std::move(ike));

	auto it = party.begin();
	Unit& mia2 = **it++;
	Unit::UniquePtr& ike2 = *it;

	std::unique_ptr<Weapon> mias_sword = WeaponFactory::makeBronzeSword();

	mia2.getInventory().equip(ON_HAND, std::move(mias_sword));

	map.insertUnit(mia2, map[10][10]);
	std::set <ID> cells = move_helper.getAccesibleCellIDs(mia2);
	MovementPath path = move_helper.getShortestPath(mia2, map[10][13]._id);
	move_helper.reRoutePath(path, map[10][7]._id);
	move_helper.walkPath(mia2, path);

	/*
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getMoveEquipableAttackIDs(mia2);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	map.insertUnit(*ike2, map[10][11]);
	MovementPath a = move_helper.getShortestPath(mia2, map[10][12]._id);
	move_helper.walkPath(mia2, a);
	MovementPath b = move_helper.getShortestPath(mia2, map[10][10]._id);
	move_helper.walkPath(mia2, b);
	cells = move_helper.getAccesibleCellIDs(mia2);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getMoveEquipableAttackIDs(mia2);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	std::cout << "How many cells are adjacent to Mia: " << map[map[mia2]].getAdjacentCellIDs().size() << std::endl;
	party2.insertUnit(party.dropUnit(*ike2));
	cells = move_helper.getAccesibleCellIDs(mia2);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getMoveEquipableAttackIDs(mia2);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	
	std::cout << "How many cells are adjacent to Mia: " << map[map[mia2]].getAdjacentCellIDs().size() << std::endl;
	MovementPath c = move_helper.getShortestPath(mia2, map[10][12]._id);
	move_helper.walkPath(mia2, c);
	//AdjCellPath path = move_helper.getShortestPath(mia2, map[11][11]);
	/*
	move_helper.canWalk(mia2, path);
	std::cout << "Can Mia move to (11, 11)?: " << move_helper.canWalk(mia2, path) << std::endl;
	move_helper.walkPath(mia2, path);
	std::cout << "Attempted to walk" << std::endl;
	std::cout << "Is Mia at (11, 11)?" << (map[mia2] == map[11][11]) << std::endl;;
	*/
	
	return true;
}
