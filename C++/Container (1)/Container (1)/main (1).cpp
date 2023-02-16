#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

#include "ListClass.h"
#include "VectorClass.h"

using namespace std;

// 반복자 : Iterator
// -> 순회자
// -> algorithm이랑 함수 매개변수로 많이 쓰인다.
// 
// map
// -> 레드블랙트리
// key와 value로 구성된 노드들의 집합 (트리집합)
// map에서 키로 찾는데 걸리는 시간 ... log2 N
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
		cout << "키 : " << (*mapiter).first << " 값 : " << (*mapiter).second << endl;
	}

	return 0;
}