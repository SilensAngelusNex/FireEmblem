#pragma once
#pragma once

#include <optional>
#include "Component.h"
#include "Mobility.h"

class Unit;

class TurnInfo : Component<Unit> {
private:
	int _major_actions_used;
	int _actions_used;
	int _remaining_move;
	bool _tired;
public:
	explicit TurnInfo(Unit& owner);
	constexpr static int TOTAL_ACTIONS = 2;
	constexpr static int TOTAL_MAJOR_ACTIONS = 1;

	int getRemainingMove() const;
	int getActionsUsed() const;
	int getMajorActionsUsed() const;

	void useMovement(int distance);
	void useMinorAction();
	void useMajorAction();

	bool isTired() const { return _tired; }
	void tire() { _tired = true; };
	void refresh();
};




