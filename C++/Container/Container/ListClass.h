#pragma once
#include <iostream>

using namespace std;

struct Node
{
	Node() : data(0), prev(nullptr), next(nullptr)
	{}

	Node(const int& newData) : data(newData), prev(nullptr), next(nullptr)
	{}

	int data;
	Node* prev;
	Node* next;
};

// 환형 연결 리스트
class ListClass
{
public:
	ListClass()
	: _head(nullptr)
	, _size(0)
	{
		_head = new Node();
		_head->prev = _head;
		_head->next = _head;
	}

	void push_back(const int& value)
	{
		AddNode(_head->prev, value);
	}

	void push_front(const int& value)
	{
		//TODO
	}

	void pop_back()
	{
		//TODO
	}

	void pop_front()
	{
		//TODO
	}

	Node* AddNode(Node* before, const int& value)
	{
		// before 노드 다음에 newNode를 만들어서 넣고
		// newNode 반환
	}

	const int& operator[](const int& index)
	{
		if (index >= _size)
			return -1;

		Node* target = _head;
		for (int i = 0; i <= index; i++)
		{
			target = target->next;
		}

		return target->data;
	}

	unsigned int size() { return _size; }


private:
	unsigned int _size;
	Node* _head;
};