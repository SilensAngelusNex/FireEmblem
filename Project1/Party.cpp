#include "Party.h"

#include <utility>

Party::Party() 
= default;

Party::Party(std::string name) : PartyBase(std::move(name))
{}

Party::Party(std::string name, std::vector<UnitData> unit_data) : PartyBase(std::move(name), std::move(unit_data))
{}

Party::Party(PartyData data) : PartyBase(std::move(data))
{}

void Party::startTurn(PartyBase& turn_party) {
	if (this == &turn_party) {
		for (auto& unit : _units) {
			unit->refresh();
		}
	}
	else {
		for (auto& unit : _units) {
			unit->newTurn();
		}
	}
}

void Party::insertUnit(UnitData unit) {
	_units.emplace_back(std::make_unique<Unit>(unit));
	_units.back()->setParty(this);
}

void Party::insertUnit(Unit::UniquePtr unit) {
	Expects(unit != nullptr && unit->getParty() == nullptr);
	_units.emplace_back(std::move(unit));
	_units.back()->setParty(this);
}

Unit::UniquePtr Party::dropUnit(Unit& unit) {
	Expects(hasUnit(unit));
	auto it = getPosition(unit);
	Unit::UniquePtr temp = std::move(*it);
	_units.erase(it);
	temp->setParty(nullptr);
	return temp;
}

/*Use this function to determine when to change turns
*/
bool Party::isDone() const{
	bool isDone = true;
	for (auto& unit : _units) {
		isDone &= unit->isTired() || unit->getBattleInfo().isDead();
	}
	return isDone;
}

std::vector<Unit::Ref> Party::getUnits() {
	auto vec = std::vector<Unit::Ref>();
	for (auto& unit : _units) {
		vec.emplace_back(*unit);
	}
	return vec;
}

std::vector<Unit::Ref> Party::getOtherUnits(const Unit& unit) {
	auto vec = std::vector<Unit::Ref>();
	for (auto& other : _units) {
		if (unit != *other) {
			vec.emplace_back(*other);
		}
	}
	return vec;
}

std::vector<Unit::ConstRef> Party::getUnits() const {
	auto vec = std::vector<Unit::ConstRef>();
	for (auto& unit : _units) {
		vec.emplace_back(*unit);
	}
	return vec;
}

std::vector<Unit::ConstRef> Party::getOtherUnits(const Unit& unit) const{
	auto vec = std::vector<Unit::ConstRef>();
	for (auto& other : _units) {
		if (unit != *other) {
			vec.emplace_back(*other);
		}
	}
	return vec;
}
