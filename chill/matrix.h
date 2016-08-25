// Name:	matrix.h
// Date:	03/30/2016
// Version:	1.0.0.0

#ifndef _SYSTEM_MATRIX_H_
#define _SYSTEM_MATRIX_H_
#include "macro.h"
#include "memory.h"
#include <string>
#include <memory>
#include <algorithm>

SYSTEM BEGIN
template <typename T>
class Matrix
{
public:
	Matrix(size_t x, size_t y)
		: _width(x), _height(y), data(Memory::create<T>(x*y), Memory::free<T>) {}
	Matrix(size_t x, size_t y, const T &inc)
		: _width(x), _height(y), data(Memory::create<T>(x*y, inc), Memory::free<T>) {}
	Matrix(size_t x, size_t y, const T *dat)
		: _width(x), _height(y), data(Memory::copyOf(dat, x*y), Memory::free<T>) {}

	// Method
	bool is_out(size_t x, size_t y) const {
		return (x > _width) || (y > _height) || (x < 0) || (y < 0);
	}
	size_t height() const { return _height; }
	size_t width() const { return _width; }

	// Unsafe
	const T& get(size_t x, size_t y) const {
		return data.get()[y*_width + x];
	}
	T& get(size_t x, size_t y) {
		return data.get()[y*_width + x];
	}
	T* operator[](size_t y) {
		return data.get() + y*_width;
	}
	void set(size_t x, size_t y, const T &elt) {
		data.get()[y*_width + x] = elt;
	}

private:
	const size_t _width, _height;
	std::shared_ptr<T> data;
};


template <typename T>
std::string to_string(const Matrix<T> &matrix) {
	using std::to_string;
	const size_t MatrixMaxShowSize = 20;

	std::string str;
	size_t mX = std::min(matrix.width(), MatrixMaxShowSize);
	size_t mY = std::min(matrix.height(), MatrixMaxShowSize);
	for (size_t y = 0; y < mY; y++) {
		for (size_t x = 0; x < mX; x++) {
			str.append(to_string(matrix.get(x, y)));
			str.push_back(' ');
		}
		str.push_back('\n');
	}
	return str;
}
END

#endif
