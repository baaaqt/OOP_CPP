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
    mByteSize = (_size - 1) / 8 + (_size % 8 >= 0);
    mPointer = new uint8_t[mByteSize];
    set(0);
}

BoolVector::BoolVector(const int _size, const int _value)
{
    if (_size < 0)
        throw "Parameter \"_size\" must be greater or equal 0.";
    mBitSize = _size;
    mByteSize = (_size - 1) / 8 + (_size % 8 >= 0);
    mPointer = new uint8_t[mByteSize];

    if (_value == 1)
    {
        for (unsigned int i = 0; i < mByteSize; i++)
            mPointer[i] = ~0;
    }
    else
    {
        for (unsigned int i = 0; i < mByteSize; i++)
            mPointer[i] = 0;
    }
}

BoolVector::BoolVector(const char* _vector)
{
    int size = strlen(_vector);
    mBitSize = size;
    mByteSize = (size - 1) / 8 + (size % 8 >= 0);
    mPointer = new uint8_t[mByteSize];

    for (unsigned int i = 0; i < mBitSize; i++)
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
        for (unsigned int i = 0; i < mByteSize; i++)
            mPointer[i] = _other.mPointer[i];
    }
    else
        mPointer = nullptr;
}

BoolVector::~BoolVector()
{
    //std::cout << "Destructor Works " << mByteSize << std::endl;
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
    for (unsigned int i = 0; i < mBitSize; i++)
    {
        if (this->operator[](i) == 1)
        {
            count++;
        }
    }
    return count;
}

void BoolVector::resize(const int _size)
{
    size_t newByteSize = (_size - 1) / 8 + (_size % 8 >= 0);
    if (mPointer) {
        uint8_t* newPointer = new uint8_t[newByteSize];
        for (unsigned int i = 0; i < newByteSize; i++)
            newPointer[i] = 0;
        
        size_t border = (newByteSize > mByteSize) ? newByteSize : mByteSize;
        for (unsigned int i = 0; i < border; i++)
            newPointer[i] = mPointer[i];
        delete[] mPointer;
        mPointer = newPointer;
        mBitSize = _size;
        mByteSize = newByteSize;
    }
    else {
        mBitSize = _size;
        mByteSize = newByteSize;
        mPointer = new uint8_t[newByteSize];
        set(0);
    }
   
}

void BoolVector::inverse()
{
    for (unsigned int i = 0; i < mByteSize; i++)
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
    size_t border = (_beginPos + _count < mBitSize) ? _beginPos + _count : mBitSize;
    for (unsigned int i = _beginPos; i < border; i++)
        (*this)[i] = _value;
}

void BoolVector::set(const bool _value)
{
    if (_value)
        for (unsigned int i = 0; i < mByteSize; i++)
            mPointer[i] = ~0;
    else
        for (unsigned int i = 0; i < mByteSize; i++)
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
    for (unsigned int i = 0; i < mByteSize; i++)
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
    size_t border = (mByteSize < _other.mByteSize) ? mByteSize : _other.mByteSize;
    for (unsigned int i = 0; i < border; i++)
        mPointer[i] &= _other.mPointer[i];
    for (unsigned int i = border; i < mByteSize; i++)
        mPointer[i] = 0;
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
    for (unsigned int i = 0; i < _other.mByteSize; i++)
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
    for (unsigned int i = 0; i < _other.mByteSize; i++)
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
    for (unsigned int i = _step; i < mBitSize; i++)
        (*this)[i - _step] = (*this)[i];

    for (unsigned int i = mBitSize - _step; i < mBitSize; i++)
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
    for (unsigned int i = mBitSize - 1 - _step; i >= 0; i--)
        (*this)[i + _step] = (*this)[i];

    for (unsigned int i = 0; i < mBitSize && i < _step; i++)
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

    for (unsigned int i = 0; i < mBitSize; i++)
        if (mPointer[i] != _other.mPointer[i])
           return false;
	
	return true;
}

bool BoolVector::operator!=(const BoolVector& _other) const
{
    return !((*this) == _other);
}

std::ostream& operator<<(std::ostream& _out, const BoolVector& _object)
{
    for (unsigned int i = 0; i < _object.bitSize(); i++)
        _out << (_object[i] == 1);
    return _out;
}

std::istream& operator>>(std::istream& _in, BoolVector& _object)
{

    for (unsigned int i = 0; i < _object.bitSize(); i++)
    {
        char c;
        _in >> c;
        _object[i] = (c == '0') ? 0 : 1;
    }
    return _in;
}