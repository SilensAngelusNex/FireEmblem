#include "Unit.h"

#include <utility>

Unit::Unit(std::string id, CONTEXT & context, AttributeList stats) :
	Unit(Identity(id), context, stats)
{}

Unit::Unit(Identity id, CONTEXT& context, AttributeList stats) :
	_id(std::move(id)),
	_context(context),	
	_stats(*this, stats),
	_exp(*this, context),
	_inv(*this),
	_combat(*this),
	_mobility(*this, 50, MobilitySet(std::array<bool, MobilityType::size>{true})),
	_battle_info(*this)
{}

Unit::Unit(UnitData data) : Unit(Identity(data.name), data.context, data.stats) {};

const Identity& Unit::getIdentity() const {
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

const PartyBase* Unit::getParty() const{
	return _id.getParty();
}

const BattleInfo& Unit::getBattleInfo() const {
	return _battle_info;
}

InventoryCommandable& Unit::getInventory() {
	return _inv;
}

BattleInfo& Unit::getBattleInfo() {
	return _battle_info;
}

Combat& Unit::getCombat() {
	return _combat;
}

void Unit::refresh() {
	//TODO(T or W): Code start of turn stuff.
}
void Unit::newTurn() {
	//TODO(T or W): code start of turn stuff.
}
bool Unit::isTired() const {
	return true; //TODO(Weston): Should this be in a component like isDead() ? 
}

PartyBase* Unit::getParty() {
	return _id.getParty();
}

PartyBase* Unit::setParty(PartyBase* other_party) {
	return _id.setParty(other_party);
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
