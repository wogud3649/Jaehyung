#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int solution(int a, int b, bool flag) {
	int answer = 0;

	if (flag)
		answer = a + b;
	else
		answer = a - b;

	return answer;
}

int main()
{
	solution(-4, 7, true);

	return 0;
}