#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

struct Vertex
{
	Vertex(int num, int g)
	: vertexNum(num)
	, g(g)
	{
	}

	bool operator<(const Vertex& other) const
	{
		if (g < other.g)
			return true;
		return false;
	}

	bool operator>(const Vertex& other) const
	{
		if (g > other.g)
			return true;
		return false;
	}

	int vertexNum = 0;
	int g = 0;
};

vector<vector<int>> adjacent;
vector<bool> discovered;
vector<int> parent;

void CreateGraph()
{
	adjacent = vector<vector<int>>(7, vector<int>(7, -1));
	discovered = vector<bool>(7, false);
	parent = vector<int>(7, -1);

	adjacent[0][1] = 10;
	adjacent[0][2] = 5;
	adjacent[0][4] = 15;

	adjacent[1][0] = 10;
	adjacent[1][2] = 3;
	adjacent[1][6] = 7;

	adjacent[2][0] = 5;
	adjacent[2][1] = 3;
	adjacent[2][3] = 2;
	adjacent[2][5] = 4;

	adjacent[3][2] = 2;

	adjacent[4][0] = 15;

	adjacent[5][2] = 4;

	adjacent[6][1] = 7;
}

void Djikstra(int start)
{
	vector<int> best(adjacent.size(), INT_MAX);
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	Vertex startV = Vertex(start, 0);
	pq.push(startV);
	best[start] = 0;

	discovered[start] = true;
	parent[start] = start;

	while (true)
	{
		if (pq.empty())
			break;

		int cost = pq.top().g;
		int here = pq.top().vertexNum;
		pq.pop();

		// 먼저 찾은게 현재 찾은 vertex의 가중치보다 작다.
		if (best[here] < cost)
		{
			cout << here << endl;
			cout << cost << endl;
			cout << best[here] << endl;
			continue;
		}

		for (int there = 0; there < adjacent.size(); there++)
		{
			if (here == there)
				continue;
			if (adjacent[here][there] == -1)
				continue;

			// 뒤늦게 찾은 vertex의 가중치가 기존에 찾은 vertex의 가중치보다 더 크면 다음꺼 확인
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there])
				continue;
			Vertex v = Vertex(there, nextCost);
			pq.push(v);
			best[there] = nextCost;
			discovered[there] = true;
			parent[there] = here;
		}
	}

	for (int i = 0; i < adjacent.size(); i++)
	{
		cout << i << "정점의 부모" << parent[i] << endl;
		cout << i << "의 0으로부터의 최단 거리 : " << best[i] << endl;
	}
}

int main()
{
	CreateGraph();
	Djikstra(0);

	return 0;
}