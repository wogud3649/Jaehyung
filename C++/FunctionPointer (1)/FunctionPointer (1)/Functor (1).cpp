#include <iostream>
#include <algorithm>
using namespace std;

// ����
// 1. ����
// -> �Լ���ü�� ���ؼ� ���ۿ��� ã�ƺ���
// 2. C++ vector�� ���ؼ� ����.

// �Լ�������
// ���� : �ôϱ��ĸ� ������ � �Լ��� ���� ���߿� ȣ���� �� �ִ�.
// ���� : �Լ���ü�� ������ �� �Ӽ�(�������)�� ���� �� ����.

// �Լ���ü
// - �Ӽ��� ���� �� �ִ� �Լ�
// - ��ü�� �̸� �����صΰ�, �Լ� ȣ���� ���߿� �� �� �ִ�.
// - STL -> �˰��� �ʿ��ϴ�

struct Functor
{
	void operator()()
	{
		cout << "Hello World!" << endl;
		cout << "�Ӽ� : " << _value << endl;
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
	int _itemKey; // ������ ���� Ű
	int _itemValue; // ����, ��ȭ, ����...
	int _itemPrice; // ������ ����
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
	cout << "Item�� Ű : " << item->_itemKey << endl;
	cout << "Item�� ��� : " << item->_itemValue << endl;
	cout << "Item�� ���� : " << item->_itemPrice << endl;
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

	// itemKey == 5�� �ָ� ã�ڴ�.
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