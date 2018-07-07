#pragma once
#include "GridMap.h"
#include "ChapterCommand.h"
#include "MoveCommand.h"


class Chapter {
	
	//std::vector<Listeners>
public:
	Chapter();

	template<typename T>
	void acceptCommand(ChapterCommand<T> to_execute);

	void addParty(PartyData data);
	void dropParty(Party& party);

	GridMap _map;
	std::list<Party> _parties;
};

template<typename T>
void Chapter::acceptCommand(ChapterCommand<T> to_execute) {
	to_execute.execute();
}