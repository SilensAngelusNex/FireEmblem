#include "Weapon.h"
#include "Unit.h"

Weapon::Weapon(std::shared_ptr<WeaponInfo> info) :
	_info(std::move(info))
{}

bool Weapon::is_weapon() const {
	return true;
}

const std::string& Weapon::getName() const {
	return _info->_name;
}

Damage Weapon::get_normal_damage(const Unit& attacker, const Unit&  /*defender*/) const {
	return Damage(attacker.getStats().might(), dmg_type());
}

Damage Weapon::get_crit_damage(const Unit& attacker, const Unit&  /*defender*/) const {
	return Damage(attacker.getStats().might(), dmg_type(), true);
}

SingleRange Weapon::getAttackRange() const {
	return _info->_range;
}

int Weapon::avoid(const AttributeList& stats) const {
	return (*_info)[CombatStats::values::AVOID] + 2 * stats[AttribType::values::SPD] + stats[AttribType::values::SKL];
}

int Weapon::dodge(const AttributeList& stats) const {
	return (*_info)[CombatStats::values::DODGE] + stats[AttribType::values::SKL] + stats[AttribType::values::SPD] / 2;
}

int Weapon::hit(const AttributeList& stats) const {
	return (*_info)[CombatStats::values::HIT] + 2 * stats[AttribType::values::SKL] + stats[AttribType::values::SPD];
}

int Weapon::crit(const AttributeList& stats) const {
	return (*_info)[CombatStats::values::CRIT] + (2 * stats[AttribType::values::SKL] + stats[AttribType::values::CHA]) / 3;
}

int Weapon::might(const AttributeList& stats) const {
	return (*_info)[CombatStats::values::MIGHT] + stats[_info->_offensive];
}

int Weapon::atk_spd(const AttributeList& stats) const {
	return (*_info)[CombatStats::values::ATK_SPD] + stats[AttribType::values::SPD];
}

AttribType Weapon::dmg_type() const {
	return _info->_defensive;
}