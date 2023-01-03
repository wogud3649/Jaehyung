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

	// �ؽ�Ʈ ����
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

	// �������� ���� Ȥ�� �Ʒ��� ���� �մ� �۾�
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

			// �̷ΰ� ������ �����̸� �� �ձ� ����
			if (x == _poolCountX - 2 && y == _poolCountY - 2)
			{
				_blockMatrix[y][x]->SetType(Block::Type::END);
				continue;
			}
			
			// �������� ���� Ȥ�� �Ʒ��θ� �վ��� ��, ���� �Ȼ���� �� ����ó��
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

			// ��� ���� �ĺ����� ��Ƴ��� �۾�
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

		// ����� ���� �ٲ��ִ� ��ġ ã��
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

	// Vector2 u -> ������
	// edges[u] : u ��� ������ ����� ���� ���

	map<Vector2, vector<Edge>> edges;

	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// ��� ���� �ĺ����� ��Ƴ��� �۾�
			// ����
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

	// �ش� ������ ���տ� ���ԵǾ��ֳ�?
	map<Vector2, bool> added; // ->added[{1,1}] = true;
	// � ������ ������ ���� ����Ǿ� �ִ���?
	map<Vector2, Vector2> parent;
	// ����� �ִ� ���տ� ������ ���� ��, �ش� ������ ��� �ּ� ������ ����
	map<Vector2, int> best;

	// added, best �ʱ�ȭ
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

		// ���� ����� ����
		Vector2 vertex = bestEdge.v;

		// �̹� �߰��Ǿ������� ���h
		if (added[vertex])
			continue;

		added[vertex] = true;

		// �ʿ� ����
		{
			int x = (parent[vertex].x + vertex.x) / 2;
			int y = (parent[vertex].y + vertex.y) / 2;

			_blockMatrix[y][x]->SetType(Block::Type::ABLE);
		}

		for (Edge& edge : edges[vertex])
		{
			if (added[edge.v])
				continue;

			// �ٸ� ��η� �� ���� �ĺ��� �߰��� �Ǿ��־����� ��ŵ
			if (edge.cost > best[edge.v])
				continue;

			best[edge.v] = edge.cost;
			parent[edge.v] = vertex;
			pq.push(edge);
		}
	}
}
