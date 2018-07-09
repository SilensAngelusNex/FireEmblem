#include "WaitCommand.h"
#include "Chapter.h"
#include "Unit.h"
#include "Party.h"

WaitCommand::WaitCommand(Chapter& chapter, Unit& unit) :
	CommandBase(chapter, CommandType::values::WAIT),
	_unit(unit)
{}
bool WaitCommand::isValid() const {
	bool valid = CommandBase::isValid();
	valid &= *_unit.getParty() == _chapter.getTurnParty();
	return valid && !_unit.getTurnInfo().isTired();
}
bool WaitCommand::doExecute() {
	if (_unit.getTurnInfo().getLastMove().has_value()) {
		_chapter._reversable_moves.remove(_unit.getTurnInfo().getLastMove().value());
	}
	_chapter._reversable_moves.remove(_unit.getTurnInfo().getLastMove().value());
	_unit.getTurnInfo().clearLastMove();
	_unit.getTurnInfo().tire();
	return true;
}

