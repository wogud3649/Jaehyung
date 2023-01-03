#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// BFS : 넓이 우선 탐색
// Breadth First Search

vector<vector<bool>> adjacent;
vector<bool> discovered;
vector<int> parent;

void CreateGraph()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));
	discovered = vector<bool>(7, false);
	parent = vector<int>(7, -1);

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

void BFS(int start)
{
	queue<int> q;
	q.push(start);
	discovered[start] = true;
	parent[start] = start;

	while (true)
	{
		if (q.empty() == true)
			break;

		// 방문
		int here = q.front();
		q.pop();
		cout << here << " 방문" << endl;

		for (int there = 0; there < adjacent.size(); there++)
		{
			if (discovered[there] == true)
				continue;
			if (here == there)
				continue;
			if (adjacent[here][there] == false)
				continue;

			// 예약
			q.push(there);
			discovered[there] = true;
			parent[there] = here;
		}
	}
}

int main()
{
	CreateGraph();
	BFS(0);

	return 0;
}