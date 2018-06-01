#pragma once

#include "AttributeList.h"
#include "MobilityList.h"
#include "Component.h"
#include "WeaponList.h"
#include "Health.h"

class Unit;
class InventoryViewable;


class Stats : Component<Unit> {
	AttributeList _attribs;
	AttributeList _growths;
	WeaponList _proficiencies;
	Health _health;
	MobilityType _mobility;

public:
	explicit Stats(Unit& owner);
	explicit Stats(Unit& owner, AttributeList attribs);
	explicit Stats(Unit& owner, AttributeList attribs, AttributeList growths);
	explicit Stats(Unit& owner, AttributeList attribs, AttributeList growths, WeaponList proficiencies);

	AttributeList& getAttribs();
	AttributeList& getGrowths();
	WeaponList& getWeaponProficiencies();
	MobilityType& getMobilityType();
	
	const AttributeList& getAttribs() const;
	const AttributeList& getGrowths() const;
	const WeaponList& getWeaponProficiencies() const;

	int avoid() const;
	int dodge() const;
	int hit() const;
	int crit() const;
	int might() const;
	int atk_spd() const;
};