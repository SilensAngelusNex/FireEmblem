#include "Unit.h"

#include <utility>

Unit::Unit(IDENTITY name, CONTEXT& context, AttributeList stats) :
	_id(std::move(name)),
	_context(context),	
	_stats(*this, stats),
	_exp(*this, context),
	_inv(*this),
	_combat(*this),
	_health(*this),
	_mobility(*this, 50, MobilitySet(std::array<bool, MobilityType::size>{true})),
	_turn_info(*this)
{}

const IDENTITY& Unit::getIdentity() const {
	return _id;
}

const Stats& Unit::getStats() const {
	return _stats;
}

const Mobility& Unit::getMobility() const {
	return _mobility;
}

const Experience& Unit::getExperience() const {
	return _exp;
}

const InventoryViewable& Unit::getInventory() const {
	return _inv;
}

const Health & Unit::getHealth() const {
	return _health;
}

const TurnInfo & Unit::getTurnInfo() const
{
	return _turn_info;
}

const PartyBase* Unit::getParty() const{
	return _party;
}

InventoryCommandable& Unit::getInventory() {
	return _inv;
}

Combat& Unit::getCombat() {
	return _combat;
}

void Unit::refresh() {
	_turn_info.refresh();
}
void Unit::newTurn() {
	//TODO(T or W): code start of turn stuff.
}
bool Unit::isTired() const {
	return _turn_info.isTired(); 
}
Health & Unit::getHealth() {
	return _health;
}

TurnInfo & Unit::getTurnInfo()
{
	return _turn_info;
}

PartyBase* Unit::getParty() {
	return _party;
}

PartyBase* Unit::setParty(PartyBase* other_party) {
	std::swap(_party, other_party);
	return other_party;
}

Stats& Unit::getStats() {
	return _stats;
}

Mobility& Unit::getMobility() {
	return _mobility;
}

Experience& Unit::getExperience() {
	return _exp;
}

Inventory& Unit::getInventoryInternal() {
	return _inv;
}

CONTEXT& Unit::getContext() {
	return _context;
}

bool Unit::operator==(const Unit& unit) const {
	return this == &unit;
}

bool Unit::operator!=(const Unit & unit) const
{
	return this != &unit;
}
