#pragma once

#include <deque>
#include <vector>
#include <memory>
#include <gsl/gsl_assert>
#ifndef _DEBUG
#include <iostream>
#endif // !_DEBUG

#include "Dice.h"
#include "FairDice.h"


template<int sides>
class ListDice : public Dice<sides> {
private:
	std::deque<int> _rolls;
	std::unique_ptr<Dice<sides>> _backup;
public:
	explicit ListDice(std::vector<int> rolls) :
		ListDice(rolls, std::make_unique<FairDice<sides>>())
	{}
	ListDice(std::vector<int> rolls, std::unique_ptr<Dice<sides>> backup) :
		_rolls(rolls.begin(), rolls.end()),
		_backup(backup)
	{}

	ListDice(const ListDice& a) = default;
	ListDice(ListDice&& a) = default;
	ListDice& operator=(const ListDice& rhs) = default;
	ListDice& operator=(ListDice&& rhs) = default;
	~ListDice() override = default;

	int roll() override {
		if (!_rolls.empty()) {
			int result = _rolls.front();
			_rolls.pop_front();
#ifdef _DEBUG
			if (result >= sides) {
				std::cerr <<
					std::endl <<
					"Roll of " << result <<
					" not possible for " << sides <<
					" sided die." << std::endl;
			}
			return result % sides;
#endif // _DEBUG
#ifndef _DEBUG
			return result;
#endif // _DEBUG
		}
		
			return _backup->roll();
		


	}
};