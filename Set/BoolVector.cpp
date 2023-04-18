#include "BoolVector.h"
#include <iostream>
#include <cstring>

BoolVector::BoolVector()
{
    mPointer = nullptr;
    mBitSize = 0;
    mByteSize = 0;
}

BoolVector::BoolVector(const int _size)
{
    if (_size < 0)
        throw "Parameter \"_size\" must be greater or equal 0.";
    mBitSize = _size;
    mByteSize = (_size - 1) / 8 + (_size % 8 > 0);
    mPointer = new uint8_t[mByteSize];
}

BoolVector::BoolVector(const int _size, const int _value)
{
    if (_size < 0)
        throw "Parameter \"_size\" must be greater or equal 0.";
    mBitSize = _size;
    mByteSize = (_size - 1) / 8 + (_size % 8 > 0);
    mPointer = new uint8_t[mByteSize];

    if (_value == 1)
    {
        for (int i = 0; i < mByteSize; i++)
            mPointer[i] = ~0;
    }
    else
    {
        for (int i = 0; i < mByteSize; i++)
            mPointer[i] = 0;
    }
}

BoolVector::BoolVector(const char* _vector)
{
    int size = strlen(_vector);
    mBitSize = size;
    mByteSize = size / 8 + (size % 8 > 0);
    mPointer = new uint8_t[mByteSize];

    for (int i = 0; i < mBitSize; i++)
    {
        (*this)[i] = (_vector[i] == '0') ? false : true;
    }
}

BoolVector::BoolVector(const BoolVector& _other)
{
    mBitSize = _other.mBitSize;
    mByteSize = _other.mByteSize;
    if (_other.mPointer)
    {
        mPointer = new uint8_t[mByteSize];
        for (int i = 0; i < mByteSize; i++)
            mPointer[i] = _other.mPointer[i];
    }
    else
        mPointer = nullptr;
}

BoolVector::~BoolVector()
{
    if (mPointer)
        delete[] mPointer;
}

int BoolVector::bitSize() const
{
    return mBitSize;
}

int BoolVector::byteSize() const
{
    return mByteSize;
}

int BoolVector::weight() const
{
    int count = 0;
    for (int i = 0; i < mBitSize; i++)
    {
        if (operator[](i) == 1)
        {
            count++;
        }
    }
    return count;
}

void BoolVector::resize(const int _size)
{
    int newByteSize = _size / 8 + (_size % 8 > 0);
    if (mPointer)
    {
        uint8_t* newPointer = new uint8_t[newByteSize];

        int border = (newByteSize > mByteSize) ? newByteSize : mByteSize;
        for (int i = 0; i < border; i++)
            newPointer[i] = mPointer[i];
        delete[] mPointer;
        mPointer = newPointer;

        mBitSize = _size;
        mByteSize = newByteSize;
    }
    else
    {
        mBitSize = _size;
        mByteSize = newByteSize;
        mPointer = new uint8_t[newByteSize];
    }
}

void BoolVector::inverse()
{
    for (int i = 0; i < mByteSize; i++)
        mPointer[i] = ~mPointer[i];
}

void BoolVector::inverse(const int _pos)
{
    if ((*this)[_pos] == 1)
        (*this)[_pos] = 0;
    else
        (*this)[_pos] = 1;
}

void BoolVector::set(const int _pos, const bool _value)
{
    (*this)[_pos] = _value;
}

void BoolVector::set(const int _beginPos, const int _count, const bool _value)
{
    for (int i = _beginPos; i < _beginPos + _count; i++)
        (*this)[i] = _value;
}

void BoolVector::set(const bool _value)
{
    if (_value)
        for (int i = 0; i < mByteSize; i++)
            mPointer[i] = ~0;
    else
        for (int i = 0; i < mByteSize; i++)
            mPointer[i] = 0;
}

BoolVector BoolVector::operator=(const BoolVector& _other)
{
    if (this == &_other)
        return *this;
    if (mPointer)
        delete[] mPointer;
    mBitSize = _other.mBitSize;
    mByteSize = _other.mByteSize;
    mPointer = new uint8_t[mByteSize];
    for (int i = 0; i < mByteSize; i++)
        mPointer[i] = _other.mPointer[i];
    return *this;
}

BoolVector BoolVector::operator&(const BoolVector& _other) const
{
    BoolVector newObject = (*this);
    newObject &= _other;
    return newObject;
}

BoolVector BoolVector::operator&=(const BoolVector& _other)
{
    if (mByteSize > _other.mByteSize)
        resize(_other.mBitSize);

    for (int i = 0; i < mByteSize; i++)
        mPointer[i] &= _other.mPointer[i];
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector& _other) const
{
    BoolVector newObject = (*this);
    newObject |= _other;
    return newObject;
}

BoolVector BoolVector::operator|=(const BoolVector& _other)
{
    if (mByteSize < _other.mByteSize)
        resize(_other.mBitSize);
    for (int i = 0; i < mByteSize; i++)
        mPointer[i] |= _other.mPointer[i];
    return *this;
}

BoolVector BoolVector::operator^(const BoolVector& _other) const
{
    BoolVector newObject = (*this);
    newObject ^= _other;
    return newObject;
}

BoolVector BoolVector::operator^=(const BoolVector& _other)
{
    if (mByteSize < _other.mByteSize)
        resize(_other.mBitSize);
    for (int i = 0; i < mByteSize; i++)
        mPointer[i] ^= _other.mPointer[i];

    return *this;
}

BoolVector BoolVector::operator<<(const int _step) const
{
    BoolVector newObject = (*this);
    newObject <<= _step;
    return newObject;
}

BoolVector BoolVector::operator<<=(const int _step)
{
    for (int i = _step; i < mBitSize; i++)
        (*this)[i - _step] = (*this)[i];

    for (int i = mBitSize - _step; i < mBitSize; i++)
        (*this)[i] = 0;
    return *this;
}

BoolVector BoolVector::operator>>(const int _step) const
{
    BoolVector newObject = (*this);
    newObject >>= _step;
    return newObject;
}

BoolVector BoolVector::operator>>=(const int _step)
{
    for (int i = mBitSize - 1 - _step; i >= 0; i--)
        (*this)[i + _step] = (*this)[i];

    for (int i = 0; i < mBitSize && i < _step; i++)
        (*this)[i] = 0;

    return *this;
}

BoolVector BoolVector::operator~() const
{
    BoolVector newObject = (*this);
    newObject.inverse();
    return newObject;
}

const BoolRank BoolVector::operator[](const int _pos) const
{
    if (_pos < 0 || _pos > mBitSize - 1)
        throw "Invalid _pos: index out of range.";
    BoolRank elem(&mPointer[_pos / 8], _pos % 8);
    return elem;
}

BoolRank BoolVector::operator[](const int _pos)
{
    if (_pos < 0 || _pos > mBitSize - 1)
        throw "Invalid _pos: index out of range.";
    BoolRank elem(&mPointer[_pos / 8], _pos % 8);
    return elem;
}

bool BoolVector::operator==(const BoolVector& _other) const
{
    if (this == &_other)
        return true;

    if (weight() != _other.weight())
        return false;

    int border = (mBitSize < _other.mBitSize) ? mBitSize : _other.mBitSize;
    for (int i = 0; i < border; i++)
        if ((*this)[i] != _other[i])
            return false;
}

bool BoolVector::operator!=(const BoolVector& _other) const
{
    return !((*this) == _other);
}

std::ostream& operator<<(std::ostream& _out, const BoolVector& _object)
{
    for (int i = 0; i < _object.bitSize(); i++)
        _out << (_object[i] == 1);
    return _out;
}

std::istream& operator>>(std::istream& _in, BoolVector& _object)
{

    for (int i = 0; i < _object.bitSize(); i++)
    {
        char c;
        _in >> c;
        _object[i] = (c == '0') ? 0 : 1;
    }
    return _in;
}