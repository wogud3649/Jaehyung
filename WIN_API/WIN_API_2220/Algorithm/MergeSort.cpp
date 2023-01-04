#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// ���� ����(Divide And Conquer)
// - ���� : ������ �ִ��� �ܼ��ϰ� �����Ѵ�
// - ���� : ������ �ذ��Ѵ�.
// - ���� : ����� �����ϸ� �������Ѵ�.

// Quick, Merge, Heap
// -> �־��� ��� : n^2
// ��������� : n * log2n

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	// { 55 ,30 ,15 ,100 ,1 ,5 ,70 ,30 };
	int leftIndex = left;
	int rightIndex = mid + 1;

	// left 0
	// mid 0
	// right 1
	vector<int> temp;

	while (true)
	{
		if (leftIndex > mid || rightIndex > right)
			break;
		if (v[leftIndex] <= v[rightIndex])
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
		else
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	// ������ ���� ����
	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	// �������� ���� ����
	else
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	// { 55 ,30 ,15 ,100 ,1 ,5 ,70 ,30 };
	// ����
	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	// ����, ����
	MergeResult(v, left, mid, right);

}

int main()
{
	vector<int> v = { 55 ,30 ,15 ,100 ,1 ,5 ,70 ,30 };

	//std::stable_sort(v.begin(), v.end());
	MergeSort(v, 0, 7);


	return 0;
}