#include "Swords.h"

BronzeSword::BronzeSword() :
	Weapon(_shared_info)
{}

bool BronzeSword::can_equip(Unit&  /*unit*/, EquipSlot  /*slot*/) const {
	// TODO(Weston): check weapon rank
	return true;
}