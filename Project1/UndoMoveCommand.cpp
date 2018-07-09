#include "UndoMoveCommand.h"
#include "MoveCommand.h"
#include "Unit.h"
#include "Chapter.h"
#include "GridCell.h"

UndoMoveCommand::UndoMoveCommand(Chapter & chapter, Unit & unit):
	CommandBase(chapter, CommandType::values::UNDO_MOVE),
	_unit(unit)
{
	if (_unit.getTurnInfo().getLastMove().has_value()) {
		_command.emplace(_unit.getTurnInfo().getLastMove().value());
	}
}

bool UndoMoveCommand::isValid() const {
	bool valid = CommandBase::isValid();
	valid &= _command.has_value();
	valid &= std::find(_chapter._reversable_moves.begin(), _chapter._reversable_moves.end(), _command) != _chapter._reversable_moves.end();
	valid &=  *_unit.getParty() == _chapter.getTurnParty();
	valid &= _command->get()._path.back() == *_chapter._map.getCell(_unit);
	valid &= _unit == _command->get()._path._unit;
	valid &= !_chapter._map.hasUnit(_command->get()._path.front());
	return valid && !_unit.isTired() && !_unit.getHealth().isDead();
}

bool UndoMoveCommand::doExecute() {//warp back for now, pretend there is no pass through skills to worry about
	GridCell& location = *_chapter._map.getCell(_unit);
	_chapter._map.moveUnit(_chapter._map[_unit], _command->get()._path.front()._id);
	_chapter._reversable_moves.remove(_command.value());
	_unit.getTurnInfo().undoLastMove();

	return false;
}
