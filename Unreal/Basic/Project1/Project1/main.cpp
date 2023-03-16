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
	cout << "포인터 함수 : " << *data << endl;
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
		cout << "캐릭터 : " << name < endl;
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