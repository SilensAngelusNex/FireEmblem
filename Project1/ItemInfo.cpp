#include "ItemInfo.h"

EquipInfo::EquipInfo() :
	EquipInfo("~NULL ITEM~", {}, { 1 })
{}

EquipInfo::EquipInfo(std::string name) :
	EquipInfo(name, {}, { 1 })
{}

EquipInfo::EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats, const std::array<bool, 32> range) :
	_name(std::move(name)),
	_stats(std::move(base_stats)),
	_range(std::move(range))
{}

int EquipInfo::operator[](CombatStats stat) const {
	return _stats[stat];
}

bool EquipInfo::operator[](size_t distance) const {
	return _range[distance];
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