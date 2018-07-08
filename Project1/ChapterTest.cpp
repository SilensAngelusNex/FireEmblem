#include "Tests.h"
#include "FairDice.h"
#include "Chapter.h"
#include "Movehelper.h"
#include "UnitPath.h"
#include "ChapterCommand.h"
#include "MoveCommand.h"




bool test::runChapterTest() {
	std::cout << "Chapter Test Begin" << std::endl;
	FairDice<100> d;
	UnitData mia_data = { "Mia", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	UnitData ike_data = { "Ike", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }) };
	std::vector<UnitData> unit_vec = { mia_data, ike_data };
	PartyData data1 = { "Greil Mercenaries", unit_vec };
	PartyData data2 = { "Daein" ,{} };
	
	Chapter chapter = Chapter();

	chapter.addParty(data1);
	chapter.addParty(data2);
	

	chapter.start();	
	chapter.newTurn();
	chapter.newTurn();

	auto it = chapter._parties.front().begin();
	Unit::UniquePtr& mia_ptr = *it++;
	Unit& mia = *mia_ptr;
	Unit::UniquePtr& ike_ptr = *it;
	Unit& ike = *ike_ptr;

	MoveHelper move_helper = MoveHelper(chapter._map);


	chapter._map.insertUnit(mia, chapter._map[10][10]);
	UnitPath path = move_helper.getShortestPath(mia, chapter._map[10][12]._id);
	ChapterCommand<MoveCommand> move_command = ChapterCommand<MoveCommand>(MoveCommand(chapter, mia, path));
	chapter.acceptCommand(move_command);
	UnitPath path2 = move_helper.getShortestPath(mia, chapter._map[10][10]._id);
	ChapterCommand<MoveCommand> move_command2 = ChapterCommand<MoveCommand>(MoveCommand(chapter, mia, path2));
	chapter.acceptCommand(move_command2);
	chapter.acceptCommand(move_command2);
	return chapter._map.getUnit(chapter._map[10][12]) == &mia;

	return true;
}