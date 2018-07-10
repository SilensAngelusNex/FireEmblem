#include "EquipCommand.h"
#include "Unit.h"
#include "Chapter.h"
EquipCommandIndex::EquipCommandIndex(Chapter & chapter, Unit & unit, int index, EquipSlot slot):
	CommandBase(chapter, CommandType::values::EQUIP),
	_unit(unit),
	_index(index),
	_slot(slot)
{}

bool EquipCommandIndex::isValid() const {
	bool valid = CommandBase::isValid();
	valid &= *_unit.getParty() == _chapter.getTurnParty();
	valid &= _unit.getInventoryInternal().canEquip(_slot, _index);
	return valid && !_unit.getTurnInfo().isTired() && !_unit.getHealth().isDead();
}

bool EquipCommandIndex::doExecute() {
	_unit.getInventoryInternal().equip(_slot, _index);
	return true;
}

EquipCommandRef::EquipCommandRef(Chapter & chapter, Unit & unit, Item& item, EquipSlot slot) :
	CommandBase(chapter, CommandType::values::EQUIP),
	_unit(unit),
	_item(item),
	_slot(slot)
{}

bool EquipCommandRef::isValid() const {
	bool valid = CommandBase::isValid();
	valid &= *_unit.getParty() == _chapter.getTurnParty();
	valid &= _unit.getInventoryInternal().canEquip(_slot, _item);
	return valid && !_unit.getTurnInfo().isTired() && !_unit.getHealth().isDead();
}

bool EquipCommandRef::doExecute() {
	_unit.getInventoryInternal().equip(_slot, _item);
	return true;
}

EquipCommandPtr::EquipCommandPtr(Chapter & chapter, Unit & unit, std::unique_ptr<Item> item, EquipSlot slot) :
	CommandBase(chapter, CommandType::values::EQUIP),
	_unit(unit),
	_item(std::move(item)),
	_slot(slot)
{}

bool EquipCommandPtr::isValid() const {
	bool valid = CommandBase::isValid();
	valid &= *_unit.getParty() == _chapter.getTurnParty();
	valid &= _unit.getInventoryInternal().canEquip(_slot, _item.get());
	return valid && !_unit.getTurnInfo().isTired() && !_unit.getHealth().isDead();
}

bool EquipCommandPtr::doExecute() {
	_unit.getInventoryInternal().equip(_slot, std::move(_item));
	return true;
}