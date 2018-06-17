#include "ItemEquip.h" 
#include "Unit.h"

void ItemEquip::equip(Unit& unit, EquipSlot slot) {
	if (can_equip(unit, slot)) {
		unit.getInventoryInternal().equipInternal(slot, this);
	}
	else {
		throw GameException("Item cannot be equipped to the given slot.");
	}
}

bool ItemEquip::is_weapon() const {
	return false;
}

Damage ItemEquip::get_normal_damage(const Unit&  /*attacker*/, const Unit&  /*defender*/) const {
	throw GameException("Non-weapons have no associated damage.");
}

Damage ItemEquip::get_crit_damage(const Unit&  /*attacker*/, const Unit&  /*defender*/) const {
	throw GameException("Non-weapons have no associated damage.");
}

SingleRange ItemEquip::getAttackRange() const {
	return SingleRange();
}

SingleRange ItemEquip::getAssistRange() const {
	return SingleRange();
}

bool ItemEquip::is_equippable() const {
	return true;
}
int ItemEquip::avoid(const AttributeList&  /*stats*/) const {
	return 0;
}
int ItemEquip::dodge(const AttributeList&  /*stats*/) const {
	return 0;
}
int ItemEquip::hit(const AttributeList&  /*stats*/) const {
	return 0;
}
int ItemEquip::crit(const AttributeList&  /*stats*/) const {
	return 0;
}
int ItemEquip::might(const AttributeList&  /*stats*/) const {
	return 0;
}
int ItemEquip::atk_spd(const AttributeList&  /*stats*/) const {
	return 0;
}
AttribType ItemEquip::dmg_type() const {
	return AttribType::values::DEF;
}