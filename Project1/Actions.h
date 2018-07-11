#pragma once

#include <set>
#include <string>

class Actions {
public:
	using ActionId = std::string;
private:
	int _used_move = 0;
	bool _major_remaining = true;
	bool _minor_remaining = true;
	std::set<ActionId> _independent_used;

public:
	Actions();

	bool hasMajor() const;
	bool hasMinor() const;
	int moveUsed() const;
	bool hasIndependent(const ActionId& action) const;
	const std::set<ActionId>& usedIndependents() const;

	void useMajor();
	void useMinor();
	void useMove(int used);
	void useIndependent(ActionId used);

	void refresh();
};