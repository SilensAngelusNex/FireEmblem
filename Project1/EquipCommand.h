#pragma once
#include "CommandBase.h"
#include "Item.h"
class Unit;
class Item;

class EquipCommandIndex : public CommandBase {
private:
	Unit& _unit;
	int _index;
	EquipSlot _slot;
	
public:
	EquipCommandIndex(Chapter& chapter, Unit& unit, int index, EquipSlot slot);
	bool isValid() const;
	bool doExecute();
};

class EquipCommandRef : public CommandBase {
private:
	Unit & _unit;
	Item& _item;
	EquipSlot _slot;

public:
	EquipCommandRef(Chapter& chapter, Unit& unit, Item& item, EquipSlot slot);
	bool isValid() const;
	bool doExecute();
};

class EquipCommandPtr : public CommandBase {
private:
	Unit & _unit;
	std::unique_ptr<Item> _item;
	EquipSlot _slot;

public:
	EquipCommandPtr(Chapter& chapter, Unit& unit, std::unique_ptr<Item> item, EquipSlot slot);
	bool isValid() const;
	bool doExecute();
};