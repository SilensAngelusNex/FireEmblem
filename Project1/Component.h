#pragma once

class Unit;

template <class T>
class Component {
	friend T;
public:
	Component() = delete;
protected:
	T & _owner;

	explicit Component(T& owner) :
		_owner(owner)
	{}

	void init() {}
};