#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

#include "ListClass.h"
#include "VectorClass.h"

using namespace std;

// �ݺ��� : Iterator
// -> ��ȸ��
// -> algorithm�̶� �Լ� �Ű������� ���� ���δ�.
// 
// map
// -> �����Ʈ��
// key�� value�� ������ ������ ���� (Ʈ������)
// map���� Ű�� ã�µ� �ɸ��� �ð� ... log2 N
// 

class Player
{
public:
	Player() : _playerID(0) {}
	Player(int id) : _playerID(id) {}

	int _playerID; // Key
};

int main()
{
#pragma region Iterator
	ListClass<int> myList;

	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);
	myList.push_back(4);
	myList.push_back(5);

	ListClass<int>::Iterator iter = myList.begin();

	for (iter; iter != myList.end(); iter++)
	{
		cout << *iter << endl;
	}
#pragma endregion
	srand(static_cast<unsigned int>(time(nullptr)));
	map<int, Player*> m;

	map<int, Player*>::iterator mapiter = m.begin();

	for (int i = 0; i < 1000; i++)
	{
		pair<int, Player*> tempPair;
		tempPair.first = rand() % 1000;
		tempPair.second = new Player(i);
		m.insert(tempPair);
		//m.insert(make_pair<int, Player*>(rand() % 10000, new Player(i)));
		m[rand() % 1000] = new Player(i);
	}

	mapiter = m.begin();
	for (; mapiter != m.end(); ++mapiter)
	{
		cout << "Ű : " << (*mapiter).first << " �� : " << (*mapiter).second << endl;
	}

	return 0;
}