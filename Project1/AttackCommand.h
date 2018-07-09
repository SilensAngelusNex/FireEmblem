#pragma once
#include "CommandBase.h"
#include "AttackHelper.h"
class Unit;

class AttackCommand : public CommandBase, AttackContainer {
private:
	Unit& _attacker;
	Unit& _defender;
public:
	AttackCommand(Chapter& chapter, Unit& attacker, Unit& defender);
	bool isValid() const;
	bool doExecute();
};



