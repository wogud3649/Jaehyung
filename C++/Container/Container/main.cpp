#include <iostream>
#include <vector>
#include <list>

#include "ListClass.h"
#include "VectorClass.h"

using namespace std;

int main()
{

	VectorClass<int> v;
	v.reserve(10);

	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	v.clear();

	// 진짜 삭제하는 법
	// vector<int>().swap(v);
	
	return 0;
}