#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int lowIndex = left + 1;
	int highIndex = right;

	while (true)
	{
		if (lowIndex > highIndex)
			break;

		while (lowIndex <= right && pivot >= v[lowIndex])
		{
			lowIndex++;
		}

		while (highIndex >= left && pivot < v[highIndex])
		{
			highIndex--;
		}

		if (lowIndex <= highIndex)
			std::swap(v[lowIndex], v[highIndex]);
	}

	std::swap(v[highIndex], v[left]);

	return highIndex;
}
void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivotIndex = Partition(v, left, right);

	cout << left << " ~ " << pivotIndex - 1 << endl;
	QuickSort(v, left, pivotIndex - 1);
	QuickSort(v, pivotIndex + 1, right);
}

int main()
{
	vector<int> v = { 55 ,30 ,15 ,100 ,1 ,5 ,70 ,30 };

	//sort(v.begin(), v.end());
	QuickSort(v, 0, v.size() - 1);

	// 병합 정렬

	return 0;
}