#include <iostream>

using namespace std;

// �Լ�������
// ���� : �ñ״�ó�� ������ � �Լ��� ���� ���߿� ȣ���� �� �ִ�.
// ���� : �Լ� ��ü�� ������ �� �Ӽ�(�������)�� ���� �� ����.

// �Լ���ü
// - �Ӽ��� ���� �� �ִ� �Լ�
// - ��ü�� �̸� ������ �ΰ�, �Լ� ȣ���� ���߿� �� �� �ִ�.
// - STL -> �˰��� �ʿ��ϴ�.

struct Functor
{
	void operator()()
	{
		cout << "HelloWorld!" << endl;
		cout << "�Ӽ� : " << _value << endl;
	}

	void operator()(int& a)
	{
		++a;
	}

	int _value = 5;
};

int main()
{
	int aInt = 0;

	Functor functor;
	functor();
	functor._value = 100;
	functor();

	functor(aInt);

	return 0;
}