#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

string arr[4] = { "aya", "ye", "woo", "ma" };
vector<bool> visited = vector<bool>(4, false);
unordered_map<string, int> allBabbling;

void MakeString(int index, string word)
{
	// 기저
	if (word.size() >= 10)
		return;
	
	// 캐쉬
	
	// 구하기
	string makeWord = word + arr[index];
	visited[index] = true;
	allBabbling[makeWord]++;

	for (int nextIndex = 0; nextIndex < 4; nextIndex++)
	{
		if (visited[nextIndex] == true)
			continue;
		if (index == nextIndex)
			continue;
		MakeString(nextIndex, makeWord);
	}

	visited[index] = false;
}

int solution(vector<string> babbling)
{
	int answer = 0;

	for (int i = 0; i < 4; i++)
	{
		MakeString(i, "");
	}
	
	for (auto str : babbling)
	{
		if (allBabbling.count(str)!= 0)
			answer++;
	}
	return answer;
}

int main()
{
	vector<string> t = { "aya", "yee", "u", "maa", "wyeoo" };
	int answer = solution(t);
	

	return 0;
}