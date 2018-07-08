#pragma once
#include "CommandBase.h"

class Party;
class EndCommand : public CommandBase {
private:
	const Party& _party;
public:
	EndCommand(Chapter& chapter, const Party& party);
	bool isValid() const;
	bool doExecute();
};
