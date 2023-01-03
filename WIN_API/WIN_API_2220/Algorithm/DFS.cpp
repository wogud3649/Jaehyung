#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// DFS
// Deep First Search (±íÀÌ ¿ì¼± Å½»ö)

vector<vector<bool>> adjacent;
vector<bool> visited;

void CreateGraph()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));
	visited = vector<bool>(7, false);

	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][4] = true;

	adjacent[1][0] = true;
	adjacent[1][6] = true;

	adjacent[2][0] = true;
	adjacent[2][3] = true;
	adjacent[2][5] = true;

	adjacent[3][2] = true;

	adjacent[4][0] = true;

	adjacent[5][2] = true;

	adjacent[6][1] = true;
}

void DFS(int here)
{
	visited[here] = true;
	cout << here << "¹æ¹®!!" << endl;

	for (int there = 0; there < 7; there++)
	{
		if (here == there)
			continue;
		if (visited[there] == true)
			continue;
		if (adjacent[here][there] == false)
			continue;

		DFS(there);
	}
}

void DFS_ALL()
{
	for (int i = 0; i < 7; i++)
	{
		visited = vector<bool>(7, false);
		DFS(i);
		cout << endl;
	}
}

int main()
{
	CreateGraph();
	DFS_ALL();

	return 0;
}