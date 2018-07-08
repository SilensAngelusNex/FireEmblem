#include "WaitCommand.h"
#include "Chapter.h"
#include "Unit.h"
#include "Party.h"

WaitCommand::WaitCommand(Chapter& chapter, Unit& unit) :
	CommandBase(chapter, CommandType::values::WAIT),
	_unit(unit)
{}
bool WaitCommand::isValid() const {
	return *_unit.getParty() == _chapter.getTurnParty() && !_unit.getTurnInfo().isTired();
}
bool WaitCommand::doExecute() {
	_unit.getTurnInfo().tire();
	return true;
}

