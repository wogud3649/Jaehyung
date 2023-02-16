#include <iostream>
#include <vector>
#include <list>

using namespace std;

// list
// 장점
// 1. 중간 삽입 삭제가 vector에 비해서 빠르다 (미리 찾아놓은 경우)
// -> 첫삽입 삭제 -> 상수
// 
// 단점
// 1. 임의 접근이 vector에 비해서 느리다.(N번 걸린다.)

class Player
{
public:
	void operator[](const int& index)
	{

	}
};

int main()
{
	list<int> l;
	
	for (int i = 0; i < 10; i++)
	{
		l.push_back(i);
	}

	l.pop_front();
	l.pop_back();
	l.push_front(50);

	return 0;
}