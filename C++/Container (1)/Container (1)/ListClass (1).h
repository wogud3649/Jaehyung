#pragma once
template <typename T>
struct Node
{
	Node() : data(T()), prev(nullptr), next(nullptr)
	{}

	Node(const T& newData) : data(newData), prev(nullptr), next(nullptr)
	{}

	T data;
	Node<T>* prev;
	Node<T>* next;
};

template <typename T>
class ListClass
{
public:
	class Iterator
	{
	public:
		Iterator() : ptr(nullptr) {}
		Iterator(Node<T>* node) : ptr(node) {}
		~Iterator() {}

		Iterator& operator++()
		{
			ptr = ptr->next;
		}

		Iterator& operator++(int)
		{
			Iterator temp = *this;

			ptr = ptr->next;
			return temp;
		}

		T& operator*()
		{
			return ptr->data;
		}

		bool operator==(const Iterator& iter)
		{
			return ptr == iter.ptr;
		}

		bool operator!=(const Iterator& iter)
		{
			return ptr != iter.ptr;
		}

	private:
		Node<T>* ptr;
	};
	ListClass()
		: _head(nullptr)
		, _size(0)
	{
		_head = new Node<T>();
		_head->prev = _head;
		_head->next = _head;
	}
	~ListClass()
	{
		clear();
	}

	void push_back(const T& value)
	{
		AddNode(_head->prev, value);
	}

	void push_front(const T& value)
	{
		AddNode(_head, value);
	}

	void pop_back()
	{
		RemoveNode(_head->prev);
	}

	void pop_front()
	{
		if (_head->next != nullptr)
		{
			_head->next = _head->next->next;
			delete _head->next->prev;
			_head->next->prev = _head;
			_size--;
		}
	}

	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);

		Node<T>* prevNode = before;
		Node<T>* nextNode = before->next;

		// »ðÀÔÇÒ ¶§ prev¶û ¿¬°áÇÏ±â
		prevNode->next = newNode;
		newNode->prev = prevNode;

		// next¶û ¿¬°áÇÏ±â
		newNode->prev = newNode;
		newNode->next = nextNode;
		
		_size++;

		return newNode;
	}

	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->prev;
		Node<T>* nextNode = node->next;

		prevNode->next = nextNode;
		nextNode->prev = prevNode;

		delete node;

		--_size;

		return nextNode;
	}

	const int& operator[](const int& index) 
	{
		if (index >= _size)
			return -1;

		Node<T>* target = _head;
		for (int i = 0; i <= index; i++)
		{
			target = target->next;
		}

		return target->data;
	}

	void clear()
	{
		Node<T>* target = _head->next;
		while (true)
		{
			if (target == _head)
				break;
			target = RemoveNode(target);
		}
		_size = 0;
	}

	unsigned int size() const { return _size; }

	Iterator begin() { return Iterator(_head->next); }
	Iterator end() { return Iterator(_head); }

private:
	unsigned int _size;
	Node<T>* _head;
};