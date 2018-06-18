#include "PartyBase.h"

std::vector<UnitPtr>::const_iterator PartyBase::getPosition(const Unit & unit) const {
	return std::find_if(_units.begin(), _units.end(), [&](const UnitPtr& a) -> bool { return a.get() == &unit; });
}

std::vector<UnitPtr>::iterator PartyBase::getPosition(const Unit & unit) {
	return std::find_if(_units.begin(), _units.end(), [&](const UnitPtr& a) -> bool { return a.get() == &unit; });
}

PartyBase::PartyBase() :
	PartyBase("~NULL PARTY~", std::vector<UnitData>())
{}

PartyBase::PartyBase(std::string name) :
	PartyBase(name, std::vector<UnitData>())
{}

PartyBase::PartyBase(std::string name, std::vector<UnitData> unit_data) :
	_party_name(std::move(name)) {
	for (UnitData& data : unit_data) {
		insertUnit(data);
	}
}
PartyBase::PartyBase(PartyData data) :
	PartyBase(data.name, data.unit_data)
{}

void PartyBase::startTurn(PartyBase& turn_party) {
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
/*Use this function to determine when to change turns
*/
bool PartyBase::isDone() {
	bool isDone = false;
	for (UnitPtr& unit : _units) {
		isDone = isDone || unit->isTired(); // || unit->isDead();
	}
	return isDone;
}

Party& PartyBase::getParty(Passkey<Map> key) {
	return *(Party*)this;
}

bool PartyBase::hasUnit(const Unit& unit) const {
	return (getPosition(unit) != _units.end());
}

bool PartyBase::operator==(const PartyBase & other) const {
	return this == &other;
}

void PartyBase::insertUnit(UnitData unit) {

	_units.emplace_back(std::move( new Unit(unit)));
	_units.back()->_party = this;
}

void PartyBase::changeParty(Unit & unit, PartyBase& new_party) {
	Expects(hasUnit(unit));
	auto it  = getPosition(unit);
	unit._party = &new_party;
	new_party._units.push_back(std::move(*it));
	_units.erase(it);
}
