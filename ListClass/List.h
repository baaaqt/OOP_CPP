#pragma once
#include <iostream>

class Node;

class List
{
private:
    size_t mSize;
    Node* mHead;
    Node* mTail;

    void qsort(const int _left, const int _right);
    
public:
    List();
    List(const size_t _size);
    List(const int* _arr, const size_t _arrSize);
    List(const List& _other);
    ~List();

    Node * find(const int _key);

    bool isEmpty();

    void erase_back();
    void erase_forward();
    void erase_by_position(const size_t _pos);
    void erase_by_key(const int _key);

    void push_back(const int _value);
    void push_forward(const int _value);
    void push_by_position(const int _value, const size_t _pos);
    void push_by_key(const int _value, const int _key);

    int min();
    int max();

    void clear();
    void sort();

    int& operator[](const size_t _pos);
    int operator[](const size_t _pos) const;

    Node* getNode(const size_t _pos);
    List &operator=(const List& _other);

    bool operator==(const List& _other);
    bool operator!=(const List& _other);

    List operator+(const List& _other);

    friend std::ostream& operator<<(std::ostream& _out, const List& _obj);
    friend std::istream& operator>>(std::istream& _in, List& _obj);
};