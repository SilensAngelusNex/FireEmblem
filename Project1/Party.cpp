#include "Party.h"

#include <utility>

Party::Party(): PartyBase()
{}

Party::Party(std::string name) : PartyBase(name)
{}

Party::Party(std::string name, std::vector<UnitData> unit_data) : PartyBase(name, unit_data)
{}

Party::Party(PartyData data) : PartyBase(data)
{}

void Party::startTurn(PartyBase& turn_party) {
	if (this == &turn_party) {
		for (UnitPtr& unit : _units) {
			unit->refresh();
		}
	}
	else {
		for (UnitPtr& unit : _units) {
			unit->newTurn();
		}
	}
}
void Party::insertUnit(Unit& unit) {
	PartyBase::insertUnit(unit);
}
/*Use this function to determine when to change turns
*/
bool Party::isDone() {
	bool isDone = false;
	for (UnitPtr& unit : _units) {
		isDone = isDone || unit->isTired(); // || unit->isDead();
	}
	return isDone;
}
Unit & Party::getUnit(int index) {
	Expects(index >= 0 && index < _units.size());
	return *_units[index];
}

std::vector<std::reference_wrapper<Unit>> Party::getUnits() {
	auto vec = std::vector<std::reference_wrapper<Unit>>();
	for (auto& unit : _units) {
		vec.push_back(*unit.get());
	}
	return vec;
}

std::vector<std::reference_wrapper<Unit>> Party::getOtherUnits(Unit& unit)
{
	auto vec = std::vector<std::reference_wrapper<Unit>>();
	for (auto& a : _units) {
		if (unit != *a) {
			vec.push_back(*a.get());
		}
	}
	return vec;
}
