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
bool Party::isDone() const{
	bool isDone = false;
	for (const UnitPtr& unit : _units) {
		isDone = isDone || unit->isTired(); // || unit->isDead();
	}
	return isDone;
}
Unit& Party::getUnit(int index) {
	Expects(index >= 0 && index < _units.size());
	return *_units[index];
}

std::vector<std::reference_wrapper<Unit>> Party::getUnits() {
	return std::as_const(*this).getUnits();
}

std::vector<std::reference_wrapper<Unit>> Party::getOtherUnits(const Unit& unit) {
	return std::as_const(*this).getOtherUnits(unit);
}

const Unit&  Party::getUnit(int index) const{
	Expects(index >= 0 && index < _units.size());
	return *_units[index];
}

const std::vector<std::reference_wrapper<Unit>> Party::getUnits() const{
	auto vec = std::vector<std::reference_wrapper<Unit>>();
	for (auto& unit : _units) {
		vec.emplace_back(*unit);
	}
	return vec;
}

const std::vector<std::reference_wrapper<Unit>> Party::getOtherUnits(const Unit& unit) const
{
	auto vec = std::vector<std::reference_wrapper<Unit>>();
	for (auto& a : _units) {
		if (unit != *a) {
			vec.emplace_back(*a);
		}
	}
	return vec;
}
