#pragma once

#include <array>

#include "Enum.h"
#include "EnumContainer.h"

enum class _WEAPON_TYPES { SWD, AXE, LNC, KNF, BOW, ETH, AIR, FIR, WTR, LGT, DRK, ENUM_END };

using WeaponType = Enum<_WEAPON_TYPES>;
using WeaponList = EnumContainer<int, WeaponType>;

int compare(WeaponType lhs, WeaponType rhs);
bool operator<(WeaponType lhs, WeaponType rhs);
bool operator>(WeaponType lhs, WeaponType rhs);

bool runWeaponListTests();