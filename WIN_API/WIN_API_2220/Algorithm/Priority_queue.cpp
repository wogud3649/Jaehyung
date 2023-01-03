#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// 최대 힙
template<typename T,
		 typename Container = vector<T>,
		 typename Pred = less<T>>
class Priority_Queue
{
public:
	Priority_Queue() {}
	void push(const T& value)
	{
		v.push_back(value);

		// 규칙 확인

		int now = static_cast<int>(v.size() - 1); // 맨 마지막

		while (true)
		{
			if (now <= 0)
				break;

			int parent = (now - 1) / 2;

			if (Pred()(v[now], v[parent]))
			{
				break;
			}

			std::swap(v[now], v[parent]);
			now = parent;
		}
	}

	void pop()
	{
		v[0] = v.back();
		v.pop_back();

		// 규칙 확인
		int now = 0;

		while (true)
		{
			int leftChild = 2 * now + 1;
			int rightChild = 2 * now + 2;

			if (leftChild >= (int)v.size())
				break;

			int next = now;

			if (Pred()(v[next], v[leftChild]))
				next = leftChild;

			if (rightChild < (int)v.size() && Pred()(v[next], v[rightChild]))
				next = rightChild;

			if (next == now)
				break;

			std::swap(v[now], v[next]);
			now = next;
		}
	}

	const int& top()
	{
		return v[0];
	}

	bool empty()
	{
		return v.empty();
	}
	
private:
	Container v;
};

int main()
{
	Priority_Queue<int, vector<int>, greater<int>> pq1; // 최소 힙
	Priority_Queue<int, vector<int>, less<int>> pq2;
	// 1. 퀵정렬 (qsort, std::sort)
	// 2. 병합정렬 (merge, std::stable_sort)
	// 3. 힙정렬 (heap, std::partial_sort)

	pq1.push(10);
	pq1.push(7);
	pq1.push(8);
	pq1.push(6);
	pq1.push(3);
	pq1.push(15);

	cout << pq1.top() << endl;
	pq1.pop();
	cout << pq1.top() << endl;
	pq1.pop();
	cout << pq1.top() << endl;

	pq2.push(10);
	pq2.push(7);
	pq2.push(8);
	pq2.push(6);
	pq2.push(3);
	pq2.push(15);

	cout << pq2.top() << endl;
	pq2.pop();
	cout << pq2.top() << endl;
	pq2.pop();
	cout << pq2.top() << endl;
	
	return 0;
}