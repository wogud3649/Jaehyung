#include <iostream>
using namespace std;

template<typename T>
void Print(T data)
{
	cout << data << endl;
}
template<>
void Print(float data)
{
	cout << data << endl;
}

template<typename T>
void Print(T* data)
{
	cout << "������ �Լ� : " << *data << endl;
}

template<typename T>
class Character
{
public:
	void Set(T name)
	{
		this->name = name;
	}
	void Print()
	{
		cout << "ĳ���� : " << name < endl;
	}
private:
	T name;
};

int main()
{
	int i = 0;
	Print(i);
	float j = 2.001f;
	Print(j);
}