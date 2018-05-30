#include "ItemInfo.h"

EquipInfo::EquipInfo() :
	EquipInfo("~NULL ITEM~", {})
{}

EquipInfo::EquipInfo(std::string name) :
	EquipInfo(name, {})
{}

EquipInfo::EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats) :
	_name(std::move(name)),
	_stats(std::move(base_stats))
{}

int EquipInfo::operator[](CombatStats stat) {
	return _stats[stat];
}

WeaponInfo::WeaponInfo() :
	WeaponInfo("~NULL WEAPON~", WeaponType::values::SWD, AttribType::values::STR, AttribType::values::DEF, {})
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type) :
	WeaponInfo(name, type, AttribType::values::STR, AttribType::values::DEF, {})
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type, std::array<int, CombatStats::size> base_stats) :
	WeaponInfo(name, type, AttribType::values::STR, AttribType::values::DEF, {})
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type, AttribType offensive_stat, AttribType defensive_stat, std::array<int, CombatStats::size> base_stats) :
	EquipInfo(name, base_stats),
	_type(type),
	_offensive(offensive_stat),
	_defensive(defensive_stat)
{}