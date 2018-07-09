#include "Tests.h"
#include "FairDice.h"
#include "Chapter.h"
#include "Movehelper.h"
#include "UnitPath.h"
#include "ChapterCommand.h"
#include "MoveCommand.h"
#include "UndoMoveCommand.h"
#include "WaitCommand.h"
#include "EndCommand.h"
#include "AttackCommand.h"

#include "Weapon.h"
#include "Swords.h"


bool test::runChapterTest() {
	std::cout << "Chapter Test Begin" << std::endl;
	FairDice<100> d;
	UnitData mia_data = { "Mia", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	UnitData ike_data = { "Ike", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	std::vector<UnitData> unit_vec = { mia_data, ike_data };
	PartyData data1 = { "Greil Mercenaries", {mia_data} };
	PartyData data2 = { "Daein" ,{ike_data} };
	
	Chapter chapter = Chapter();

	chapter.addParty(data1);
	chapter.addParty(data2);
	

	chapter.start();	
	chapter.newTurn();
	chapter.newTurn();

	auto it = chapter._parties.front().begin();
	Unit::UniquePtr& mia_ptr = *it++;
	Unit& mia = *mia_ptr;
	it = chapter._parties.back().begin();
	Unit::UniquePtr& ike_ptr = *it;
	Unit& ike = *ike_ptr;

	MoveHelper move_helper = MoveHelper(chapter._map);


	chapter._map.insertUnit(mia, chapter._map[10][10]);
	UnitPath path = move_helper.getShortestPath(mia, chapter._map[10][12]._id);
	ChapterCommand<MoveCommand> move_command = ChapterCommand<MoveCommand>(MoveCommand(chapter, mia, path));
	chapter.acceptCommand(move_command);
	ChapterCommand<UndoMoveCommand> undo_move_command = ChapterCommand<UndoMoveCommand>(UndoMoveCommand(chapter, mia));
	chapter.acceptCommand(undo_move_command);
	chapter._map.insertUnit(ike, chapter._map[10][11]);
	std::unique_ptr<Weapon> mias_sword = WeaponFactory::makeBronzeSword();
	std::unique_ptr<Weapon> ikes_sword = WeaponFactory::makeBronzeSword();

	mia.getInventory().equip(ON_HAND, std::move(mias_sword));
	ike.getInventory().add(std::move(ikes_sword));
	ike.getInventory().equip(ON_HAND, 0);
	auto attack_command = ChapterCommand<AttackCommand>(AttackCommand(chapter, mia, ike));
	chapter.acceptCommand(attack_command);
	std::cout << chapter._map[mia] << std::endl;
	return chapter._map.getUnit(chapter._map[10][10]) == &mia;

	return true;
}