#pragma once
#include "BoolVector.h"
#include "BoolRank.h"
#include <string.h>

class BoolMatrix {
private:
	BoolVector* rows_;
	size_t nRows_;
	size_t nColumns_;

public:
	BoolMatrix();
	BoolMatrix(const int _nRows, const int _nColumns);
	BoolMatrix(const int _nRows, const char** _str);
	BoolMatrix(const BoolMatrix& _other);
	~BoolMatrix();

	size_t sizeRows() const { return nRows_; }
	size_t sizeColumns() const { return nColumns_; }

	unsigned int weight() const;
	unsigned int weight(const int _row) const;
	BoolVector conjunct() const;
	BoolVector disjunct() const;
	void inverse(const int _row, const int _column);
	void inverse(const int _row, const int _column, const int _count);
	void set(const int _row, const int _column, const bool _value);
	void set(const int _row, const int _column, const bool _value, const int _count = 1);

	BoolMatrix& operator=(const BoolMatrix& _other);
	BoolVector& operator[](const int _row);
	
	BoolMatrix operator&(const BoolMatrix& _other);
	BoolMatrix& operator&=(const BoolMatrix& _other);
	BoolMatrix operator|(const BoolMatrix& _other);
	BoolMatrix& operator|=(const BoolMatrix& _other);
	BoolMatrix operator^(const BoolMatrix& _other);
	BoolMatrix& operator^=(const BoolMatrix& _other);
	BoolMatrix operator~();
	
	friend std::ostream& operator<<(std::ostream& _out, const BoolMatrix& _object);
	friend std::istream& operator>>(std::istream& _in, BoolMatrix& _obejct);	
};
