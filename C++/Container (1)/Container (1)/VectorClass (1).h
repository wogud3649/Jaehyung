#pragma once
#include <iostream>
using namespace std;

template <typename T>
class VectorClass
{
public:
	VectorClass()
	: _size(0)
	, _capacity(0)
	, _data(nullptr)
	{
	
	}
	
	~VectorClass()
	{
		_size = 0;
		_capacity = 0;
		if (_data != nullptr)
			delete _data;
	}

	void push_back(const T& value)
	{
		// �����Ͱ� ���ƴ�.
		if (_size == _capacity)
		{
			unsigned int newCapacity = _capacity * 1.5f;
			if (newCapacity <= 1)
				++newCapacity;

			reserve(newCapacity);
		}
		// �����Ͱ� ��ġ�� �ʾҴ�.
		_data[_size];
		
		++_size;
	}

	void reserve(const int& capacity)
	{
		_capacity = capacity;

		T* newData = new T[_capacity];

		// ������ ����
		for (int i = 0; i < _size; i++)
		{
			newData[i] = _data[i];
		}

		if (_data != nullptr)
			delete _data;

		_data = newData;
	}

	const T& operator[](unsigned int index)
	{
		if (index >= _size)
		{
			cout << "���� �߻�" << endl;
			return INT_MIN;
		}

		return _data[index];
	}

	void clear()
	{
		_size = 0;
	}

	unsigned int size() { return _size; }
	unsigned int capacity() { return _capacity; }

private:
	T* _data;
	unsigned int _size;
	unsigned int _capacity;
};