#pragma once
#include "CommandBase.h"
class Unit;

class UndoMoveCommand : public CommandBase {
private:
	Unit& _unit;
public:
	UndoMoveCommand(Chapter& chapter, Unit& unit);
	bool isValid() const;
	bool doExecute();
};