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

string solution(string my_string, int k) {
	string answer = "";

	for (int i = 0; i < k; i++)
	{
		answer += my_string;
	}

	return answer;
}

int main()
{
	solution("string", 6);

	return 0;
}