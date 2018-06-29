#pragma once

template<typename T1, typename T2>
class logic_pair :
	public std::pair<T1, T2> {
public:
	using std::pair<T1, T2>::pair;
	using std::pair<T1, T2>::operator=;
	using std::pair<T1, T2>::swap;
	using std::pair<T1, T2>::first;
	using std::pair<T1, T2>::second;

	bool operator==(const logic_pair& other) const {
		return first == other.first && second == other.second;
	}

	bool operator!=(const logic_pair& other) const {
		return first != other.first || second != other.second;
	}

	bool operator<(const logic_pair& other) const {
		bool a = first < other.first;
		bool b = second < other.second;
		bool c = first == other.first;
		return a | (c && b);
	}
	bool operator>(const logic_pair& other) const {
		bool a = first > other.first;
		bool b = second > other.second;
		bool c = first == other.first;
		return a | (c && b);
	}

	bool operator>=(const logic_pair& other) const {
		bool a = first < other.first;
		bool b = second < other.second;
		bool c = first == other.first;
		return !(a | (c && b));
	}
	bool operator<=(const logic_pair& other) const {
		bool a = first > other.first;
		bool b = second > other.second;
		bool c = first == other.first;
		return !(a | (c && b));
	}

};