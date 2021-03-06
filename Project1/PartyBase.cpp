#include "PartyBase.h"

PartyBase::PartyBase() :
	PartyBase("~NULL PARTY~", std::vector<UnitData>())
{}

PartyBase::PartyBase(std::string name) :
	PartyBase(std::move(name), std::vector<UnitData>())
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
	return std::find_if(_units.cbegin(), _units.cend(), [&](const Unit::UniquePtr& a) -> bool { return a.get() == &unit; });
}

PartyBase::iterator PartyBase::getPosition(const Unit & unit) {
	return std::find_if(_units.begin(), _units.end(), [&](const Unit::UniquePtr& a) -> bool { return a.get() == &unit; });
}

void PartyBase::insertUnit(UnitData unit) {
	_units.emplace_back(std::make_unique<Unit>(unit));
	_units.back()->setParty(this);
}

Party& PartyBase::getParty(Passkey<GridMap> /*unused*/) {
	return *reinterpret_cast<Party*>(this);
}

const Party& PartyBase::getParty(Passkey<GridMap> /*unused*/) const {
	return *reinterpret_cast<const Party*>(this);
}

bool PartyBase::hasUnit(const Unit& unit) const {
	return (getPosition(unit) != _units.cend());
}

bool PartyBase::operator==(const PartyBase & other) const {
	return this == &other;
}

bool PartyBase::operator!=(const PartyBase & other) const {
	return this != &other;
}
