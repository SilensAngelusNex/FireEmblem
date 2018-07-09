#pragma once
#include "CommandType.h"
class Chapter;

class CommandBase {
public:
	static int _incrementor;
	const int  _command_id;
	bool isValid() const;
	bool doExecute();
	bool operator==(const CommandBase& rhs) const;
	bool operator!=(const CommandBase& rhs) const;
protected:
	Chapter & _chapter;
	const CommandType _command_type;
	CommandBase(Chapter& chapter, CommandType command_type); 
};