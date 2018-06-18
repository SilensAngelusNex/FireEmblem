#include "PartyBase.h"

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

PartyBase::const_iterator PartyBase::getPosition(const Unit & unit) const {
	return std::find_if(_units.cbegin(), _units.cend(), [&](const Unit& a) -> bool { return a == unit; });
}

PartyBase::iterator PartyBase::getPosition(const Unit & unit) {
	return std::find_if(_units.begin(), _units.end(), [&](const Unit& a) -> bool { return a == unit; });
}

Party& PartyBase::getParty(Passkey<Map> key) {
	return *reinterpret_cast<Party*>(this);
}

void PartyBase::insertUnit(UnitData unit) {
	_units.emplace_back(unit);
	_units.back()._party = this;
}

bool PartyBase::hasUnit(const Unit& unit) const {
	return (getPosition(unit) != _units.cend());
}

void PartyBase::insertUnit(Unit & unit) {
	Expects(!hasUnit(unit) && unit._party != nullptr);
	auto it = unit._party->getPosition(unit);
	_units.emplace_back(std::move(*it));
	unit._party->_units.erase(std::move(it));
	unit._party = this;
}


bool PartyBase::operator==(const PartyBase & other) const {
	return this == &other;
}

bool PartyBase::operator!=(const PartyBase & other) const {
	return this != &other;
}
