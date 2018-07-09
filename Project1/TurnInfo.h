#pragma once
#pragma once

#include <optional>
#include "Component.h"
#include "Mobility.h"
#include "MoveCommand.h"

class Unit;

class TurnInfo : Component<Unit> {
private:
	int _major_actions_used;
	int _actions_used;
	int _remaining_move;
	bool _tired;
	std::optional<MoveCommand> _last_move;
	int _last_move_cost;
public:
	explicit TurnInfo(Unit& owner);
	constexpr static int TOTAL_ACTIONS = 2;
	constexpr static int TOTAL_MAJOR_ACTIONS = 1;

	int getRemainingMove() const;
	int getActionsUsed() const;
	int getMajorActionsUsed() const;
	std::optional<MoveCommand>& getLastMove();


	void useMovement(int distance);
	void useMinorAction();
	void useMajorAction();
	void setLastMove(MoveCommand& last_move);
	void clearLastMove();
	void undoLastMove();

	bool isTired() const { return _tired; }
	void tire() { _tired = true; };
	void refresh();
};




