#pragma once
#include "CommandType.h"
class Chapter;


class CommandBase {
protected:
	Chapter& _chapter;
	const CommandType _command_type;
	CommandBase(Chapter& chapter, CommandType command_type) :
		_chapter(chapter),
		_command_type(command_type)
	{}
public:
	bool isValid() { return false; }
	bool doExecute() { return false; }
};