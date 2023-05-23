#pragma once
#include <iostream>
#include "BoolRank.h"


class BoolMatrix;


class BoolVector
{
private:
    uint8_t* mPointer;
    size_t   mBitSize;
    size_t   mByteSize;

    void resize(const int _size);

	friend class BoolMatrix;
public:
    BoolVector();
    BoolVector(const int _size);
    BoolVector(const int _size, const int _value);
    BoolVector(const char* _vector);
    BoolVector(const BoolVector& _other);
    ~BoolVector();

    int  bitSize() const;
    int  byteSize() const;
    int  weight() const;

    void inverse();
    void inverse(const int _pos);
    void set(const int _pos, const bool _value);
    void set(const int _beginPos, const int _count, const bool _value);
    void set(const bool _value);

    BoolVector operator=(const BoolVector& _other);

    BoolRank       operator[](const int _pos);
    const BoolRank operator[](const int _pos) const;

    BoolVector operator&(const BoolVector& _other) const;
    BoolVector operator&=(const BoolVector& _other);
    BoolVector operator|(const BoolVector& _other) const;
    BoolVector operator|=(const BoolVector& _other);
    BoolVector operator^(const BoolVector& _other) const;
    BoolVector operator^=(const BoolVector& _other);
    BoolVector operator<<(const int _step) const;
    BoolVector operator<<=(const int _step);
    BoolVector operator>>(const int _step) const;
    BoolVector operator>>=(const int _step);
    BoolVector operator~() const;

    bool operator==(const BoolVector& _other) const;
    bool operator!=(const BoolVector& _other) const;

    friend std::ostream& operator<<(std::ostream& _out, const BoolVector& _object);
    friend std::istream& operator>>(std::istream& _in, BoolVector& _object);
};