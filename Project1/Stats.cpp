#include "Stats.h"

#include <utility>
#include "Unit.h"
#include "InventoryViewable.h"


Stats::Stats(Unit& owner) : Stats(owner, AttributeList(), AttributeList(), WeaponList()) {}

Stats::Stats(Unit& owner, AttributeList attribs) : Stats(owner, std::move(attribs), AttributeList(), WeaponList()) {}

Stats::Stats(Unit& owner, AttributeList attribs, AttributeList growths) : Stats(owner, std::move(attribs), std::move(growths), WeaponList()) {}

Stats::Stats(Unit& owner, AttributeList attribs, AttributeList growths, WeaponList proficiencies) :
	Component<Unit>(owner),
	_attribs(std::move(attribs)),
	_growths(std::move(growths)),
	_proficiencies(std::move(proficiencies)),
	_health(_growths[AttribType::values::CON])
{}

void Stats::init() {
	_inv = &_owner.getInventory();
}


AttributeList& Stats::getAttribs() {
	return _attribs;
}
AttributeList& Stats::getGrowths() {
	return _growths;
}
WeaponList& Stats::getWeaponProficiencies() {
	return _proficiencies;
}

const AttributeList& Stats::getAttribs() const {
	return _attribs;
}
const AttributeList& Stats::getGrowths() const {
	return _growths;
}
const WeaponList& Stats::getWeaponProficiencies() const {
	return _proficiencies;
}

int Stats::avoid() const {
	return _inv->avoid(Passkey<Stats>());
}

int Stats::dodge() const {
	return _inv->dodge(Passkey<Stats>());
}

int Stats::hit() const {
	return _inv->hit(Passkey<Stats>());
}

int Stats::crit() const {
	return _inv->crit(Passkey<Stats>());
}

int Stats::might() const {
	return _inv->might(Passkey<Stats>());
}

int Stats::atk_spd() const {
	return _inv->atk_spd(Passkey<Stats>());
}
