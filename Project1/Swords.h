#ifndef SWORDS_H
#define SWORDS_H

#include "Weapon.h"

class BronzeSword : public Weapon {
private:
	static const std::string _name;
	
public:
	BronzeSword() = default;
	BronzeSword(const BronzeSword& a) = default;
	BronzeSword(BronzeSword&& a) = default;
	BronzeSword& operator=(const BronzeSword& rhs) = default;
	BronzeSword& operator=(BronzeSword&& rhs) = default;
	~BronzeSword() override = default;

	const std::string& getName() const override;
	bool can_equip(Unit& unit, EquipSlot slot) const override;

	int hit(const AttributeList& stats) const override;
	int crit(const AttributeList& stats) const override;
	int might(const AttributeList& stats) const override;
};

#endif // !SWORDS_H
