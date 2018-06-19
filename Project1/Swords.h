#pragma once

#include "Weapon.h"
#include "ItemInfo.h"

class BasicWeapon : public Weapon {
public:
	BasicWeapon(std::shared_ptr<WeaponInfo> info);
	BasicWeapon(const BasicWeapon& a) = default;
	BasicWeapon(BasicWeapon&& a) = default;
	BasicWeapon& operator=(const BasicWeapon& rhs) = default;
	BasicWeapon& operator=(BasicWeapon&& rhs) = default;
	~BasicWeapon() override = default;

	bool can_equip(Unit& unit) const override;
	bool can_equip(Unit& unit, EquipSlot slot) const override;
};

class WeaponFactory {
private:
	inline static std::shared_ptr<WeaponInfo> _bronze_sword = std::make_shared<WeaponInfo>(
		WeaponInfo(
			"Bronze Sword",
			WeaponType::values::SWD,
			{ 5, 90, 0, 5, 0, 0 }
			)
		);
public:
	static std::unique_ptr<Weapon> makeBronzeSword();
};