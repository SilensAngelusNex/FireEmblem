#pragma once
#include "CommandBase.h"

class Party;
class EndCommand : public CommandBase {
private:
public:
	EndCommand(Chapter& chapter);
	bool isValid() const;
	bool doExecute();
};
