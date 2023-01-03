#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// MST
// Minimum Spanning Tree
// 최소 신장 트리

// 스패닝 트리
// - 모든 노드들이 연결되어 있어야 한다.
// - 모든 간선의 개수는 노드가 N개일 때 N-1개 이다.

// 최소 스패닝 트리
// - 스패닝 트리에서 각 간선의 가중치가 있을 때, 이 가중치 합이 최소가 되는 것을 MST라고 한다.
// - 사이클이 포함돼서는 안된다.

struct Edge
{
	int cost;
	int u; // 시작점
	int v; // 도착점
};

vector<vector<int>> adjacent;
vector<Edge> edges;

void CreateGraph()
{
	adjacent = vector<vector<int>>(7, vector<int>(7, -1));

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

class DisJointSet
{
public:
	DisJointSet(int n)
	: _parent(n, 0)
	, _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];
		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		if (_rank[uLeader] > _rank[vLeader])
		{
			std::swap(uLeader, vLeader);
		}
		_parent[uLeader] = vLeader;

		if (_rank[uLeader] == _rank[vLeader])
			_rank[vLeader]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

// 크루스칼 알고리즘
// -> 최소 스패닝 트리 찾기
// -> 탐욕법

// 탐욕법
// 각 부분마다 현재 최선의 선택을 찾아서 전체 답을 구하는 과정

void CreateEdgeInfo()
{
	for (int u = 0; u < adjacent.size(); u++)
	{
		for (int v = 0; v < adjacent[u].size(); v++)
		{
			if (u > v)
				continue;
			
			if (adjacent[u][v] == -1)
				continue;
			int cost = adjacent[u][v];

			Edge edge;
			edge.cost = cost;
			edge.u = u;
			edge.v = v;

			edges.push_back(edge);
		}
	}
}

vector<Edge> Kruskal(vector<Edge>& edges)
{
	vector<Edge> result;

	std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b)->bool
		{
			return a.cost < b.cost;
		});

	DisJointSet sets(adjacent.size());

	for (Edge& edge : edges)
	{
		// 시작노드랑 도착노드가 같은 그룹이다 하면 스킵
		if (sets.FindLeader(edge.u) == sets.FindLeader(edge.v))
			continue;

		// 시작노드랑 도착노드가 다른 그룹이면 Merge
		sets.Merge(edge.u, edge.v);
		result.push_back(edge);
	}
	return result;
};

int main()
{
	CreateGraph();
	CreateEdgeInfo();
	vector<Edge> mst = Kruskal(edges);

	int result = 0;
	for (auto& edge : mst)
	{
		result += edge.cost;
	}

	cout << result << endl;

	return 0;
}