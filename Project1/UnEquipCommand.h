#pragma once
#include "CommandBase.h"
#include "Item.h"
class Unit;
class Item;

class UnEquipCommand : public CommandBase {
private:
	Unit & _unit;
	EquipSlot _slot;

public:
	UnEquipCommand(Chapter& chapter, Unit& unit, EquipSlot slot);
	bool isValid() const;
	bool doExecute();
};