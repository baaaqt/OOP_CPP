#include "List.h"
#include "Node.h"

List::List()
{
    mHead = nullptr;
    mTail = nullptr;
    mSize = 0;
}

List::List(const int* _arr, const size_t _size)
{
    for (size_t i = 0; i < _size; i++)
        push_back(_arr[i]);
}

List::List(const size_t _size)
{
    if (_size < 0)
        throw std::invalid_argument("Invalid _size to list object");

    for (size_t i = 0; i < _size; i++)
    {
        push_back(0);
    }
}

List::List(const List& _other)
{
    Node* temp = _other.mHead;
    while (temp)
    {
        push_back(temp->getValue());
        temp = temp->pointerToNext;
    }
}

List::~List()
{
    Node* temp = mHead;
    while (temp)
    {
        mHead = mHead->getNext();
        delete temp;
        temp = mHead;
    }
}

Node* List::find(const int _key)
{
    Node* temp = mHead;
    while (temp->getValue() != _key && temp)
        temp = temp->pointerToNext;
    return temp;
}

bool List::isEmpty()
{
    return mSize == 0;
}

void List::erase_back()
{
    if (mTail)
    {
        Node* temp = mTail;
        mTail = mTail->pointerToPrevius;
        delete temp;
        mSize--;
    }
}

void List::erase_forward()
{
    if (mHead)
    {
        Node* temp = mHead;
        mHead = mHead->pointerToNext;
        delete temp;
        mSize--;
    }
}

void List::erase_by_position(const size_t _pos)
{
    Node* temp = getNode(_pos);
    if (temp)
    {
        delete temp;
        mSize--;
    }
}

void List::erase_by_key(const int _key)
{
    Node* temp = find(_key);
    if (temp)
    {
        delete temp;
        mSize--;
    }
}

void List::push_back(const int _value)
{
    Node* newNode = new Node(_value, nullptr, mTail);
    if (mTail)
        mTail->pointerToNext = newNode;
    mTail = newNode;

    if (!mHead)
        mHead = newNode;

    mSize++;
}

void List::push_forward(const int _value)
{
    Node* newNode = new Node(_value, mHead, nullptr);
    if (mHead)
        mHead->pointerToPrevius = newNode;
    mHead = newNode;

    if (!mTail)
        mTail = newNode;

    mSize++;
}

void List::push_by_position(const int _value, const size_t _pos)
{
    if (_pos == 0) {
        push_forward(_value);
        return;
    }
    if (_pos == mSize - 1) {
        push_back(_value);
        return;
    }

    Node* temp = getNode(_pos);
    Node* newNode = new Node(_value, temp, temp->pointerToPrevius);
    temp->pointerToPrevius->pointerToNext = newNode;
    temp->pointerToPrevius = newNode;
    mSize++;
}

void List::push_by_key(const int _value, const int _key)
{
    Node* temp = find(_key);

    if (temp == mTail) {
        push_back(_value);
        return;
    }
    if (temp == mHead) {
        push_forward(_value);
        return;
    }

    Node* newNode = new Node(_value, temp->pointerToNext, temp);
    temp->pointerToNext->pointerToPrevius = newNode;
    temp->pointerToNext = newNode;
    mSize++;
}

int List::min()
{
    if (!mSize)
        return mTail->mValue;
    Node* temp = mHead;
    int minimum = mHead->mValue;
    while (temp)
    {
        if (minimum > temp->getValue())
            minimum = temp->getValue();
        temp = temp->pointerToNext;
    }

    return minimum;
}

int List::max()
{
    if (!mSize)
        return mTail->mValue;
    Node* temp = mHead;
    int maximum = mHead->mValue;
    while (temp)
    {
        if (maximum < temp->getValue())
            maximum = temp->getValue();
        temp = temp->pointerToNext;
    }

    return maximum;
}

void List::clear()
{
    Node* temp = mHead;
    while (temp)
    {
        mHead = mHead->pointerToNext;
        delete temp;
        temp = mHead;
    }
    mHead = nullptr;
    mTail = nullptr;
    mSize = 0;
}

void List::sort()
{
    qsort(0, mSize - 1);
}

int& List::operator[](const size_t _pos)
{
    if (_pos >= mSize)
    {
        throw std::invalid_argument("Index out of range.");
    }

    Node* temp = mHead;
    for (size_t i = 1; i <= _pos && temp; i++)
        temp = temp->pointerToNext;
    return temp->mValue;
}

int List::operator[](const size_t _pos) const
{
    if (_pos >= mSize)
    {
        throw std::invalid_argument("Index out of range.");
    }

    Node* temp = mHead;
    for (size_t i = 1; i <= _pos && temp; i++)
        temp = temp->pointerToNext;
    return temp->getValue();
}

Node* List::getNode(const size_t _pos)
{
    if (_pos > mSize - 1)
    {
        throw std::invalid_argument("Index out of range.");
    }

    Node* temp = mHead;
    for (size_t i = 1; i <= _pos && temp; i++)
        temp = temp->pointerToNext;

    return temp;
}

List & List::operator=(const List& _other)
{
    if (this == &_other)
        return *this;

    clear();
    Node* temp = _other.mHead;
    while (temp) {
        push_back(temp->getValue());
        temp = temp->getNext();
    }

    return *this;
}

bool List::operator==(const List& _other)
{
    if (this == &_other)
        return true;

    if (this->mSize < _other.mSize)
        return false;

    Node* temp = this->mHead;
    Node* tempOther = _other.mHead;
    while (temp)
    {
        if (temp != tempOther)
            return false;
        temp = temp->pointerToNext;
        tempOther = tempOther->pointerToNext;
    }
    return true;
}

bool List::operator!=(const List& _other)
{
    return !this->operator==(_other);
}

List List::operator+(const List& _other)
{
    List newList(*this);

    Node* temp = _other.mHead;
    while (temp)
    {
        newList.push_back(temp->getValue());
        temp = temp->pointerToNext;
    }

    return newList;
}

std::ostream& operator<<(std::ostream& _out, const List& _obj)
{
    _out << '[';
    Node* temp = _obj.mHead;
    while ((temp != _obj.mTail) && temp)
    {
        _out << *temp << ", ";
        temp = temp->getNext();
    }
    if (_obj.mTail)
        _out << (*_obj.mTail);
    _out << ']';

    return _out;
}

std::istream& operator>>(std::istream& _in, List& _obj)
{
    Node* temp = _obj.mHead;
    while (temp) {
        _in >> (*temp);
        temp = temp->getNext();
    }
    return _in;
}

void List::qsort(const int _begin, const int _end)
{
    int i = _begin;
    int j = _end;
    Node* left = getNode(i);
    Node* right = getNode(j);
    int pivot = getNode((i + j) / 2)->mValue;

    while (i <= j)
    {
        while (left->getValue() < pivot)
        {
            i++;
            left = left->pointerToNext;
        }
        while (right->getValue() > pivot)
        {
            j--;
            right = right->pointerToPrevius;
        }
        if (i <= j)
        {
            int temp = getNode(i)->mValue;
            getNode(i)->mValue = getNode(j)->mValue;
            getNode(i)->mValue = temp;
            i++;
            left = left->pointerToNext;
            j--;
            right = right->pointerToPrevius;
        }
    }
    if (j > _begin)
        qsort(_begin, j);
    if (i < _end)
        qsort(i, _end);
}
