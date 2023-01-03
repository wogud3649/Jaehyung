#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

template<typename T, typename Container = deque<T>>
class Stack
{
public:
	Stack() { v.clear(); }
	~Stack() {}

	void push(const T& value)
	{
		v.push_back(value);
	}

	void pop()
	{
		v.pop_back();
	}

	const T& top()
	{
		return v.back();
	}

	bool empty()
	{
		return v.empty();
	}

	size_t size()
	{
		return v.size();
	}

private:
	Container v;
};

template<typename T, typename Container = deque<T>>
class Queue
{
public:
	void push(const T& value)
	{
		l.push_front(value);
	}

	void pop()
	{
		l.pop_front();
	}

	const T& front()
	{
		return l.front();
	}

	bool empty()
	{
		return l.empty();
	}

private:
	deque<int> l;
};

int main()
{
	Stack<int> s;
	
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	while (true)
	{
		if (s.empty() == true)
			break;
		// stack 데이터를 활용
		cout << s.top() << endl;

		s.pop();
	}

	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	while (true)
	{
		if (q.empty() == true)
			break;

		// queue 의 데이터의 활용
		cout << q.front() << endl;

		q.pop();
	}

	return 0;
}