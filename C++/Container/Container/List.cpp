#include <iostream>
#include <vector>
#include <list>

using namespace std;

// list
// ����
// 1. �߰� ���� ������ vector�� ���ؼ� ������ (�̸� ã�Ƴ��� ���)
// -> ù���� ���� -> ���
// 
// ����
// 1. ���� ������ vector�� ���ؼ� ������.(N�� �ɸ���.)

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