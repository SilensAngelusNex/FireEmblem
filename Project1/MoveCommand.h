#pragma once
#include "CommandBase.h"
#include "UnitPath.h"

class MoveCommand : public CommandBase {
private:
	UnitPath _path;
public:
	MoveCommand(Chapter& chapter, UnitPath path); 
	bool isValid() const;
	bool doExecute();
};



