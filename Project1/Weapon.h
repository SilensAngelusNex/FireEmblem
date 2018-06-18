#pragma once

#include <memory>

#include "AttributeList.h"
#include "ItemEquip.h"
#include "ItemInfo.h"

class Weapon : public ItemEquip {
protected:
	std::shared_ptr<WeaponInfo> _info;
public:
	Weapon(std::shared_ptr<WeaponInfo> info);
	Weapon(const Weapon& a) = default;
	Weapon(Weapon&& a) = default;
	Weapon& operator=(const Weapon& rhs) = default;
	Weapon& operator=(Weapon&& rhs) = default;
	~Weapon() override = default;

	bool is_weapon() const override;
	const std::string& getName() const override;

	Damage get_normal_damage(const Unit& attacker, const Unit& defender) const override;
	Damage get_crit_damage(const Unit& attacker, const Unit& defender) const override;

	Range getAttackRange() const override;

	int avoid(const AttributeList& stats) const override;
	int dodge(const AttributeList& stats) const override;
	int hit(const AttributeList& stats) const override;
	int crit(const AttributeList& stats) const override;
	int might(const AttributeList& stats) const override;
	int atk_spd(const AttributeList& stats) const override;
	AttribType dmg_type() const override;
};