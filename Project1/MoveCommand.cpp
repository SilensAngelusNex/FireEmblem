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
	bool my_turn = *_unit.getParty() == _chapter.getTurnParty();
	bool is_located = &_path.front() == _chapter._map.getCell(_unit);
	bool is_unit = _unit == _path._unit;
	bool is_not_too_far = _path.getCost() <= _unit.getTurnInfo().getRemainingMove();
	return my_turn && is_located && !_unit.isTired() && is_not_too_far  && !_unit.getHealth().isDead();
}

bool MoveCommand::doExecute() {

	GridCell* current_cell = _chapter._map.getCell(_unit);
	for (auto& pair : _path) {
		if (!_unit.getMobility().canPass(_chapter._map.getUnit(pair.second))) {
			_unit.getTurnInfo().useMovement(pair.first);//still attempted to step there, so you pay for it
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

	return true;
}