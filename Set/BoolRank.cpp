#include "BoolRank.h"

BoolRank::BoolRank(uint8_t* _byte, const int _bitPos)
{
    mPointer = _byte;
    mMask = 1 << (8 - 1 - _bitPos);
}

bool BoolRank::operator=(const bool _value)
{
    if (_value)
    {
        *mPointer |= mMask;
    }
    else
    {
        *mPointer &= ~mMask;
    }
    return _value;
}

bool BoolRank::operator=(const BoolRank& _other)
{
    (*this) = (_other == 1);
    return false;
}

bool BoolRank::operator==(const int _value) const
{
    if ((*mPointer & mMask) && _value == 1)
        return true;
    else if (!(*mPointer & mMask) && _value == 0)
        return true;
    return false;
}

bool BoolRank::operator==(const BoolRank& _other) const
{
    return (*mPointer & mMask) == (*_other.mPointer & _other.mMask);
}

bool BoolRank::operator!=(const BoolRank& _other) const
{
    return !((*this) == _other);
}

bool BoolRank::operator>(const int _value) const
{
    if ((*mPointer && mMask) == 1 && _value == 0)
        return true;
    return false;
}

bool BoolRank::operator<(const int _value) const
{
    if ((*mPointer & mMask) == 0 && _value == 1)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& _out, const BoolRank& _object)
{
    _out << (_object == 1);
    return _out;
}

std::istream& operator>>(std::istream& _in, BoolRank& _object)
{
    char c;
    _in >> c;
    _object = (c == '0') ? 0 : 1;
    return _in;
}