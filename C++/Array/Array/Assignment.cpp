// ���� : �ζǹ�ȣ �̱�
// 1. ������ 1 ~ 45������ ��ȣ�� 7�� �̴´�. (�ߺ���� X)
// ---> 1. 1 ~ 45������ �迭�� ����� ����(Shuffle)
// ---> 2. ������ �̰� ��� �迭�� ����. -> ���� �̰� ���� (�迭�� ���� ������ ������ٽ� ��� �ݺ�) -> �迭�� 7���� �ϼ��Ǹ� �Ϸ�
// 2. 7�� ���� ���ڸ� �����Ѵ�.

// ��ü������ 3�Ӽ�
// 1. ���м�
// 2. ��Ӽ�
// 3. ������

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