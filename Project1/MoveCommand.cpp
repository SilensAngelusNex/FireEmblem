#include "MoveCommand.h"
#include "Chapter.h"
#include "UnitPath.h"

MoveCommand::MoveCommand(Chapter& chapter, UnitPath path) :
	CommandBase(chapter, CommandType::values::MOVE),
	_path(path)
{}

bool MoveCommand::isValid() const {
	bool my_turn = *_path._unit.getParty() == _chapter.getTurnParty();
	bool is_located = &_path.front() == _chapter._map.getCell(_path._unit);
	return my_turn && is_located && !_path._unit.isTired() && !_path._unit.getHealth().isDead();
}

bool MoveCommand::doExecute() {

	const Unit& unit = _path._unit;
	unit.getMobility().tire();
	GridCell* current_cell = _chapter._map.getCell(unit);
	for (auto& pair : _path) {
		if (!unit.getMobility().canPass(_chapter._map.getUnit(pair.second))) {
			// Walked into a stealthed unit or the like
			//Add logic for that
			return true;
		}
		if (!_chapter._map.hasUnit(pair.second)) { //Skip over units we can move through add skill logic for that
			_chapter._map.moveUnit(current_cell->_id, pair.second.get()._id);
			current_cell = _chapter._map.getCell(unit);
		}
	}
	return true;
}