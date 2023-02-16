#include <iostream>

using namespace std;

// 배열
// [][][][][][][][]
// int arr[5];
// int arr[5] = {1,2,3,4,5};

// 데이터가 메모리에 일렬로 나열이 되어있다.

// 정적배열
// 정적 : 런타임에 바뀌지 않는.

// index : 색인
// for문의 활용

// 배열의 이름 포인터처럼 동작한다.
	// 배열에서 배열의 이름은 배열의 첫버째 주소를 나타낸다.

// 포인터 연산
// + : 메모리 번지수를 (힌트 * delta)
// - : (힌트의 크기 바이트 * delta만큼 뺀다)
// ++, --
// [x] : 임의접근연산자 x라는 인덱스를 이용해서 주소에 접근할 수 있다.
int* aPtr;


struct Player
{
	int _hp;
	int _mp;
};

// 함수로 배열을 넘기기 : 사이즈도 같이 넘겨줘야 한다.
// 함수에서는 정적 배열을 포인터로 받는다.
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

	// 배열의 크기
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