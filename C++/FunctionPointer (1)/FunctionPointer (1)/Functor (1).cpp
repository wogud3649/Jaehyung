#include <iostream>
#include <algorithm>
using namespace std;

// 과제
// 1. 복습
// -> 함수객체에 대해서 구글에서 찾아보기
// 2. C++ vector에 대해서 조사.

// 함수포인터
// 장점 : 시니그쳐만 맞으면 어떤 함수던 간에 나중에 호출할 수 있다.
// 단점 : 함수객체랑 비교했을 때 속성(멤버변수)을 가질 수 없다.

// 함수객체
// - 속성을 가질 수 있는 함수
// - 객체만 미리 선언해두고, 함수 호출을 나중에 할 수 있다.
// - STL -> 알고리즘에 필요하다

struct Functor
{
	void operator()()
	{
		cout << "Hello World!" << endl;
		cout << "속성 : " << _value << endl;
	}

	void operator()(int& a)
	{
		++a;
	}

	int _value = 5;
};

struct Item
{
public:
	int _itemKey; // 아이템 고유 키
	int _itemValue; // 전설, 신화, 에픽...
	int _itemPrice; // 아이템 가격
};

struct FindItem_Functor
{
public:
	bool operator()(const Item* item)
	{
		if (this->_itemKey == item->_itemKey && this->_itemValue == item->_itemValue && this->_price == item->_itemPrice)
			return true;
		else if (this->_itemKey == item->_itemKey && this->_price == item->_itemPrice)
			return true;
		return false;
	}
	int _itemKey;
	int _itemValue;
	int _price;
};

struct ItemSort
{
	bool operator()(const Item* a, const Item* b)
	{
		if (a->_itemPrice > b->_itemPrice)
		{
			return true;
		}
		return false;
	}
};
void PrintItemInfo(Item* item)
{
	if (item == nullptr)
		return;
	cout << "Item의 키 : " << item->_itemKey << endl;
	cout << "Item의 등급 : " << item->_itemValue << endl;
	cout << "Item의 가격 : " << item->_itemPrice << endl;
}

Item* FindItemByKey(Item* items[], int size, int itemKey)
{
	for (int i = 0; i < size; i++)
	{
		if (items[i]->_itemKey == itemKey)
			return items[i];
	}

	return nullptr;
}

Item* FindItemByPrice(Item* items[], int size, int itemPrice)
{
	for (int i = 0; i < size; i++)
	{
		if (items[i]->_itemPrice == itemPrice)
			return items[i];
	}

	return nullptr;
}

template <typename T>
Item* FindItem(Item* items[], int size, T& finder)
{
	for (int i = 0; i < size; i++)
	{
		if (finder(items[i]))
			return items[i];
	}
	return nullptr;
}

int main()
{
	const int ITEMSIZE = 10;

	Item* items[10];

	for (int i = 0; i < ITEMSIZE; i++)
	{
		Item* item = new Item();
		item->_itemKey = i;
		item->_itemValue = 10 - i;
		item->_itemPrice = 10000 - i * 500;
		items[i] = item;
	}

	// itemKey == 5인 애를 찾겠다.
	/*PrintItemInfo(FindItemByKey(items, ITEMSIZE, 5));
	PrintItemInfo(FindItemByPrice(items, ITEMSIZE, 8500));*/
	FindItem_Functor functor;
	functor._itemKey = 5;
	functor._price = 7500;
	PrintItemInfo(FindItem(items, ITEMSIZE, functor));

	// itemKey 0, Value = 10, Price = 10000
	functor._itemKey = 0;
	functor._price = 10000;
	functor._itemValue = 10;
	PrintItemInfo(FindItem(items, ITEMSIZE, functor));

	ItemSort sorter;
	std::sort(items, items + ITEMSIZE, sorter);

	return 0;
}