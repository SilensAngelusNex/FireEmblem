#include "Unit.h"

#include <utility>

Unit::Unit(IDENTITY name, CONTEXT& context, AttributeList stats) :
	_id(std::move(name)),
	_context(context),	
	_stats(*this, stats),
	_exp(*this, context),
	_inv(*this),
	_combat(*this), 
	_mobility(*this, 50, MobilityList<bool>({true}))
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

InventoryCommandable& Unit::getInventory() {
	return _inv;
}

Combat& Unit::getCombat() {
	return _combat;
}

void Unit::refresh() {
	//TODO(Torrey): Code start of turn stuff.
}
void Unit::newTurn() {
	//TODO(Torrey): code start of turn stuff.
}
bool Unit::isTired() const {
	return true; //TODO(Torrey): add tired logic
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
