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
	_mobility(50, MobilityList<bool>(std::array<bool, MobilityType::size>{true}))
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

InventoryCommandable& Unit::getInventory() {
	return _inv;
}

Combat& Unit::getCombat() {
	return _combat;
}

Health & Unit::getHealth() {
	return _health;
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
