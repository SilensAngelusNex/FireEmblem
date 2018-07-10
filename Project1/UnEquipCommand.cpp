#include "UnEquipCommand.h"
#include "Unit.h"
#include "Chapter.h"
UnEquipCommand::UnEquipCommand(Chapter & chapter, Unit & unit, EquipSlot slot) :
	CommandBase(chapter, CommandType::values::EQUIP),
	_unit(unit),
	_slot(slot)
{}

bool UnEquipCommand::isValid() const {
	bool valid = CommandBase::isValid();
	valid &= *_unit.getParty() == _chapter.getTurnParty();
	valid &= _unit.getInventoryInternal().canDequip(_slot);
	return valid && !_unit.getTurnInfo().isTired() && !_unit.getHealth().isDead();
}

bool UnEquipCommand::doExecute() {
	_unit.getInventoryInternal().dequip(_slot);
	return true;
}