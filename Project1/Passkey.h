#pragma once

template<typename T>
class Passkey {
public:
	Passkey(const Passkey& that) = delete;
	Passkey& operator=(const Passkey& that) = delete;
private:
	friend T;
	Passkey() = default;

	Passkey(Passkey&& that) = default;
	Passkey& operator=(Passkey&& that) = default;

	~Passkey() = default;
};