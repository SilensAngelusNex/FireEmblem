#pragma once

#include "Dice.h"
#include <random>

template<int sides>
class FairDice : public Dice<sides> {
private:
	std::mt19937 _generator;
	std::uniform_int_distribution<> _distribution;
public:
	FairDice() {
		std::random_device rand_device;

		_generator = std::mt19937(rand_device());
		_distribution = std::uniform_int_distribution<>(0, sides - 1);
	}

	explicit FairDice(int seed) {
		_generator = std::mt19937(seed);
		_distribution = std::uniform_int_distribution<>(0, sides - 1);
	}

	FairDice(const FairDice& a) = default;
	FairDice(FairDice&& a) = default;
	FairDice& operator=(const FairDice& rhs) = default;
	FairDice& operator=(FairDice&& rhs) = default;
	~FairDice() override = default;

	int roll() override {
		return _distribution(_generator);
	}
};
