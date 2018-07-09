#pragma once
#include "GridMap.h"
#include "ChapterCommand.h"
#include <optional>

class MoveCommand;

class Chapter {
private: 
	int _turn = 0;
	std::list<Party>::iterator _turn_iterator;
	void setHelpers();
	//std::vector<Listeners>
public:
	std::list<MoveCommand> _reversable_moves;
	Chapter();

	template<typename T>
	void acceptCommand(ChapterCommand<T>& to_execute);

	Party& getTurnParty();
	void addParty(PartyData data);
	void dropParty(Party& party);

	void start();
	void newTurn();
	GridMap _map;
	std::list<Party> _parties;

};

template<typename T>
void Chapter::acceptCommand(ChapterCommand<T>& to_execute) {
	to_execute.execute();
}
