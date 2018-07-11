#pragma once

#include <set>


// TODO(Weston): revamp Observer/Observable to allow one class to observe multiple things
template <class T>
class Observable {
protected:
	std::set<T*> _observers;
public:
	void attach(T& observer) {
		_observers.insert(&observer);
	}

	void detach(T& observer) {
		_observers.erase(&observer);
	}
};