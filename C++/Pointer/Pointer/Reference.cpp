#include <iostream>

using namespace std;

// ����
// 1. �����丵
// 2. �迭�� ���ؼ� ����

// ������ vs ����(Reference)

// ����
// C++
// 1. ����
// 1. int aRef = a;
// ==> aRef�� a�� �����̴�.

// �������
// �����Ϳ� ������ ����.

// ������ ����
// 1. ���� ���ϴ�.
// 2. ������

// ������ ����
// 1. ���� ���ϴ�.
// 2. �ʱ�ȭ�� ������ �ʿ��ϴ�.
// 3. nullptr�� �ʱ�ȭ�� �� ����. => ���� ���� ���� ���� ����.

// �����Ϳ� ������ ������
// 1. ������ ������ �����ϴ�.
// 2. ������ �Ѵ� �����Ϳ� �����ϰ� �����Ѵ�. (������� ����)
// 3. ũ��� 32��Ʈ ȯ�濡�� 4����Ʈ, 64��Ʈ ȯ�濡�� 8����Ʈ

// �����Ϳ� ������ ������
// 1. �����ʹ� nullptr�� ���� ���� ���� �� �ִ�/ ref�� ���� ���̶��� ����.
// 2. ref �� c++�������� �����̶�� �ؼ��Ѵ�.

struct Player
{
	int _hp;
	int _level;
};

// Call by Value
void PrintPlayer(Player p)
{
	cout << p._hp << endl;
	cout << p._level << endl;
}

// Call by Address
// ���� ����
void PrintPlayer(Player* ptr)
{
	cout << ptr->_hp << endl;
	cout << ptr->_level << endl;
}

// Call by Reference
// ���� ����
// ���� ������ ���ƺ��� -> const Player& p... �б�����
void PrintPlayer(const Player& ref)
{
	cout << ref._hp << endl;
	cout << ref._level << endl;
}

int main(void)
{
	int a = 5;
	int* aPtr = &a;
	int& aRef = a;

	int* bPtr = nullptr;
	// int& bRef; (x)

	aRef = 3;

	int b = 5;
	int* bPtr_ = &b;

	int** bPtrPtr_ = &bPtr_;
	int*& bPtrRef_ = bPtr_;

	*(*bPtrPtr_) = 10;
	cout << b << endl;



	return 0;
}