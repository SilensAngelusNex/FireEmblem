#include "ItemInfo.h"

EquipInfo::EquipInfo() :
	EquipInfo("~NULL ITEM~", {}, Range())
{}

EquipInfo::EquipInfo(std::string name) :
	EquipInfo(std::move(name), {}, Range())
{}

EquipInfo::EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats) :
	EquipInfo(std::move(name), base_stats, std::vector<int>{})
{}

EquipInfo::EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats, Range range) :
	_name(std::move(name)),
	_stats(std::move(base_stats)),
	_range(range)
{}

int EquipInfo::operator[](CombatStats stat) const {
	return _stats[stat];
}

bool EquipInfo::operator[](size_t distance) const {
	return _range[distance];
}

WeaponInfo::WeaponInfo() :
	WeaponInfo("~NULL WEAPON~", WeaponType::values::SWD, AttribType::values::STR, AttribType::values::DEF, {}, std::vector<int>{ 1 })
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type) :
	WeaponInfo(std::move(name), type, AttribType::values::STR, AttribType::values::DEF, {}, std::vector<int>{ 1 })
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type, std::array<int, CombatStats::size> base_stats) :
	WeaponInfo(std::move(name), type, AttribType::values::STR, AttribType::values::DEF, base_stats, std::vector<int>{ 1 })
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type, AttribType offensive_stat, AttribType defensive_stat, std::array<int, CombatStats::size> base_stats) :
	WeaponInfo(std::move(name), type, offensive_stat, defensive_stat, base_stats, std::vector<int>{ 1 })
{}

WeaponInfo::WeaponInfo(std::string name, WeaponType type, AttribType offensive_stat, AttribType defensive_stat, std::array<int, CombatStats::size> base_stats, Range range) :
	EquipInfo(std::move(name), base_stats, range),
	_type(type),
	_offensive(offensive_stat),
	_defensive(defensive_stat)
{}

WeaponInfo::WeaponInfo(EquipInfo info, WeaponType type) :
	WeaponInfo(std::move(info), type, AttribType::values::STR, AttribType::values::DEF)
{}

WeaponInfo::WeaponInfo(EquipInfo info, WeaponType type, AttribType offensive_stat, AttribType defensive_stat) :
	EquipInfo(std::move(info)),
	_type(type),
	_offensive(offensive_stat),
	_defensive(defensive_stat)
{}
