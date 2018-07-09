#include "CommandBase.h"
#include "Chapter.h"
#include "CommandType.h"

int CommandBase::_incrementor = 0;

CommandBase::CommandBase(Chapter& chapter, CommandType command_type) :
_chapter(chapter),
_command_type(command_type),
_command_id(++_incrementor)
{}

bool CommandBase::isValid() const { 
	return _command_id == _incrementor; 
}
bool CommandBase::doExecute() {
	return false; 
}

bool CommandBase::operator==(const CommandBase& rhs) const {
	return _command_id == rhs._command_id;
}

bool CommandBase::operator!=(const CommandBase & rhs) const {
	return _command_id != rhs._command_id;
}
