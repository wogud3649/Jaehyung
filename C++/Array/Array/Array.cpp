#include <iostream>

using namespace std;

// �迭
// [][][][][][][][]
// int arr[5];
// int arr[5] = {1,2,3,4,5};

// �����Ͱ� �޸𸮿� �Ϸķ� ������ �Ǿ��ִ�.

// �����迭
// ���� : ��Ÿ�ӿ� �ٲ��� �ʴ�.

// index : ����
// for���� Ȱ��

// �迭�� �̸� ������ó�� �����Ѵ�.
	// �迭���� �迭�� �̸��� �迭�� ù��° �ּҸ� ��Ÿ����.

// ������ ����
// + : �޸� �������� (��Ʈ * delta)
// - : (��Ʈ�� ũ�� ����Ʈ * delta��ŭ ����)
// ++, --
// [x] : �������ٿ����� x��� �ε����� �̿��ؼ� �ּҿ� ������ �� �ִ�.
int* aPtr;


struct Player
{
	int _hp;
	int _mp;
};

// �Լ��� �迭�� �ѱ�� : ����� ���� �Ѱ���� �Ѵ�.
// �Լ������� ���� �迭�� �����ͷ� �޴´�.
void PrintArr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << *(arr + i) << endl;
	}
}

void SetPlayer(Player& p)
{
	p._hp = 10;
	p._mp = 5;
}

void PrintPlayer(const Player& p)
{
	cout << p._hp << endl;
	cout << p._mp << endl;
}

void PrintArr2(int arr[][3], int size)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			cout << arr[y][x] << endl;
		}
	}
}

int main()
{
	int arr[5] = { 1,2,3,4,5 };

	// �迭�� ũ��
	int arrSize = sizeof(arr) / sizeof(int);
	cout << sizeof(arr) << endl;

	/*cout << arr[0] << endl;
	cout << arr[1] << endl;
	cout << arr[2] << endl;
	cout << arr[3] << endl;
	cout << arr[4] << endl;*/

	/*for (int i = 0; i < arrSize; i++)
	{
		cout << arr[i] << endl;
	}*/

	PrintArr(arr, arrSize);

	Player p;
	p._hp = 0;
	SetPlayer(p);
	PrintPlayer(p);

	Player playerArr[3];
	for (int i = 0; i < 3; i++)
	{
		playerArr[i]._hp = 0;
		playerArr[i]._mp = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		SetPlayer(playerArr[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		PrintPlayer(playerArr[i]);
	}

	int arr2[2][3] =
					{ { 1,2,3 },
					  { 4,5,6 }
};
	PrintArr2(arr2, 2);

	return 0;
}