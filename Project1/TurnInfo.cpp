#include "TurnInfo.h"
#include "Unit.h"


void TurnInfo::refresh() {
	_tired = false;
	_major_actions_used = 0;
	_actions_used = 0;
	_remaining_move = _owner.getMobility().getMove();
	_tired = false;
	_last_move.reset();
	_last_move_cost = 0;

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

std::optional<MoveCommand>& TurnInfo::getLastMove() {
	return _last_move;
}

void TurnInfo::useMovement(int distance) {
	Expects(distance >= 0 && distance <= _remaining_move);
	_last_move_cost = distance;
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

void TurnInfo::setLastMove(MoveCommand& last_move) {
	_last_move.emplace(last_move);
}

void TurnInfo::clearLastMove() {
	_last_move_cost = 0;
	_last_move.reset();
}

void TurnInfo::undoLastMove() {
	_remaining_move += _last_move_cost;
	_last_move_cost = 0;
	_last_move.reset();
}
