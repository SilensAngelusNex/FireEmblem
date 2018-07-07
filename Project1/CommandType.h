#pragma once
#include "Enum.h"
enum class _COMMAND_TYPES { MOVE, UNDO_MOVE, ATTACK, ACTIVATE_SKILL, TRADE, EQUIP, USE_ITEM, WAIT, END, ENUM_END };
using CommandType = Enum<_COMMAND_TYPES>;