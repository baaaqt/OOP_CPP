#pragma once
#include <iostream>

class BoolRank
{
private:
    uint8_t* mPointer;
    uint8_t mMask;

public:
    BoolRank(uint8_t* _byte, const int _bitIndex);

    bool operator=(const bool _value);
    bool operator=(const BoolRank& _other);

    bool operator==(const int _value) const;
    bool operator==(const BoolRank& _other) const;
    bool operator!=(const BoolRank& _other) const;
    bool operator>(const int _value) const;
    bool operator<(const int _value) const;



    friend std::ostream& operator<<(std::ostream& _out, const BoolRank& _object);
    friend std::istream& operator>>(std::istream& _in, BoolRank& _object);
};