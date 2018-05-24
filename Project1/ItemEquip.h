#pragma once

#include "Item.h"
#include "AttributeList.h"
#include "Damage.h"

class ItemEquip : public Item {
public:
	ItemEquip() = default;
	ItemEquip(const ItemEquip& a) = default;
	ItemEquip(ItemEquip&& a) = default;
	ItemEquip& operator=(const ItemEquip& rhs) = default;
	ItemEquip& operator=(ItemEquip&& rhs) = default;
	~ItemEquip() override = default;

	void equip(Unit& unit, EquipSlot slot) override;
	virtual bool can_equip(Unit& unit, EquipSlot slot) const = 0;

	bool is_equippable() const override;
	virtual bool is_weapon() const;

	virtual Damage get_normal_damage(const Unit& attacker, const Unit& defender) const;
	virtual Damage get_crit_damage(const Unit& attacker, const Unit& defender) const;

	virtual int avoid(const AttributeList& stats) const = 0;
	virtual int dodge(const AttributeList& stats) const = 0;
	virtual int hit(const AttributeList& stats) const = 0;
	virtual int crit(const AttributeList& stats) const = 0;
	virtual int might(const AttributeList& stats) const = 0;
	virtual int atk_spd(const AttributeList& stats) const = 0;
	virtual AttribType dmg_type() const = 0;

};