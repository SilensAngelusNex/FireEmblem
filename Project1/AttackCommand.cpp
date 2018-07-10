#include "AttackCommand.h"
#include "Chapter.h"
#include "Unit.h"

AttackCommand::AttackCommand(Chapter & chapter, Unit & attacker, Unit & defender):
	CommandBase(chapter, CommandType::values::ATTACK),
	_attacker(attacker),
	_defender(defender)
{}

bool AttackCommand::isValid() const {
	auto attackable_units = getHelper().getAttackableUnits(_attacker);
	auto helper = AttackHelper(_chapter._map);
	bool valid = CommandBase::isValid();
	valid &= *_attacker.getParty() == _chapter.getTurnParty();
	valid &= std::find(attackable_units.begin(), attackable_units.end(), _defender) != attackable_units.end();
	valid &= _attacker.getTurnInfo().getActionsUsed() < TurnInfo::TOTAL_ACTIONS;
	valid &= _attacker.getTurnInfo().getMajorActionsUsed() < TurnInfo::TOTAL_MAJOR_ACTIONS;
	return valid && !_attacker.isTired() && !_attacker.getHealth().isDead() && !_defender.getHealth().isDead();
}

bool AttackCommand::doExecute() {
	_attacker.getCombat().combat(_defender);
	_attacker.getTurnInfo().useMajorAction();
	_chapter._reversable_moves.clear();
	_attacker.getTurnInfo().clearLastMove();
	std::cout << _attacker.getIdentity() << " attacked " << _defender.getIdentity() << std::endl;
	return true;
}


