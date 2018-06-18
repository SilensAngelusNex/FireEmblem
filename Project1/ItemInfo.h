#pragma once

#include <array>
#include <vector>

#include "AttributeList.h"
#include "IterableBitset.h"
#include "WeaponList.h"
#include "Range.h"


enum class _COMBAT_STATS { MIGHT, HIT, AVOID, CRIT, DODGE, ATK_SPD, ENUM_END };
using CombatStats = Enum<_COMBAT_STATS>;


class EquipInfo {
public:
	const std::string _name;
	const EnumContainer<int, CombatStats> _stats;
	const Range _range;

	explicit EquipInfo();
	EquipInfo(std::string name);
	EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats);
	EquipInfo(std::string name, std::array<int, CombatStats::size> base_stats, Range range);

	int operator[] (CombatStats stat) const;
	bool operator[] (size_t distance) const;
};

class WeaponInfo : public EquipInfo {
public:
	const WeaponType _type;
	const AttribType _offensive;
	const AttribType _defensive;

	explicit WeaponInfo();
	WeaponInfo(std::string name, WeaponType type);
	WeaponInfo(std::string name, WeaponType type, std::array<int, CombatStats::size> base_stats);
	WeaponInfo(std::string name, WeaponType type, AttribType offensive_stat, AttribType defensive_stat, std::array<int, CombatStats::size> base_stats);
	WeaponInfo(std::string name, WeaponType type, AttribType offensive_stat, AttribType defensive_stat, std::array<int, CombatStats::size> base_stats, Range range);

	WeaponInfo(EquipInfo info, WeaponType type);
	WeaponInfo(EquipInfo info, WeaponType type, AttribType offensive_stat, AttribType defensive_stat);
};