#include "Swords.h"

const std::string BronzeSword::_name = "Bronze Sword";

const std::string & BronzeSword::getName() const {
	return _name;
}

bool BronzeSword::can_equip(Unit &  /*unit*/, EquipSlot  /*slot*/) const {
	// TODO(Weston): check weapon rank
	return true;
}

int BronzeSword::hit(const AttributeList& stats) const {
	return 90 + Weapon::hit(stats);
}

int BronzeSword::crit(const AttributeList& stats) const {
	return 5 + Weapon::crit(stats);
}

int BronzeSword::might(const AttributeList& stats) const {
	return 5 + Weapon::might(stats);
}


