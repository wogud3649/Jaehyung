#include "framework.h"
#include "Maze.h"

Maze::Maze()
{
	Vector2 offset = { 400, 150 };

	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			shared_ptr<Block> block = make_shared<Block>();
			block->SetType(Block::Type::DISABLE);
			Vector2 distance = { 17.0f * x, 17.0f * y};
			block->SetPosition(offset + distance);

			_blocks.push_back(block);
			_blockMatrix[y][x] = block;
		}
	}

	CreateMaze_Prim();
}

Maze::~Maze()
{
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			_blockMatrix[y][x] = nullptr;
		}
	}
}

void Maze::Update()
{
	for (auto& block : _blocks)
	{
		block->Update();
	}
}

void Maze::Render(HDC hdc)
{
	for (auto& block : _blocks)
	{
		block->Render(hdc);
	}

	// 텍스트 적기
	wstring maze = L"Maze!!!";
	TextOut(hdc, CENTER_X - 100, 100, maze.c_str(), maze.size());
}

void Maze::CreateMaze()
{
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blockMatrix[y][x]->SetType(Block::Type::DISABLE);
			}
			else
				_blockMatrix[y][x]->SetType(Block::Type::ABLE);
		}
	}

	// 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x == 1 && y == 1)
			{
				_blockMatrix[y][x]->SetType(Block::Type::START);
			}

			if (x % 2 == 0 || y % 2 == 0)
			{
				continue;
			}

			// 미로가 끝나는 지점이면 길 뚫기 중지
			if (x == _poolCountX - 2 && y == _poolCountY - 2)
			{
				_blockMatrix[y][x]->SetType(Block::Type::END);
				continue;
			}
			
			// 랜덤으로 우측 혹은 아래로만 뚫었을 때, 길이 안생기는 것 예외처리
			if (y == _poolCountY - 2)
			{
				_blockMatrix[y][x + 1]->SetType(Block::Type::ABLE);
				continue;
			}

			if (x == _poolCountX - 2)
			{
				_blockMatrix[y + 1][x]->SetType(Block::Type::ABLE);
				continue;
			}

			const int randValue = rand() % 2;
			if (randValue == 0)
				_blockMatrix[y][x + 1]->SetType(Block::Type::ABLE);
			else
				_blockMatrix[y+1][x]->SetType(Block::Type::ABLE);
		}
	}
}

void Maze::CreateMaze_Kruskal()
{
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blockMatrix[y][x]->SetType(Block::Type::DISABLE);
			}
			else
				_blockMatrix[y][x]->SetType(Block::Type::ABLE);
		}
	}

	vector<Kruskal_Edge> edges;

	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 모든 간선 후보들을 담아놓는 작업
			if (x < _poolCountX - 2)
			{
				const int randValue = rand() % 100;
				Kruskal_Edge edge;
				edge.cost = randValue;
				edge.u = Vector2(x, y);
				edge.v = Vector2(x + 2, y);

				edges.push_back(edge);
			}

			if (y < _poolCountY - 2)
			{
				const int randValue = rand() % 100;
				Kruskal_Edge edge;
				edge.cost = randValue;
				edge.u = Vector2(x, y);
				edge.v = Vector2(x, y+2);

				edges.push_back(edge);
			}
		}
	}

	std::sort(edges.begin(), edges.end(), [](const Kruskal_Edge& a, const Kruskal_Edge& b)->bool
	{
		return a.cost < b.cost;
	});

	DisJointSet sets(_poolCountX * _poolCountY);

	for (auto& edge : edges)
	{
		int u = edge.u.x + edge.u.y * _poolCountY;
		int v = edge.v.x + edge.v.y * _poolCountY;

		if (sets.FindLeader(u) == sets.FindLeader(v))
			continue;

		sets.Merge(u, v);

		// 연결된 노드로 바꿔주는 위치 찾기
		int x = (edge.u.x + edge.v.x) / 2;
		int y = (edge.u.y + edge.v.y) / 2;

		_blockMatrix[y][x]->SetType(Block::Type::ABLE);
	}
}

void Maze::CreateMaze_Prim()
{
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blockMatrix[y][x]->SetType(Block::Type::DISABLE);
			}
			else
				_blockMatrix[y][x]->SetType(Block::Type::ABLE);
		}
	}

	// Vector2 u -> 시작점
	// edges[u] : u 라는 정점과 연결된 간선 목록

	map<Vector2, vector<Edge>> edges;

	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 모든 간선 후보들을 담아놓는 작업
			// 우측
			if (x < _poolCountX - 2)
			{
				const int randValue = rand() % 100;
				Vector2 u = Vector2{ x, y };
				Vector2 v = Vector2{ x + 2, y };
				edges[u].push_back({ randValue, v });
				edges[v].push_back({ randValue, u });
			}

			if (y < _poolCountY - 2)
			{
				const int randValue = rand() % 100;
				Vector2 u = Vector2{ x, y };
				Vector2 v = Vector2{ x, y + 2 };
				edges[u].push_back({ randValue, v });
				edges[v].push_back({ randValue, u });
			}
		}
	}

	// 해당 정점이 집합에 포함되어있나?
	map<Vector2, bool> added; // ->added[{1,1}] = true;
	// 어떤 정점이 누구에 의해 연결되어 있는지?
	map<Vector2, Vector2> parent;
	// 만들고 있는 집합에 인접한 간선 중, 해당 정점에 닿는 최소 간선의 정보
	map<Vector2, int> best;

	// added, best 초기화
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			best[Vector2{ x,y }] = INT_MAX;
			added[Vector2{ x,y }] = false;
		}
	}

	priority_queue<Edge> pq;
	Vector2 startPos = { 1, 1 };
	pq.push(Edge({ 0, startPos }));
	best[startPos] = 0;
	parent[startPos] = startPos;
	while (true)
	{
		if (pq.empty())
			break;

		Edge bestEdge = pq.top();
		pq.pop();

		// 새로 연결된 정점
		Vector2 vertex = bestEdge.v;

		// 이미 추가되어있으면 스킾
		if (added[vertex])
			continue;

		added[vertex] = true;

		// 맵에 적용
		{
			int x = (parent[vertex].x + vertex.x) / 2;
			int y = (parent[vertex].y + vertex.y) / 2;

			_blockMatrix[y][x]->SetType(Block::Type::ABLE);
		}

		for (Edge& edge : edges[vertex])
		{
			if (added[edge.v])
				continue;

			// 다른 경로로 더 좋은 후보가 발견이 되어있었으면 스킵
			if (edge.cost > best[edge.v])
				continue;

			best[edge.v] = edge.cost;
			parent[edge.v] = vertex;
			pq.push(edge);
		}
	}
}
