#pragma once

#include "ItemEquip.h"
#include "AttributeList.h"

class Weapon : public ItemEquip {
public:
	Weapon() = default;
	Weapon(const Weapon& a) = default;
	Weapon(Weapon&& a) = default;
	Weapon& operator=(const Weapon& rhs) = default;
	Weapon& operator=(Weapon&& rhs) = default;
	~Weapon() override = default;

	bool is_weapon() const override;
	Damage get_normal_damage(const Unit& attacker, const Unit& defender) const override;
	Damage get_crit_damage(const Unit& attacker, const Unit& defender) const override;

	int avoid(const AttributeList& stats) const override;
	int dodge(const AttributeList& stats) const override;
	int hit(const AttributeList& stats) const override;
	int crit(const AttributeList& stats) const override;
	int might(const AttributeList& stats) const override;
	int atk_spd(const AttributeList& stats) const override;
	AttribType dmg_type() const override;
};