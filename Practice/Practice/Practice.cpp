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

vector<vector<int>> direction =
	{	{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1} };

void dfs(vector<vector<int>>& answer, int x, int y, int dir, int count, int n)
{
	if (count > n * n)
		return;

	answer[y][x] = count;

	int tempX = x + direction[dir][0];
	int tempY = y + direction[dir][1];
	if (tempX > n - 1 || tempY > n - 1 || tempX < 0 || tempY < 0 || answer[tempY][tempX] != 0)
	{
		dir++;
		dir %= 4;
	}

	dfs(answer, x + direction[dir][0], y + direction[dir][1], dir, ++count, n);
}

vector<vector<int>> solution(int n) {
	vector<vector<int>> answer = vector<vector<int>>(n, vector<int>(n, 0));

	int x = 0;
	int y = 0;
	int dir = 0;
	int count = 0;

	dfs(answer, x, y, dir, ++count, n);

	return answer;
}


int main()
{
	solution(6);

	return 0;
}