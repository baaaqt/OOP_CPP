#pragma once
#include <iostream>
#include <algorithm>

template<typename Type>
class DynamicArray
{
private:
	size_t m_len;
	Type* m_arr;

	bool is_valid_index(const unsigned int _pos);

public:
	DynamicArray();
	DynamicArray(const unsigned int _size); // constructor to initialize array with size
	DynamicArray(const unsigned int _size, const Type* _arr); // constructor from usual array
	DynamicArray(const DynamicArray<Type>& _arr); // copy constructor
	~DynamicArray();

	const unsigned int size() const; // returns size of array
	Type max_value() const;
	Type min_value() const;

	int find(const Type _value); // returns index of first such value in array
	void sort(); // sorts array by shell algorithm
	void random_array(const Type _left_border, const Type _right_border);
	void increasing_random_array(const Type _left_border, const Type _right_border);
	void decreasing_random_array(const Type _left_border, const Type _right_border);

	void push_back(const Type _value); // inserts value to end of array
	void insert(const unsigned int _pos, const Type _value); // inserts _value by index = _pos
	void erase(const unsigned int _pos); // removes elements by index
	void remove(const Type _value); // removes first such value in array
	void shift_right(const unsigned int _step);
	void shift_left(const unsigned int _step);
	void cycle_shift_right(const unsigned _step);
	void cycle_shift_left(const unsigned _step);
	void reverse(const unsigned int _start = 0, const unsigned int _end = 0); // changes elements sequence

	DynamicArray<Type> operator-=(const unsigned int _pos); // like erase()
	DynamicArray<Type> operator-(const Type _value); // like remove()
	DynamicArray<Type> operator+=(const Type _value); // like push_back()
	DynamicArray<Type> operator+(const Type _value); // like push_back() but returns new object
	DynamicArray<Type>& operator+=(const DynamicArray<Type>& _other); // merges object with other, but other doesn't change
	DynamicArray operator+(const DynamicArray<Type>& _other); // returns new object merged from two others, but others don't change

	Type& operator[](const unsigned int _pos);
	DynamicArray& operator=(const DynamicArray<Type>& _other);
	bool operator==(const DynamicArray<Type>& _other);
	bool operator!=(const DynamicArray<Type>& _other);

	template <typename T> friend std::ostream& operator<<(std::ostream& _out, const DynamicArray<T>& _obj); // output stream
	template <typename T> friend std::istream& operator>>(std::istream& _in, DynamicArray<T>& _obj); // input stream, needs arr with not null size
};


template<typename Type>
inline DynamicArray<Type>::DynamicArray()
{
	m_len = 0;
	m_arr = nullptr;
}

template<typename Type>
inline DynamicArray<Type>::DynamicArray(const unsigned int _size)
{
	m_len = _size;
	m_arr = new Type[_size];
}


template<typename Type>
inline DynamicArray<Type>::DynamicArray(const unsigned int _size, const Type* _arr)
{
	m_len = _size;
	m_arr = new Type[_size];
	for (int i = 0; i < _size; i++)
	{
		m_arr[i] = _arr[i];
	}
}


template<typename Type>
inline DynamicArray<Type>::DynamicArray(const DynamicArray<Type>& _arr)
{
	m_len = _arr.m_len;
	m_arr = new Type[m_len];
	for (unsigned int i = 0; i < m_len; i++)
	{
		m_arr[i] = _arr.m_arr[i];
	}
}

template<typename Type>
inline DynamicArray<Type>::~DynamicArray()
{
	m_len = 0;
	delete[] m_arr;
}

template<typename Type>
inline const unsigned int DynamicArray<Type>::size() const
{
	return m_len;
}


template<typename Type>
inline Type DynamicArray<Type>::max_value() const
{
	Type max = m_arr[0];
	for (unsigned int i = 1; i < m_len; i++)
	{
		if (max < m_arr[i])
		{
			max = m_arr[i];
		}
	}
	return max;
}


template<typename Type>
inline Type DynamicArray<Type>::min_value() const
{
	Type min = m_arr[0];
	for (unsigned int i = 1; i < m_len; i++)
	{
		if (min > m_arr[i])
		{
			min = m_arr[i];
		}
	}
	return min;
}


template<typename Type>
inline int DynamicArray<Type>::find(const Type _value)
{
	for (unsigned int i = 0; i < m_len; i++)
	{
		if (m_arr[i] == _value)
		{
			return i;
		}
	}
	return -1;
}


template<typename Type>
inline void DynamicArray<Type>::sort()
{
	for (unsigned int step = m_len / 2; step > 0; step /= 2)
	{
		for (unsigned int i = step; i < m_len; i++)
		{
			for (unsigned int j = i - step; j >= 0 && m_arr[j] > m_arr[j + step]; j -= step)
			{
				Type tmp = m_arr[j];
				m_arr[j] = m_arr[j + step];
				m_arr[j + step] = tmp;
			}
		}
	}
}


template<typename Type>
inline void DynamicArray<Type>::push_back(const Type _value)
{
	Type* new_arr = new Type[m_len + 1];
	for (unsigned int i = 0; i < m_len; i++)
	{
		new_arr[i] = m_arr[i];
	}
	new_arr[m_len] = _value;
	m_len += 1;
	delete[] m_arr;
	m_arr = new_arr;
}


template<typename Type>
inline void DynamicArray<Type>::random_array(const Type _left_border, const Type _right_border)
{
	for (unsigned int i = 0; i < m_len; i++)
	{
		m_arr[i] = rand() % (_right_border - _left_border + 1) + _left_border;
	}
}


template<typename Type>
inline void DynamicArray<Type>::increasing_random_array(const Type _left_border, const Type _right_border)
{
	Type left_border_copy = _left_border;
	for (unsigned int i = 0; i < m_len; i++)
	{
		m_arr[i] = rand() % (_right_border - left_border_copy + 1) + left_border_copy;
		left_border_copy = m_arr[i];
	}
}


template<typename Type>
inline void DynamicArray<Type>::decreasing_random_array(const Type _left_border, const Type _right_border)
{
	Type right_border_copy = _right_border;
	for (unsigned int i = 0; i < m_len; i++)
	{
		m_arr[i] = rand() % (right_border_copy - _left_border + 1) + _left_border;
		right_border_copy = m_arr[i];
	}
}


template<typename Type>
inline void DynamicArray<Type>::insert(const unsigned int _pos, const Type _value)
{
	if (!is_valid_index(_pos))
	{
		std::cerr << "Index out of range!!!\n";
		return;
	}

	Type* new_arr = new Type[m_len + 1];
	unsigned int index = 0;
	while (index < _pos)
	{
		new_arr[index] = m_arr[index];
		index++;
	}
	new_arr[index] = _value;
	index++;
	while (index < m_len + 1)
	{
		new_arr[index] = m_arr[index - 1];
		index++;
	}

	delete[] m_arr;
	m_len += 1;
	m_arr = new_arr;
}


template<typename Type>
inline void DynamicArray<Type>::erase(const unsigned int _pos)
{
	if (!is_valid_index(_pos))
	{
		std::cerr << "Index out of range!!!\n";
		return;
	}

	Type* new_arr = new Type[m_len - 1];
	unsigned int index = 0;
	while (index < _pos)
	{
		new_arr[index] = m_arr[index];
		index++;
	}
	while (index < m_len - 1)
	{
		new_arr[index] = m_arr[index + 1];
		index++;
	}

	delete[] m_arr;
	m_len -= 1;
	m_arr = new_arr;
}


template<typename Type>
inline void DynamicArray<Type>::remove(const Type _value)
{
	Type* new_arr = new Type[m_len - 1];
	unsigned int index = 0;
	while (m_arr[index] != _value)
	{
		new_arr[index] = m_arr[index];
		index++;
	}
	while (index < m_len - 1)
	{
		new_arr[index] = m_arr[index + 1];
		index++;
	}

	delete[] m_arr;
	m_len -= 1;
	m_arr = new_arr;
}


template<typename Type>
inline void DynamicArray<Type>::shift_right(const unsigned int _step)
{
	for (unsigned int i = m_len; i - _step >= 0; i++)
	{
		m_arr[i] = m_arr[i - _step];
		m_arr[i - _step] = 0;
	}
}


template<typename Type>
inline void DynamicArray<Type>::shift_left(const unsigned int _step)
{
	for (unsigned int i = 0; i + _step < m_len; i++)
	{
		m_arr[i] = m_arr[i + _step];
		m_arr[i + _step] = 0;
	}
}


template<typename Type>
inline void DynamicArray<Type>::cycle_shift_right(const unsigned _step)
{
	reverse(m_len - _step, m_len - 1);
	reverse(0, m_len - _step - 1);
	reverse(0, m_len - 1);
}


template<typename Type>
inline void DynamicArray<Type>::reverse(const unsigned int _start, const unsigned int _end)
{
	if (!is_valid_index(_start) && !is_valid_index(_end))
	{
		std::cerr << "Index out of range!!!\n";
		return;
	}
	if (_start > _end)
	{
		std::cerr << "Not valid end index!\n";
		return;
	}

	for (unsigned int i = 0; i < (_end - _start) % 2 + (_end - _start) / 2; i++)
	{
		std::swap(m_arr[_start + i], m_arr[_end - i]);
	}
}


template<typename Type>
inline void DynamicArray<Type>::cycle_shift_left(const unsigned _step)
{
	reverse(0, _step - 1);
	reverse(_step, m_len - 1);
	reverse(0, m_len - 1);
}


template<typename Type>
inline DynamicArray<Type> DynamicArray<Type>::operator-=(const unsigned int _pos)
{
	erase(_pos);
	return *this;
}


template<typename Type>
inline DynamicArray<Type> DynamicArray<Type>::operator+=(const Type _value)
{
	push_back(_value);
	return *this;
}



template<typename Type>
inline DynamicArray<Type> DynamicArray<Type>::operator+(const Type _value)
{
	DynamicArray<Type> new_obj(*this);
	new_obj.push_back(_value);
	return new_obj;
}


template<typename Type>
inline DynamicArray<Type>& DynamicArray<Type>::operator+=(const DynamicArray<Type>& _other)
{
	if (this == &_other)
	{
		return;
	}
	Type* new_arr = new Type[m_len + _other.m_len];
	for (unsigned int i = 0; i < m_len; i++)
	{
		new_arr[i] = m_arr[i];
	}
	for (unsigned int i = 0; i < _other.m_len; i++)
	{
		new_arr[m_len + i] = _other.m_arr[i];
	}
	m_len += _other.m_len;
	delete[] m_arr;
	m_arr = new_arr;
	return *this;
}

template<typename Type>
inline DynamicArray<Type> DynamicArray<Type>::operator+(const DynamicArray<Type>& _other)
{
	DynamicArray<Type> new_obj(*this);
	new_obj += _other;
	return new_obj;
}


template<typename Type>
inline DynamicArray<Type> DynamicArray<Type>::operator-(const Type _value)
{
	remove(_value);
}


template<typename Type>
inline Type& DynamicArray<Type>::operator[](const unsigned int _pos)
{
	if (!is_valid_index(_pos))
	{
		throw("Not valid index\n");
	}
	return m_arr[_pos];
}


template<typename Type>
inline DynamicArray<Type>& DynamicArray<Type>::operator=(const DynamicArray<Type>& _other)
{
	if (this == &_other)
	{
		return *this;
	}
	if (m_len != _other.m_len)
	{
		m_len = _other.m_len;
		delete[] m_arr;
		m_arr = new Type[m_len];
	}
	for (unsigned int i = 0; i < m_len; i++)
	{
		m_arr[i] = _other.m_arr[i];
	}
	return *this;
}

template<typename Type>
inline bool DynamicArray<Type>::operator==(const DynamicArray<Type>& _other)
{
	if (this == &_other)
	{
		return true;
	}
	if (m_len != _other.m_len)
	{
		return false;
	}
	for (unsigned int i = 0; i < m_len; i++)
	{
		if (m_arr[i] != _other.m_arr[i])
		{
			return false;
		}
	}
	return true;
}


template<typename Type>
inline bool DynamicArray<Type>::operator!=(const DynamicArray<Type>& _other)
{
	return !operator==(_other);
}


template<typename Type>
std::ostream& operator<<(std::ostream& _out, const DynamicArray<Type>& _obj)
{
	_out << '[';
	for (unsigned int i = 0; i < _obj.m_len - 1; i++)
	{
		_out << _obj.m_arr[i] << ", ";
	}
	_out << _obj.m_arr[_obj.m_len - 1] << ']';
	return _out;
}


template<typename Type>
std::istream& operator>>(std::istream& _in, DynamicArray<Type>& _obj)
{
	for (unsigned int i = 0; i < _obj.m_len; i++)
	{
		_in >> _obj.m_arr[i];
	}
	return _in;
}

template<typename Type>
inline bool DynamicArray<Type>::is_valid_index(const unsigned int _pos)
{
	if (_pos < m_len && _pos > -1)
	{
		return true;
	}

	return false;
}