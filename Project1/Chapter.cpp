#include "Chapter.h"
#include "Party.h"
#include "ChapterCommand.h"
#include "MoveCommand.h"

Chapter::Chapter() :
	_map(20, 20)
{}

void Chapter::addParty(PartyData data) {
	_parties.emplace_back(data);
}

void Chapter::dropParty(Party & party) {
	Expects(std::find_if(_parties.begin(), _parties.end(), [&](const Party& a) -> bool { return a == party; }) != _parties.end());
	_parties.erase(std::find_if(_parties.begin(), _parties.end(), [&](const Party& a) -> bool { return a == party; }));
	
}

