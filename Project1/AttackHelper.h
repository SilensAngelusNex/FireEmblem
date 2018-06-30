#pragma once
#include "MapHelper.h"
#include "MoveHelper.h"
#include <vector>
#include "GridMap.h"
#include "MapHelper.h"
#include "reference_logic.h"
#include "GridCell.h"
#include "ID.h"

class Unit;
class GridCell;
class AttackHelper :
	private MoveHelper
{
public:
	using MoveHelper::MoveHelper;
	using MoveHelper::getEquipedAttackIDs;
	using MoveHelper::getEquipableAttackIDs;
};

