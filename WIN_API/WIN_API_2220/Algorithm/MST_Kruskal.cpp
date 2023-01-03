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
// �ּ� ���� Ʈ��

// ���д� Ʈ��
// - ��� ������ ����Ǿ� �־�� �Ѵ�.
// - ��� ������ ������ ��尡 N���� �� N-1�� �̴�.

// �ּ� ���д� Ʈ��
// - ���д� Ʈ������ �� ������ ����ġ�� ���� ��, �� ����ġ ���� �ּҰ� �Ǵ� ���� MST��� �Ѵ�.
// - ����Ŭ�� ���Եż��� �ȵȴ�.

struct Edge
{
	int cost;
	int u; // ������
	int v; // ������
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

// ũ�罺Į �˰���
// -> �ּ� ���д� Ʈ�� ã��
// -> Ž���

// Ž���
// �� �κи��� ���� �ּ��� ������ ã�Ƽ� ��ü ���� ���ϴ� ����

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
		// ���۳��� ������尡 ���� �׷��̴� �ϸ� ��ŵ
		if (sets.FindLeader(edge.u) == sets.FindLeader(edge.v))
			continue;

		// ���۳��� ������尡 �ٸ� �׷��̸� Merge
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