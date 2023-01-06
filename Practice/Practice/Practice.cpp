#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void service(int x, int& count)
{
	if (x / 10 == 0)
		return;
	int eaten = x / 10;
	count += eaten;
	x = x % 10 + eaten;

	service(x, count);
}

int main()
{
	int x = 1999;
	int count = 0;
	service(x, count);
	
	return 0;
}