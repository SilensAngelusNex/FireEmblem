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
	return std::find_if(cbegin(), cend(), [&](const UnitPtr& a) -> bool { return a.get() == &unit; });
}

PartyBase::iterator PartyBase::getPosition(const Unit & unit) {
	return std::find_if(begin(), end(), [&](const UnitPtr& a) -> bool { return a.get() == &unit; });
}

Party& PartyBase::getParty(Passkey<Map> key) {
	return *reinterpret_cast<Party*>(this);
}

void PartyBase::insertUnit(UnitData unit) {
	_units.emplace_back(std::make_unique<Unit>(unit));
	_units.back()->_party = this;
}

bool PartyBase::hasUnit(const Unit& unit) const {
	return (getPosition(unit) != cend());
}

void PartyBase::insertUnit(UnitPtr& unit) {
	Expects(!hasUnit(*unit) && unit != nullptr);
	if (unit->_party != nullptr) {		
		_units.emplace_back(std::move(unit->_party->dropUnit(*unit)));
		_units.back()->_party = this;
	}
	else {
		_units.emplace_back(std::move(unit));
		_units.back()->_party = this;
	}
}

UnitPtr PartyBase::dropUnit(Unit& unit) {
	Expects(hasUnit(unit));
	return dropUnit(getPosition(unit));
}

UnitPtr PartyBase::dropUnit(const iterator& pos) {
	UnitPtr temp = std::move(*pos);
	_units.erase(pos);
	temp->_party = nullptr;
	return temp;
}


bool PartyBase::operator==(const PartyBase & other) const {
	return this == &other;
}

bool PartyBase::operator!=(const PartyBase & other) const {
	return this != &other;
}
