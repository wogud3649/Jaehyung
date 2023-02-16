#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

struct Vector2
{
	bool operator<(const Vector2& other)
	{
		float aLength = x * x + y * y;
		float bLength = other.x * other.x + other.y * other.y;

		if (aLength < bLength)
			return true;
		return false;
	}
	int x;
	int y;
};

int main()
{
#pragma region Lambda 기초
	vector<int> v;
	for (int i = 0; i < 30; i++)
	{
		if (i % 2 == 0)
		{
			v.push_back(i);
		}
	}
	struct Finder
	{
		bool operator() (const int& value)
		{
			if (value > 25)
				return true;
			return false;
		}

		int compare = 25;
	};

	// 25보다 큰 첫번째 원소의 iter
	// [] : Capture
	// () : 매개변수
	// -> : 반환함 : 람다함수의 반환형
	// {} : 함수 정의부

	int num = 25;
	auto iter = std::find_if(v.begin(), v.end(), [num](const int& value)->bool
		{
			if (value > num)
				return true;
			return false;
		});
#pragma endregion
	srand(static_cast<unsigned int>(time(nullptr)));
	vector<Vector2> myVec;

	for (int i = 0; i < 20; i++)
	{
		Vector2 temp;
		temp.x = rand() % 21;
		temp.y = rand() % 21;
		myVec.push_back(temp);
	}

	// x가 10보다 크고 y가 5보다 작은 Vector2가 있는지 확인해 주세요
	struct FindVector2
	{
		bool operator()(const Vector2& value)
		{
			if (value.x > v.x && value.y < v.y)
			{
				return true;
			}

			return false;
		}

		Vector2 v;
	};

	FindVector2 finder;
	finder.v.x = 10;
	finder.v.y = 5;

	Vector2 v2;
	v2.x = 10;
	v2.y = 5;
	auto vector2Iter = std::find_if(myVec.begin(), myVec.end(), [v2](const Vector2& value)->bool
		{
			if (value.x > v2.x && value.y < v2.y)
				return true;
			return false;
		});

	Vector2 finderVector;
	finderVector.x = 10;
	finderVector.y = 5;
	auto vector2Iter = std::find_if(myVec.begin(), myVec.end(), [finderVector](const Vector2& temp)->bool
		{
			if (temp.x > finderVector.x && temp.y < finderVector.y)
				return true;
			return false;
		});

	// sort
	// Vector2의 크기가 작은 순으로 나열해주세요.
	// 크기 : 길이
	std::sort(myVec.begin(), myVec.end());
	std::sort(myVec.begin(), myVec.end(), [](const Vector2& temp1, const Vector2& temp2)-> bool
		{
			int length1 = pow(temp1.x, 2) + pow(temp1.y, 2);
			int length2 = pow(temp2.x, 2) + pow(temp2.y, 2);
			if (length1 < length2)
				return true;
			return false;
		});

	std::sort(myVec.begin(), myVec.end(), [](const Vector2& a, const Vector2& b)-> bool
		{
			int aLength = (a.x * a.x + a.y * a.y);
			int bLength = (b.x * b.x + b.y * b.y);
			if (aLength < bLength)
				return true;
			return false;
		});

	return 0;
}