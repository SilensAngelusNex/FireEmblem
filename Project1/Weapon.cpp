#include "Weapon.h"
#include "Unit.h"

bool Weapon::is_weapon() const {
	return true;
}

Damage Weapon::get_normal_damage(const Unit& attacker, const Unit&  /*defender*/) const {
	return Damage(attacker.getStats().might(), dmg_type());
}

Damage Weapon::get_crit_damage(const Unit& attacker, const Unit&  /*defender*/) const {
	return Damage(attacker.getStats().might(), dmg_type(), true);
}

int Weapon::avoid(const AttributeList& stats) const {
	return 2 * stats[AttribType::values::SPD] + stats[AttribType::values::SKL];
}

int Weapon::dodge(const AttributeList& stats) const {
	return stats[AttribType::values::SKL] + stats[AttribType::values::SPD] / 2;
}

int Weapon::hit(const AttributeList& stats) const {
	return 2 * stats[AttribType::values::SKL] + stats[AttribType::values::SPD];
}

int Weapon::crit(const AttributeList& stats) const {
	return (2 * stats[AttribType::values::SKL] + stats[AttribType::values::CHA]) / 3;
}

int Weapon::might(const AttributeList& stats) const {
	return stats[AttribType::values::STR];
}

int Weapon::atk_spd(const AttributeList& stats) const {
	return stats[AttribType::values::SPD];
}

AttribType Weapon::dmg_type() const {
	return AttribType::values::DEF;
}