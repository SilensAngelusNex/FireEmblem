#include "PathBase.h"

void PathBase::push_back(GridCell & tail) {
	_path.emplace_back(0, tail);
}

GridCell & PathBase::front() {
	Expects(_path.size() > 0); {
		return _path.front().second;
	}
}

const GridCell & PathBase::front() const{
	Expects(_path.size() > 0); {
		return _path.front().second;
	}
}
GridCell& PathBase::back() {
	Expects(_path.size() > 0); {
		return _path.back().second;
	}
}

const GridCell& PathBase::back() const {
	Expects(_path.size() > 0); {
		return _path.back().second;
	}
}