#include "Chapter.h"
#include "Party.h"
#include "ChapterCommand.h"
#include "MoveCommand.h"
#include "Party.h"
#include "AttackHelper.h"
#include "MoveHelper.h"
#include "HelperContainer.h"

void Chapter::setHelpers(){
	AttackContainer::setHelper(AttackHelper(_map));
	MoveContainer::setHelper(MoveHelper(_map));
}

Chapter::Chapter() :
	_map(20, 20)
{
	setHelpers();
}

Party & Chapter::getTurnParty() {
	Expects(turn > 0);
	return *_turn_iterator;
}

void Chapter::addParty(PartyData data) {
	_parties.emplace_back(data);
}

void Chapter::dropParty(Party & party) {
	Expects(std::find_if(_parties.begin(), _parties.end(), [&](const Party& a) -> bool { return a == party; }) != _parties.end());
	Expects(party != getTurnParty());
	_parties.erase(std::find_if(_parties.begin(), _parties.end(), [&](const Party& a) -> bool { return a == party; }));
	
}

void Chapter::start() {
	Expects(turn == 0 && !_parties.empty());
	turn++;
	_turn_iterator = _parties.begin();
	for (auto& party : _parties) {
		party.startTurn(getTurnParty());
	}
}

void Chapter::newTurn() {
	Expects(turn > 0 && !_parties.empty());
	turn++;
	_turn_iterator++;
	if (_turn_iterator == _parties.end()) {
		_turn_iterator = _parties.begin();
	}
	for (auto& party : _parties) {
		party.startTurn(getTurnParty());
	}
}

