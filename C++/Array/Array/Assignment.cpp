// 과제 : 로또번호 뽑기
// 1. 랜덤한 1 ~ 45까지의 번호를 7개 뽑는다. (중복허용 X)
// ---> 1. 1 ~ 45까지의 배열을 만들고 섞기(Shuffle)
// ---> 2. 난수를 뽑고 어느 배열에 저장. -> 난수 뽑고 저장 (배열에 가서 난수가 있으면다시 계속 반복) -> 배열이 7개가 완성되면 완료
// 2. 7개 나온 숫자를 정렬한다.

// 객체지향의 3속성
// 1. 은닉성
// 2. 상속성
// 3. 다형성

#include<iostream>

using namespace std;

void SetArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = i + 1;
	}
}

void Shuffle(int arr[], int size)
{
	int temp;
	for (int i = 0; i < 10000; i++)
	{
		int rn = rand() % 45; // 11
		int rn2 = rand() % 45; // 10
		while (rn == rn2)
		{
			rn2 = rand() % 45;
		}
		temp = arr[rn];
		arr[rn] = arr[rn2];
		arr[rn2] = temp;
	}
}

void Pick7Numbers(int arr[], int arr2[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arr2[i] = arr[i];
	}
}

void SortArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		
	}
}

void PrintArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
}

int main()
{
	srand(unsigned int(time(nullptr)));
	int arr[45], arr2[7];
	int arrSize = sizeof(arr) / sizeof(int);
	int arrSize2 = sizeof(arr2) / sizeof(int);

	SetArray(arr, arrSize);
	Shuffle(arr, arrSize);
	Pick7Numbers(arr, arr2, arrSize2);
	PrintArray(arr2, arrSize2);
	SortArray(arr2, arrSize2);
	

	return 0;
}