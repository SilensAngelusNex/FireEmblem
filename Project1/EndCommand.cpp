#include "EndCommand.h"
#include "Chapter.h"
#include "Party.h"

EndCommand::EndCommand(Chapter& chapter) :
	CommandBase(chapter, CommandType::values::END)
{}
bool EndCommand::isValid() const {
	return CommandBase::isValid();
}
bool EndCommand::doExecute() {
	_chapter.newTurn();
	return true;
}

