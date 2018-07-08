#include "TurnInfo.h"
#include "Unit.h"


void TurnInfo::refresh() {
	_tired = false;
	_major_actions_used = 0;
	_actions_used = 0;
	_remaining_move = _owner.getMobility().getMove();
	_tired = false;

}
TurnInfo::TurnInfo(Unit & owner) :
	Component(owner)
{
	refresh();
}

int TurnInfo::getRemainingMove() const {
	return _remaining_move;
}
int TurnInfo::getActionsUsed() const {
	return _actions_used;
}
int TurnInfo::getMajorActionsUsed() const {
	return _major_actions_used;
}

void TurnInfo::useMovement(int distance) {
	Expects(distance >= 0 && distance <= _remaining_move);
	_remaining_move -= distance;
}

void TurnInfo::useMinorAction() {
	Expects( _actions_used < TOTAL_ACTIONS);
	_actions_used++;
}
void TurnInfo::useMajorAction() {
	Expects(_actions_used < TOTAL_ACTIONS && _major_actions_used < TOTAL_MAJOR_ACTIONS);
	_actions_used++;
	_major_actions_used++;
}