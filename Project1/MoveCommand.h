#pragma once
#include "CommandBase.h"
#include "UnitPath.h"

class MoveCommand : public CommandBase {
private:
	UnitPath _path;
	Unit& _unit;
public:
	MoveCommand(Chapter& chapter, Unit& unit, UnitPath path); 
	bool isValid() const;
	bool doExecute();
};



