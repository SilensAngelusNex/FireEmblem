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

std::vector<UnitPtr>::const_iterator PartyBase::getPosition(const Unit & unit) const {
	return std::find_if(cbegin(), cend(), [&](const UnitPtr& a) -> bool { return a.get() == &unit; });
}

std::vector<UnitPtr>::iterator PartyBase::getPosition(const Unit & unit) {
	return std::find_if(begin(), end(), [&](const UnitPtr& a) -> bool { return a.get() == &unit; });
}

Party& PartyBase::getParty(Passkey<Map> key) {
	return *reinterpret_cast<Party*>(this);
}

void PartyBase::insertUnit(UnitData unit) {
	_units.emplace_back(std::move(new Unit(unit)));
	_units.back()->_party = this;
}

bool PartyBase::hasUnit(const Unit& unit) const {
	return (getPosition(unit) != _units.end());
}

void PartyBase::insertUnit(Unit & unit) {
	Expects(!hasUnit(unit) && unit._party != nullptr);
	auto it = unit._party->getPosition(unit);
	_units.push_back(std::move(*it));
	unit._party->_units.erase(it);
	unit._party = this;
}


bool PartyBase::operator==(const PartyBase & other) const {
	return this == &other;
}


