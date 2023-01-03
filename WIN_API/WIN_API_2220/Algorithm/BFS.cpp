#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// BFS : ���� �켱 Ž��
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

		// �湮
		int here = q.front();
		q.pop();
		cout << here << " �湮" << endl;

		for (int there = 0; there < adjacent.size(); there++)
		{
			if (discovered[there] == true)
				continue;
			if (here == there)
				continue;
			if (adjacent[here][there] == false)
				continue;

			// ����
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