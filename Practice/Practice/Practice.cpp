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

vector<bool> visited;
vector<string> result;

void DFS(int here, const vector<vector<string>>& tickets)
{
	visited[here] = true;
	string thereString = tickets[here][1];
	result.push_back(thereString);

	if (result.size() == tickets.size())
		return;

	if (std::all_of(visited.begin(), visited.end(), [](const bool& value)-> bool { return value == true; }))
		return;

	for (int i = 0; i < tickets.size(); i++)
	{
		if (visited[i] == true)
			continue;

		if (thereString == tickets[i][0])
		{
			DFS(i, tickets);
			return;
		}
	}
}

vector<string> solution(vector<vector<string>> tickets) {

	visited.resize(tickets.size(), false);

	std::sort(tickets.begin(), tickets.end());

	int startIndex = 0;

	for (int i = 0; i < tickets.size(); i++)
	{
		if (tickets[i][0] == "ICN")
		{
			startIndex = i;
			break;
		}
	}

	result.push_back("ICN");
	DFS(startIndex, tickets);

	return result;
}


int main()
{
	vector<vector<string>> temp;
	//[["ICN", "BOO"], ["ICN", "COO"], ["COO", "DOO"], ["DOO", "COO"], ["BOO", "DOO"], ["DOO", "BOO"], ["BOO", "ICN"], ["COO", "BOO"]]

	temp.push_back({ "BOO", "DOO" }); //
	temp.push_back({ "BOO", "ICN" }); //
	temp.push_back({ "COO", "BOO" }); //
	temp.push_back({ "COO", "DOO" }); //
	temp.push_back({ "DOO", "BOO" }); //
	temp.push_back({ "DOO", "COO" }); //
	temp.push_back({ "ICN", "BOO" }); //
	temp.push_back({ "ICN", "COO" }); //

	// 테스트 실패 케이스
	// ICN BOO DOO BOO ICN COO BOO(X) DOO COO (X)
	// ICN BOO DOO BOO ICN COO DOO COO BOO (O)

	solution(temp);

	return 0;
}