#pragma once
#include <optional>
template<typename T>
class Math
{
public:
	T add(T x, T y) const {
		return x + y;
	}
	T sub(T x, T y) const {
		return x - y;
	}
	T mul(T x, T y) const {
		return x * y;
	}
	std::optional<T> div(T x, T y) const {
		if (y == 0) {
			return std::nullopt;
		}
		return x / y;
	}
};

