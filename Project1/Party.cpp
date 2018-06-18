#include "Party.h"

#include <utility>

Party::Party() 
= default;

Party::Party(std::string name) : PartyBase(name)
{}

Party::Party(std::string name, std::vector<UnitData> unit_data) : PartyBase(name, unit_data)
{}

Party::Party(PartyData data) : PartyBase(data)
{}

void Party::startTurn(PartyBase& turn_party) {
	if (this == &turn_party) {
		for (Unit& unit : _units) {
			unit.refresh();
		}
	}
	else {
		for (Unit& unit : _units) {
			unit.newTurn();
		}
	}
}
void Party::insertUnit(Unit& unit) {
	PartyBase::insertUnit(unit);
}
/*Use this function to determine when to change turns
*/
bool Party::isDone() const{
	bool isDone = false;
	for (const Unit& unit : _units) {
		isDone = isDone || unit.isTired(); // || unit->isDead();
	}
	return isDone;
}

std::vector<UnitRef> Party::getUnits() {
	auto vec = std::vector<UnitRef>();
	for (auto& unit : _units) {
		vec.emplace_back(unit);
	}
	return vec;
}

std::vector<UnitRef> Party::getOtherUnits(const Unit& unit) {
	auto vec = std::vector<UnitRef>();
	for (Unit& other : _units) {
		if (unit != other) {
			vec.emplace_back(other);
		}
	}
	return vec;
}

std::vector<constUnitRef> Party::getUnits() const {
	auto vec = std::vector<constUnitRef>();
	for (auto& unit : _units) {
		vec.emplace_back(unit);
	}
	return vec;
}

std::vector<constUnitRef> Party::getOtherUnits(const Unit& unit) const{
	auto vec = std::vector<constUnitRef>();
	for (auto& other : _units) {
		if (unit != other) {
			vec.emplace_back(other);
		}
	}
	return vec;
}
