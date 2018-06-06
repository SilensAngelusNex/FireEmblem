#pragma once

#include <array>

#include "AttributeList.h"
#include "WeaponList.h"


enum class _COMBAT_STATS { MIGHT, HIT, AVOID, CRIT, DODGE, ATK_SPD, ENUM_END };
using CombatStats = Enum<_COMBAT_STATS>;


class EquipInfo {
public:
	const std::string _name;
	const EnumContainer<int, CombatStats> _stats;
	const std::array<bool, 32> _range;

	EquipInfo();
	EquipInfo(std::string name);
	EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats, const std::array<bool, 32> range);

	int operator[] (CombatStats stat) const;
	bool operator[] (size_t range) const;
};

class WeaponInfo : public EquipInfo {
public:
	const WeaponType _type;
	const AttribType _offensive;
	const AttribType _defensive;

	WeaponInfo();
	WeaponInfo(std::string name, WeaponType type);
	WeaponInfo(std::string name, WeaponType type, std::array<int, CombatStats::size> base_stats);
	WeaponInfo(std::string name, WeaponType type, AttribType offensive_stat, AttribType defensive_stat, std::array<int, CombatStats::size> base_stats);
};