#pragma once

#include "Weapon.h"

class BronzeSword : public Weapon {
private:
	inline static std::shared_ptr<WeaponInfo> _shared_info = std::make_shared<WeaponInfo>(
		"Bronze Sword",
		WeaponType::values::SWD,
		std::array<int, CombatStats::size>{ 5, 90, 0, 5, 0 }
	);
public:
	BronzeSword();
	BronzeSword(const BronzeSword& a) = default;
	BronzeSword(BronzeSword&& a) = default;
	BronzeSword& operator=(const BronzeSword& rhs) = default;
	BronzeSword& operator=(BronzeSword&& rhs) = default;
	~BronzeSword() override = default;

	bool can_equip(Unit& unit, EquipSlot slot) const override;
};
