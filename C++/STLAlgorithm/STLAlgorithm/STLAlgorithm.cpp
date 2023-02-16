#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v;

	v.push_back(0);
	v.push_back(1);
	v.push_back(7);
	v.push_back(3);
	v.push_back(5);
	v.push_back(11);
	v.push_back(13);

	// find
	// 7을 8로 바꿔주세요.
	vector<int>::iterator iter;
	for (iter = v.begin(); iter != v.end(); iter++)
	{
		if (*iter == 7)
		{
			*iter = 8;
			break;
		}
	}

	iter = std::find(v.begin(), v.end(), 7);
	if (iter!= v.end())
		*iter = 8;

	// find_if
	// 3보다 작은 값이 있는 원소의 위치를 찾고 1로 바꿔주세요
	for (iter = v.begin(); iter != v.end(); iter++)
	{
		if (*iter < 3)
		{
			*iter = 1;
			break;
		}
	}

	struct Functor
	{
		bool operator()(const int& value)
		{
			if (value < compare)
				return true;
			return false;
		}
		int compare;
	};

	Functor functor;
	functor.compare = 3;
	iter = std::find_if(v.begin(), v.end(), functor);
	if (iter != v.end())
	{
		*iter = 1;
	}
	for (iter = v.begin(); iter != v.end(); iter++)
	{
		if (functor(*iter))
		{
			*iter = 1;
		}
	}

	// count
	// v에서 1인 원소의 개수를 세주세요.
	int count = std::count(v.begin(),v.end(), 1);

	// count_if
	// v에서 5보다 큰 원소의 개수를 세주세요.
	//functor.compare = 5;
	struct Count_F
	{
		bool operator()(const int& value)
		{
			return value > compare;
		}
		int compare;
	};
	Count_F functor1;
	functor1.compare = 5;
	count = std::count_if(v.begin(), v.end(), functor1);

	// all_of
	// 모든 원소가 다 5보다 큽니까?
	bool check = std::all_of(v.begin(), v.end(), functor1);

	// any_of
	// 하나라도 5보다 큰 애가 있습니까>
	check = std::any_of(v.begin(), v.end(), functor1);

	// for_each
	// 모든 원소에 5를 곱하는 작업을 하고 싶다.
	struct Each_F
	{
		void operator()(int& a)
		{
			a *= value;
		}

		int value;
	};

	Each_F each_fn;
	each_fn.value = 5;
	std::for_each(v.begin(), v.end() - 1, each_fn);

	// unique
	// v에서 중복된 원소를 지우고 싶다.
	v.push_back(5);
	v.push_back(5);
	v.push_back(5);
	vector<int>::iterator uIter = std::unique(v.begin(), v.end());

	for (iter = v.begin(); iter != uIter; iter++)
	{
		cout << *iter << endl;
	}

	// remove
	// 5를 지우고 싶다.
	v.erase(std::remove(v.begin(), v.end(), 5), v.end()); // 실제 지우기

	// remove_if
	// 13보다 큰 수들을 지우고 싶다.
	struct Remove_F
	{
		bool operator()(const int& element)
		{
			if (element > compareNum)
				return true;
			return false;
		}
		int compareNum;
	};
	Remove_F remove_FN;
	remove_FN.compareNum = 13;
	v.erase(std::remove_if(v.begin(), v.end(), remove_FN), v.end());

	return 0;
}