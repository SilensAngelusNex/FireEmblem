#include "UndoMoveCommand.h"
#include "MoveCommand.h"
#include "Unit.h"
#include "Chapter.h"
#include "GridCell.h"

UndoMoveCommand::UndoMoveCommand(Chapter & chapter, Unit & unit):
	CommandBase(chapter, CommandType::values::UNDO_MOVE),
	_unit(unit)
{}

bool UndoMoveCommand::isValid() const {
	bool valid = CommandBase::isValid();
	valid &= _unit.getTurnInfo().getLastMove().has_value();
	valid &= std::find(_chapter._reversable_moves.begin(), _chapter._reversable_moves.end(), _unit.getTurnInfo().getLastMove().value()) != _chapter._reversable_moves.end();
	valid &=  *_unit.getParty() == _chapter.getTurnParty();
	valid &= &_unit.getTurnInfo().getLastMove()->_path.back() == _chapter._map.getCell(_unit);
	valid &= _unit == _unit.getTurnInfo().getLastMove()->_path._unit;
	valid &= !_chapter._map.hasUnit(_unit.getTurnInfo().getLastMove()->_path.front());
	return valid && !_unit.isTired() && !_unit.getHealth().isDead();
}

bool UndoMoveCommand::doExecute() {//warp back for now, pretend there is no pass through skills to worry about
	GridCell& location = *_chapter._map.getCell(_unit);
	_chapter._map.moveUnit(_chapter._map[_unit], _unit.getTurnInfo().getLastMove()->_path.front()._id);
	_unit.getTurnInfo().undoLastMove();
	return false;
}
