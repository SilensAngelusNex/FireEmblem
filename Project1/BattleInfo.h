#pragma once

#include "Actions.h"
#include "Component.h"
#include "Health.h"

class Unit;

class BattleInfo : public Health, public Actions {
public:
	BattleInfo(Unit& owner);
};