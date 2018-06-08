#include "ItemInfo.h"

EquipInfo::EquipInfo() :
	EquipInfo("~NULL ITEM~", {}, { true })
{}

EquipInfo::EquipInfo(std::string name) :
	EquipInfo(name, {}, { true })
{}

EquipInfo::EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats) :
	EquipInfo(name, base_stats, { true })
{}

EquipInfo::EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats, std::array<bool, 32> range) :
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
	WeaponInfo("~NULL WEAPON~", WeaponType::values::SWD, AttribType::values::STR, AttribType::values::DEF, {}, { true })
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type) :
	WeaponInfo(name, type, AttribType::values::STR, AttribType::values::DEF, {}, { true })
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type, std::array<int, CombatStats::size> base_stats) :
	WeaponInfo(name, type, AttribType::values::STR, AttribType::values::DEF, {}, { true })
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type, AttribType offensive_stat, AttribType defensive_stat, std::array<int, CombatStats::size> base_stats) :
	WeaponInfo(name, type, offensive_stat, defensive_stat, {}, { true })
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type, AttribType offensive_stat, AttribType defensive_stat, std::array<int, CombatStats::size> base_stats, std::array<bool, 32> range) :
	EquipInfo(name, base_stats, range),
	_type(type),
	_offensive(offensive_stat),
	_defensive(defensive_stat)
{}

WeaponInfo::WeaponInfo(EquipInfo info, WeaponType type) :
	WeaponInfo(info, type, AttribType::values::STR, AttribType::values::DEF)
{}

WeaponInfo::WeaponInfo(EquipInfo info, WeaponType type, AttribType offensive_stat, AttribType defensive_stat) :
	EquipInfo(std::move(info)),
	_type(type),
	_offensive(offensive_stat),
	_defensive(defensive_stat)
{}
