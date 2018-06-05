#pragma once
#include <array>

#include "Enum.h"
#include "EnumContainer.h"

enum class _MOBILITY_TYPES { GROUNDED, FLYING, AQUATIC, ENUM_END };
using MobilityType = Enum<_MOBILITY_TYPES>;
template<typename T>
using MobilityList = EnumContainer<T, MobilityType>;
