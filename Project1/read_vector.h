#pragma once

template<typename VecT>
class read_vector {
private:
	VecT& _row;
public:

	read_vector(VecT& row) : _row(row) {}

	auto& front() {
		return _row.front();
	}
	const auto& front() const {
		return _row.front();
	}
	bool empty() const {
		return _row.empty();
	}

	auto& operator[](size_t index) {
		return _row[index];
	}
	const auto& operator[](size_t index) const {
		return _row[index];
	}
	auto& at(size_t index) {
		return _row.at(index);
	}
	const auto& at(size_t index) const {
		return _row.at(index);
	}
	size_t size() const{
		return _row.size();
	}

	auto begin() { return _row.begin(); }
	auto end() { return _row.end(); };
	auto cbegin() { return _row.cbegin(); }
	auto cend() { return _row.cend(); }

};