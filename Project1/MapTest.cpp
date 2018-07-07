#include <iostream>

#include "Tests.h"
#include "Unit.h"
#include "FairDice.h"
#include "MoveHelper.h"
#include "AttackHelper.h"
#include "Party.h"
#include "GridCell.h"
#include "GridMap.h"
#include "Weapon.h"
#include "Swords.h"
#include "UnitPath.h"

bool test::runMapTest() {
	std::cout << "Grid test start:" << std::endl;

	FairDice<100> d;
	UnitData mia_data = { "Mia", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	UnitData ike_data = { "Ike", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	std::vector<UnitData> unit_vec = { mia_data, ike_data };
	PartyData data1 = { "Greil Mercenaries", unit_vec };
	PartyData data2 = { "Daein" , {} };
	std::vector<PartyData> party_vec = { data1, data2 };

	GridMap map = GridMap(20, 20, party_vec); // create a 20 x 20 map
	auto move_helper = MoveHelper(map);
//	auto attack_helper = AttackHelper(map);
	Party& party = map._parties.front();
	Party& party2 = map._parties.back();

	//Get my Units
	auto it = party.begin();
	Unit::UniquePtr& mia_ptr = *it++;
	Unit& mia = *mia_ptr;
	Unit::UniquePtr& ike_ptr = *it;
	Unit& ike = *ike_ptr;
	ike.getMobility();
	
	std::unique_ptr<Weapon> mias_sword = WeaponFactory::makeBronzeSword();

	mia.getInventory().equip(ON_HAND, std::move(mias_sword));

	map.insertUnit(mia, map[10][10]._id);
	std::set <ID> cells = move_helper.getAccesibleCellIDs(mia);
	UnitPath path = move_helper.getShortestPath(mia, map[10][13]._id);
	move_helper.reRoutePath(path, map[11][12]._id);
	std::cout << "Start walking " << mia.getIdentity() << " from space:" << map[mia] << " to space " << path.back()._id << std::endl;
	move_helper.walkPath(mia, path);
	std::cout << "Start walking " << mia.getIdentity() << " from space:" << map[mia] << " to space " << path.back()._id << std::endl;
	move_helper.walkPath(mia, move_helper.getShortestPath(mia, map[10][10]._id));
	
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getMoveEquipableAttackIDs(mia);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	map.insertUnit(*ike_ptr, map[10][11]._id);
	UnitPath a = move_helper.getShortestPath(mia, map[10][12]._id);
	move_helper.walkPath(mia, a);
	UnitPath b = move_helper.getShortestPath(mia, map[10][10]._id);
	move_helper.walkPath(mia, b);
	cells = move_helper.getAccesibleCellIDs(mia);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getMoveEquipableAttackIDs(mia);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	std::cout << "How many cells are adjacent to Mia: " << map[map[mia]].getAdjacentCellIDs().size() << std::endl;
	party2.insertUnit(party.dropUnit(*ike_ptr));
	cells = move_helper.getAccesibleCellIDs(mia);
	UnitPath path2 = move_helper.getShortestPath(mia, map[10][12]._id);
	move_helper.walkPath(mia, path2);
	std::cout << "How many cells Mia can Reach: " << cells.size() << std::endl;
	cells = move_helper.getMoveEquipableAttackIDs(mia);
	std::cout << "How many cells can Mia Attack?: " << cells.size() << std::endl;
	
	std::cout << "How many cells are adjacent to Mia: " << map[map[mia]].getAdjacentCellIDs().size() << std::endl;


	
	return true;
}
