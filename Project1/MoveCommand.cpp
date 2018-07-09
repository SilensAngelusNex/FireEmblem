#include "MoveCommand.h"
#include "Chapter.h"
#include "UnitPath.h"
#include "Unit.h"


MoveCommand::MoveCommand(Chapter& chapter, Unit& unit, UnitPath path) :
	CommandBase(chapter, CommandType::values::MOVE),
	_path(path),
	_unit(unit)
{}

bool MoveCommand::isValid() const {
	bool valid = CommandBase::isValid();
	valid &= *_unit.getParty() == _chapter.getTurnParty();
	valid &= &_path.front() == _chapter._map.getCell(_unit);
	valid &= _unit == _path._unit;
	valid &= _path.getCost() <= _unit.getTurnInfo().getRemainingMove();
	return valid && !_unit.isTired()  && !_unit.getHealth().isDead();
}

bool MoveCommand::doExecute() {
	if (_unit.getTurnInfo().getLastMove().has_value()) {
		_chapter._reversable_moves.remove(_unit.getTurnInfo().getLastMove().value());
		_unit.getTurnInfo().clearLastMove();
	}
	GridCell* current_cell = _chapter._map.getCell(_unit);
	for (auto& pair : _path) {
		if (!_unit.getMobility().canPass(_chapter._map.getUnit(pair.second))) {
			_unit.getTurnInfo().useMovement(pair.first);//still attempted to step there, so you pay for it
			_chapter._reversable_moves.clear();
			// Walked into a stealthed unit or the like
			//Add logic for that

			return true;
		}
		if (!_chapter._map.hasUnit(pair.second)) { //Skip over units we can move through add skill logic for that
			_chapter._map.moveUnit(current_cell->_id, pair.second.get()._id);
			current_cell = _chapter._map.getCell(_unit);
			std::cout << pair.first << std::endl;
		}
	}
	_unit.getTurnInfo().useMovement(_path.getCost());
	_unit.getTurnInfo().setLastMove(*this);
	_chapter._reversable_moves.emplace_back(*this);
	return true;
}
