#pragma once
#include <iostream>

class List;

class Node
{
private:
    Node* pointerToNext;
    Node* pointerToPrevius;
    int mValue;
    
    friend class List;
public:
    Node();
    Node(const int _value);
    Node(const int _value, Node* _pointerToNextObject, Node* _pointerToPreviusObject);
    Node(const Node& _other);
    ~Node();

    Node* getNext() const;
    Node* getPrevius() const;
    int getValue() const;

    void setValue(const int _value);
    void setNext(Node* _pointerToNode);
    void setPrevius(Node* _pointerToNode);

    void operator=(const int _value);
    void operator=(const Node* _other);

    bool operator==(const Node* _other) const;
    bool operator!=(const Node* _other) const;
    friend std::ostream& operator<<(std::ostream& _out, const Node& _obj);
    friend std::istream& operator>>(std::istream& _in, Node& _obj);
};