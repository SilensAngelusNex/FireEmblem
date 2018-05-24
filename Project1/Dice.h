#pragma once

template <int sides>
class Dice {
public:
	Dice() = default;
	Dice(const Dice& a) = default;
	Dice(Dice&& a) = default;
	Dice& operator=(const Dice& rhs) = default;
	Dice& operator=(Dice&& rhs) = default;
	virtual ~Dice() = default;

	virtual int roll() = 0;

	int rollX(int count) {
		int result = 0;
		while (count > 0) {
			result += roll();
			count--;
		}
		return result;
	}
};