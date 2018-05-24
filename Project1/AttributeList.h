#pragma once

#include <array>

#include "Enum.h"
#include "EnumContainer.h"

enum class _ATTRIB_TYPES { STR, MAG, SKL, SPD, CON, CHA, DEF, RES, ENUM_END };

using AttribType = Enum<_ATTRIB_TYPES>;
using AttributeList = EnumContainer<AttribType>;

bool runAttributeListTests();
