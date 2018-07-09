#include "Chapter.h"
#include "Party.h"
#include "ChapterCommand.h"
#include "MoveCommand.h"
#include "Party.h"
#include "AttackHelper.h"
#include "MoveHelper.h"
#include "HelperContainer.h"
#include "AttackCommand.h"

void Chapter::setHelpers(){
	AttackContainer::setHelper(_attack_helper);
	MoveContainer::setHelper(_move_helper);
}

Chapter::Chapter() :
	_map(20, 20),
	_attack_helper(_map),
	_move_helper(_map)
{
	setHelpers();
}

Party & Chapter::getTurnParty() {
	Expects(_turn > 0);
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
	Expects(_turn == 0 && !_parties.empty());
	_turn++;
	_turn_iterator = _parties.begin();
	for (auto& party : _parties) {
		party.startTurn(getTurnParty());
	}
}

void Chapter::newTurn() {
	Expects(_turn > 0 && !_parties.empty());
	_turn++;
	_turn_iterator++;
	if (_turn_iterator == _parties.end()) {
		_turn_iterator = _parties.begin();
	}
	for (auto& party : _parties) {
		party.startTurn(getTurnParty());
	}
	_reversable_moves.clear();
}
