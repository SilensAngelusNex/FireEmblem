#pragma once
#include "GridMap.h"
#include "ChapterCommand.h"
#include "MoveCommand.h"


class Chapter {
private: 
	int turn = 0;
	std::list<Party>::iterator _turn_iterator;
	//std::vector<Listeners>
public:
	Chapter();

	template<typename T>
	void acceptCommand(ChapterCommand<T> to_execute);

	Party& getTurnParty();
	void addParty(PartyData data);
	void dropParty(Party& party);

	void start();
	void newTurn();
	GridMap _map;
	std::list<Party> _parties;

};

template<typename T>
void Chapter::acceptCommand(ChapterCommand<T> to_execute) {
	to_execute.execute();
}