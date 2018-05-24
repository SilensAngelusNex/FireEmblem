#include "Unit.h"

#include <utility>

Unit::Unit(IDENTITY name, CONTEXT& context, AttributeList stats) :
	_id(std::move(name)),
	_context(context),	
	_stats(*this, stats),
	_exp(*this, context),
	_inv(*this),
	_combat(*this)
{
	_stats.init();
	_exp.init();
	_inv.init();
	_combat.init();
}

const IDENTITY& Unit::getIdentity() const {
	return _id;
}

const Stats& Unit::getStats() const {
	return _stats;
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

Stats& Unit::getStats() {
	return _stats;
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
