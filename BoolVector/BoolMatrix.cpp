#include "BoolMatrix.h"

BoolMatrix::BoolMatrix()
{
	rows_ = nullptr;
	nRows_ = 0;
	nColumns_ = 0;
}

BoolMatrix::BoolMatrix(const int _nRows, const int _nColumns)
{
	if (_nRows < 0)
		throw "_nRows must greater or equal 0";
	else if (_nRows == 0) {
		BoolMatrix();
		return;
	}

	if (_nColumns < 0)
		throw "_nColumns must greater or equal 0";

	rows_ = new BoolVector[_nRows];
	for (int i = 0; i < _nRows; i++) {
		rows_[i] = BoolVector(_nColumns);
	}
	nColumns_ = _nColumns;
	nRows_ = _nRows;
}

BoolMatrix::BoolMatrix(const int _nRows, const char** _str)
{
	if (_nRows > 0) {
		nColumns_ = strlen(_str[0]);
		for (int i = 1; i < _nRows; i++) {
			if (nColumns_ < strlen(_str[i]))
				nColumns_ = strlen(_str[i]);
		}
	}
	else if (_nRows < 0) {
		throw "_nRows must be greater or equal 0";
	}
	else {
		BoolMatrix();
		return;
	}

	rows_ = new BoolVector[_nRows];
	for (int i = 0; i < _nRows; i++) {

		// if (i > 0 && new_row.bitSize != rows_[i - 1].bitSize) {
		// 	 throw "Matrix rows must have same size";
		// }


		rows_[i] = BoolVector(_str[i]);
		rows_[i].resize(nColumns_);
	}

	nRows_ = _nRows;
}

BoolMatrix::BoolMatrix(const BoolMatrix& _other)
{
	rows_ = new BoolVector[_other.nRows_];
	nRows_ = _other.nRows_;
	nColumns_ = _other.nColumns_;
	for (int i = 0; i < nRows_; i++) {
		rows_[i] = _other.rows_[i];
	}
}

BoolMatrix::~BoolMatrix()
{
	delete[] rows_;
}

unsigned int BoolMatrix::weight() const
{
	int weight = 0;
	for (int i = 0; i < nRows_; i++) {
		weight += rows_[i].weight();
	}
	return weight;
}

unsigned int BoolMatrix::weight(const int _row) const
{
	if (_row >= nRows_ || _row < 0)
		throw "Index out of range";
	return rows_[_row].weight();
}

BoolVector BoolMatrix::conjunct() const
{
	BoolVector temp;
	if (nRows_ > 0) {
		temp = rows_[0];
	}
	for (int i = 1; i < nRows_; i++) {
		temp &= rows_[i];
	}
	return temp;
}

BoolVector BoolMatrix::disjunct() const
{
	BoolVector temp;
	if (nRows_ > 0) {
		temp = rows_[0];
	}
	for (int i = 1; i < nRows_; i++) {
		temp |= rows_[i];
	}
	return temp;
}

void BoolMatrix::inverse(const int _row, const int _column)
{
	if (_row < 0 || _row >= nRows_)
		throw "Index out of range";
	if (_column < 0 || _column >= nColumns_)
		throw "Index out of range";
	rows_[_row].inverse(_column);
}

void BoolMatrix::inverse(const int _row, const int _column, const int _count)
{
	for (int i = 0; i < _count; i++) {
		inverse(_row, _column + i);
	}
}

void BoolMatrix::set(const int _row, const int _column, const bool _value)
{
	if (_row < 0 || _row >= nRows_)
		throw "Index out of range";
	if (_column < 0 || _column >= nColumns_)
		throw "Index out of range";
	rows_[_row].set(_column, _value);
}

void BoolMatrix::set(const int _row, const int _column, const bool _value, const int _count)
{
	if (_row < 0 || _row >= nRows_)
		throw "Index out of range";
	if (_column < 0 || _column >= nColumns_ || _column + _count >= nColumns_)
		throw "Index out of range";
	rows_[_row].set(_column, _count, _value);
}

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& _other)
{
	if (this == &_other) {
		return *this;
	}
	rows_ = new BoolVector[_other.nRows_];
	nRows_ = _other.nRows_;
	nColumns_ = _other.nColumns_;
	for (int i = 0; i < nRows_; i++) {
		rows_[i] = _other.rows_[i];
	}
}

BoolVector& BoolMatrix::operator[](const int _row)
{
	if (_row >= nRows_ || _row < 0)
		throw "Index out of range";
	return rows_[_row];
}



BoolMatrix BoolMatrix::operator&(const BoolMatrix& _other)
{
	BoolMatrix result(*this);
	result &= _other;
	return result;
}

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& _other)
{

	int border = _other.nRows_ <= nRows_ ? _other.nRows_ : nRows_;
	for (int i = 0; i < border; i++) {
		rows_[i] &= _other.rows_[i];
	}
	return *this;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& _other)
{
	BoolMatrix result(*this);
	result |= _other;
	return result;
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& _other)
{
	int border = _other.nRows_ <= nRows_ ? _other.nRows_ : nRows_;
	for (int i = 0; i < border; i++) {
		rows_[i] |= _other.rows_[i];
	}
	return *this;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& _other)
{
	BoolMatrix result(*this);
	result ^= _other;
	return result;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& _other)
{
	int border = _other.nRows_ <= nRows_ ? _other.nRows_ : nRows_;
	for (int i = 0; i < border; i++) {
		rows_[i] ^= _other.rows_[i];
	}
	return *this;
}

BoolMatrix BoolMatrix::operator~()
{
	BoolMatrix result(*this);
	for (int i = 0; i < result.nRows_; i++) {
		result.rows_[i].operator~();
	}
	return result;
}

std::ostream& operator<<(std::ostream& _out, const BoolMatrix& _object) {
	_out << '\n';
	for (int i = 0; i < _object.nRows_; i++) {
		_out << _object.rows_[i];
		_out << '\n';
	}
	return _out;
}

std::istream& operator>>(std::istream& _in, BoolMatrix& _object) {
	for (int i = 0; i < _object.nRows_; i++) {
		_in >> _object.rows_[i];
	}
	return _in;
}
