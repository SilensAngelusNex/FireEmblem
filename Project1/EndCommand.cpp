#include "EndCommand.h"
#include "Chapter.h"
#include "Party.h"

EndCommand::EndCommand(Chapter& chapter, const Party& party) :
	CommandBase(chapter, CommandType::values::END),
	_party(party)
{}
bool EndCommand::isValid() const {
	return _party == _chapter.getTurnParty();
}
bool EndCommand::doExecute() {
	_chapter.newTurn();
	return true;
}

