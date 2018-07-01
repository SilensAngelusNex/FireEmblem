#pragma once

#include <set>
#include <string>

class Actions {
private:
	using ActionId = std::string;

	int _used_move;
	bool _major_remaining;
	bool _minor_remaining;
	std::set<ActionId> _independent_used;

public:
	Actions();

	bool hasMajor() const;
	bool hasMinor() const;
	int moveUsed() const;
	bool hasIndependent(ActionId action) const;
	const std::set<ActionId>& usedIndependents() const;

	void useMajor();
	void useMinor();
	void useMove(int used);
	void useIndependent(ActionId used);

	void refresh();
};