#pragma once
#include <iostream>
#include "BoolVector.h"

class Set : public BoolVector
{
private:
    uint8_t mPower;

public:
    Set();
    Set(const char* _string);
    Set(const Set& _other);
    ~Set();

    bool isIn(const char _c) const;

    char max() const;
    char min() const;

    Set& operator= (const Set& _other);

    bool operator==(const Set& _other) const;
    bool operator!=(const Set& _other) const;

    Set operator| (const Set& _other) const;
    Set operator|=(const Set& _other);
    Set operator& (const Set& _other) const;
    Set operator&=(const Set& _other);
    Set operator/ (const Set& _other) const;
    Set operator/=(const Set& _other);

    Set  operator+ (const char _c) const;
    Set operator+=(const char _c);
    Set  operator- (const char _c) const;
    Set operator-=(const char _c);

    Set  operator~() const;

    friend std::ostream& operator<<(std::ostream& _out, const Set& _object);
    friend std::istream& operator>>(std::istream& _in, Set& _object);
};