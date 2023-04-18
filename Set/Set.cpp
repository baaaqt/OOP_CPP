#include "Set.h"
#include "BoolVector.h"
#include <cstring>

Set::Set() : BoolVector(95, 0)
{
    mPower = 0;
}

Set::Set(const char* _string) : BoolVector(95, 0)
{
    for (int i = 0; i < strlen(_string); i++)
    {
        if (_string[i] >= 32 && _string[i] <= 126)
            set(_string[i] - 32, 1);
    }
    mPower = weight();
}

Set::Set(const Set& _other) : BoolVector(_other)
{
    mPower = _other.mPower;
}

Set::~Set()
{
    ~BoolVector();
}

bool Set::isIn(const char _c) const
{
    if (this->BoolVector::operator[](_c - 32) == 1)
        return true;
    else
        return false;
}

char Set::max() const
{
    if (!mPower)
        return 0;
    for (int i = 94; i >= 0; i--)
    {
        if (this->BoolVector::operator[](i) == 1)
        {
            return i;
        }
    }
    return 0;
}

char Set::min() const
{
    if (!mPower)
        return 0;
    for (int i = 0; i < 95; i++)
    {
        if (this->BoolVector::operator[](i) == 1)
        {
            return i;
        }
    }
    return 0;
}

Set &Set::operator=(const Set& _other)
{
    if (this == &_other)
        return *this;
    mPower = mPower;
    this->BoolVector::operator=(_other);
    return *this;
}

bool Set::operator==(const Set& _other) const
{
    return this->BoolVector::operator==(_other);
}

bool Set::operator!=(const Set& _other) const
{
    return !(this->operator==(_other));
}

Set Set::operator|(const Set& _other) const
{
    Set newObject = (*this);
    newObject |= _other;
    return newObject;
}

Set Set::operator|=(const Set& _other)
{
    if (this == &_other)
        return *this;
    this->BoolVector::operator|=(_other);
    mPower = weight();
    return *this;
}

Set Set::operator&(const Set& _other) const
{
    Set newObject = (*this);
    newObject &= _other;
    return newObject;
}

Set Set::operator&=(const Set& _other)
{
    if (this == &_other)
        return *this;
    this->BoolVector::operator&=(_other);
    mPower = weight();
    return *this;
}

Set Set::operator/(const Set& _other) const
{
    Set newObject = _other;
    newObject /= _other;
    return newObject;
}

Set Set::operator/=(const Set& _other)
{
    if (this == &_other)
    {
        set(0);
        mPower = 0;
        return *this;
    }
    for (int i = 0; i < 95; i++)
    {
        if (this->BoolVector::operator[](i) == _other.BoolVector::operator[](i))
            set(i, false);
    }
    mPower = weight();
    return *this;
}

Set Set::operator+(const char _c) const
{
    Set newObject = (*this);
    newObject += _c;
    return newObject;
}

Set Set::operator+=(const char _c)
{
    if (_c >= 32 && _c <= 126)
    {
        set(_c - 32, 1);
        mPower = weight();
    }
    return *this;
}

Set Set::operator-(const char _c) const
{
    Set newObject = (*this);
    newObject -= _c;
    return newObject;
}

Set Set::operator-=(const char _c)
{
    if (_c >= 32 && _c <= 126)
    {
        set(_c - 32, 0);
        mPower = weight();
    }
    return *this;
}

Set Set::operator~() const
{
    Set newObject = (*this);
    newObject.inverse();
    newObject.mPower = weight();
    return newObject;
}

std::ostream& operator<<(std::ostream& _out, const Set& _object)
{
    _out << '{';
    if (!_object.mPower)
    {
        _out << '}';
        return _out;
    }
    int count = _object.weight();
    int i;
    for (i = 0; i < 95 && count > 1; i++)
    {
        if (_object.BoolVector::operator[](i) == 1)
        {
            _out << (char)(i + 32) << ',';
            count--;
        }
    }
    for (; i < 95; i++)
    {
        if (_object.BoolVector::operator[](i) == 1)
        {
            _out << (char)(i + 32) << '}';
            break;
        }
    }
    return _out;
}

std::istream& operator>>(std::istream& _in, Set& _object)
{
    int n;
    std::cout << "Input count of symbols: ";
    _in >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        _in >> c;
        if (c >= 32 && c <= 126)
        {
            _object += c;
        }
    }
    return _in;
}