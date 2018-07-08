#pragma once
#include "CommandBase.h"

class Unit;
class Party;
class WaitCommand : public CommandBase {
private:
	Unit& _unit;
public:
	WaitCommand(Chapter& chapter, Unit& unit);
	bool isValid() const;
	bool doExecute();
};
