#pragma once
#include "CommandBase.h"
#include "logical_reference_wrapper.h"
#include <optional>
class Unit;
class MoveCommand;

class UndoMoveCommand : public CommandBase {
private:
	Unit& _unit;
	std::optional<logical_reference_wrapper<MoveCommand>> _command;
public:
	UndoMoveCommand(Chapter& chapter, Unit& unit);
	bool isValid() const;
	bool doExecute();
};