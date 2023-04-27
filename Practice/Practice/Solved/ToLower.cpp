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

string solution(string myString) {
	string answer = "";

	for (int i = 0; i < myString.size(); i++)
		myString[i] = tolower(myString[i]);

	for (int i = 0; i < myString.size(); i++)
	{
		if (myString[i] >= 'A' && myString[i] <= 'Z')
			myString[i] += 32;
	}

	return answer;
}

int main()
{
	solution("I Love you");

	return 0;
}