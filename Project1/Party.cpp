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

void Party::startTurn(PartyBase party_turn) {
	return PartyBase::startTurn(party_turn);
}

bool Party::isDone() {
	return PartyBase::isDone();
}

bool Party::hasUnit(Unit & unit)
{
	return PartyBase::hasUnit(unit);
}

void Party::insertUnit(UnitData unit) {
	PartyBase::insertUnit(unit);
}

void Party::changeParty(Unit& unit, Party& party) {
	PartyBase::changeParty(unit, party);
}