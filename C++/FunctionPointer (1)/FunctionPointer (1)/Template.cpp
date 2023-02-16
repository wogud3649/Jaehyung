#include <iostream>

using namespace std;

// Template
// : ���� Ʋ
// -> Ŭ����, �Լ��� ���� Ʋ

// class : ���赵
// -> ��ü�� ���� Ʋ

// �Լ� ���ø�
template <typename T = int> // ���ø��� �⺻����
T Add(T a, T b)
{
	return a + b;
}

// ���ø��� Ư��ȭ
template<>
int* Add(int* a, int* b)
{
	cout << "Ptr�� ���߽��ϴ�." << endl;
	return a;
}

// Ŭ���� ���ø�
// ������ ��
// - ������ �ȶ�
// - ���� ������ �� ����.
template <typename T = int>
class Player
{
public:
	Player()
	{
	}
public:
	T _hp[10];
};

template<>
class Player<double>
{
public:
private:
	double _hp[10];
	int _atk;
};

int main()
{
	int a = 1;
	int b = 2;
	cout << Add(1, 2) << endl;

	Player<int> p;

	return 0;
}