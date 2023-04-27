#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<string> solution(string my_string)
{
	vector<string> answer;

	stringstream ss(my_string);
	ss.str(my_string);

	string temp;
	while (ss >> temp)
		answer.emplace_back(temp);

	return answer;
}

int main()
{
	solution("i love you");

	return 0;
}