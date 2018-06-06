#include "Swords.h"

BasicWeapon::BasicWeapon(std::shared_ptr<WeaponInfo> info) :
	Weapon(info)
{}

bool BasicWeapon::can_equip(Unit&  /*unit*/, EquipSlot  /*slot*/) const {
	// TODO(Weston): check weapon rank
	return true;
}

std::unique_ptr<Weapon> WeaponFactory::makeBronzeSword() {
	return std::make_unique<BasicWeapon>(_bronze_sword);
}
