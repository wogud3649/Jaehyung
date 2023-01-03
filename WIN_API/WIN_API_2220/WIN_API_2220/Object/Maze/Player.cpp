#include "framework.h"
#include "Player.h"

Player::Player(shared_ptr<Maze> maze)
: _maze(maze)
{
	_pos = _maze->GetStartPos();
	//RightHand();
	
	//vector<Vector2> tempPath;
	//tempPath.reserve(300);

	//DFS
	//_visited = vector<vector<bool>>(25, vector<bool>(25, false));
	//DFS(_pos, _maze->GetEndPos(), tempPath);

	//BFS
	_discovered = vector<vector<bool>>(_poolCountY, vector<bool>(_poolCountX, false));
	_parent = vector<vector<Vector2>>(_poolCountY, vector<Vector2>(_poolCountX, Vector2(-1,-1)));
	//BFS(_pos, _maze->GetEndPos(), tempPath);
	AStar(_pos, _maze->GetEndPos());

	//TrackParents(_maze->GetEndPos(), tempPath);
	//std::reverse(tempPath.begin(), tempPath.end());

	// backTracking
	//for (auto& pos : tempPath)
	//{
	//	_path.push_back(pos);
	//	if (pos == _maze->GetEndPos())
	//		break;
	//}
}

Player::~Player()
{
}

void Player::Init()
{
	_pos = _maze->GetStartPos();

	_discovered = vector<vector<bool>>(_poolCountY, vector<bool>(_poolCountX, false));
	_parent = vector<vector<Vector2>>(_poolCountY, vector<Vector2>(_poolCountX, Vector2(-1, -1)));
	AStar(_pos, _maze->GetEndPos());
}

void Player::Update()
{
	if (_pathIndex >= _path.size())
	{
		int randValue = rand() % 3;

		switch (randValue)
		{
		case 0:
		{
			_maze->CreateMaze_Kruskal();
			break;
		}
		case 1:
		{
			_maze->CreateMaze_Prim();
			break;
		}
		case 2:
		{
			_maze->CreateMaze();
			break;
		}
		}
		_pathIndex = 0;
		_path.clear();
		Init();
		return;
	}
	_time += 0.5f;
	if (_time > 1.0f)
	{
		_time = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex != 0)
		{
			Vector2 temp = _path[_pathIndex - 1];
			_maze->GetBlock(temp)->SetType(Block::Type::FOOTPRINT);
		}

		_pathIndex++;

		_maze->GetBlock(_pos)->SetType(Block::Type::PLAYER);
	}
}

void Player::RightHand()
{
	Vector2 pos = _pos; // 현재 위치
	_path.push_back(pos);
	Vector2 endPos = _maze->GetEndPos();
	_dir = Dir::DIR_UP;

	Vector2 frontPos[4] =
	{
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0}, // LEFT
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0} // RIGHT
	};

	while (pos != endPos)
	{
		// 현재 바라보는 방향 기준으로 오른쪽으로 갈 수 있는지 확인
		int newDir = ( _dir - 1 + DIR_COUNT ) % DIR_COUNT;
		Vector2 oldDirVector2 = frontPos[_dir]; // 기존 방향
		Vector2 newDirVector2 = frontPos[newDir]; // 새로운 방향

		if (CanGo(pos + newDirVector2))
		{
			_dir = static_cast<Dir>(newDir);
			pos += newDirVector2;
			_path.push_back(pos);
		}

		// 현재 바라보는 방향 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + oldDirVector2))
		{
			pos += oldDirVector2;
			_path.push_back(pos);
		}

		// 오른쪽, 앞이 다 막혀있다면 왼쪽으로 회전
		else
		{
			_dir = static_cast<Dir>((_dir + 1 + DIR_COUNT) % DIR_COUNT);
		}
	}

	// Stack
	stack<Vector2> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
			s.push(_path[i]);
	}

	s.push(_path.back());
	_path.clear();
	while(true)
	{
		if (s.empty() == true)
			break;
		_path.push_back(s.top());
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::DFS(Vector2 pos, Vector2 end, vector<Vector2>& tempPath)
{
	tempPath.push_back(pos);
	_maze->GetBlock(pos)->SetType(Block::Type::SEARCHPRINT);
	_visited[pos.y][pos.x] = true;
	if (pos == end)
		return;

	Vector2 frontPos[4] =
	{
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0}, // RIGHT
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0} // LEFT
	};

	for (int i = 0; i < 4; i++)
	{
		Vector2 there = pos + frontPos[i];
		if (CanGo(there) == false)
			continue;
		if (_visited[there.y][there.x] == true)
			continue;
		DFS(there, end, tempPath);
	}
}

void Player::BFS(Vector2 pos, Vector2 end, vector<Vector2>& tempPath)
{
	_maze->GetBlock(pos)->SetType(Block::Type::SEARCHPRINT);
	queue<Vector2> q;
	q.push(pos);
	_path.push_back(pos);
	_discovered[pos.y][pos.x] = true;
	_parent[pos.y][pos.x] = pos;

	Vector2 frontPos[4] =
	{
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0}, // RIGHT
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0} // LEFT
	};

	while (true)
	{
		if (q.empty() == true)
			break;

		Vector2 here = q.front();
		if (here == end)
			break;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			Vector2 there = here + frontPos[i];
			if (here == there)
				continue;
			if (CanGo(there) == false)
				continue;
			if (_discovered[there.y][there.x] == true)
				continue;
			q.push(there);
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here;
			_maze->GetBlock(there)->SetType(Block::Type::SEARCHPRINT);
		}
	}

	Vector2 pos2 = end;
	_path.push_back(pos2);
	while (true)
	{
		_path.push_back(_parent[pos2.y][pos2.x]);
		pos2 = _parent[pos2.y][pos2.x];

		if (pos2 == pos)
			break;
	}
	std::reverse(_path.begin(), _path.end());
}

void Player::Djikstra(Vector2 start, Vector2 end)
{
	Vector2 frontPos[8] =
	{
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0}, // RIGHT
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0}, // LEFT

		Vector2 {1, 1}, // RIGHT DOWN
		Vector2 {-1, 1}, // LEFT DOWN
		Vector2 {1, -1}, // RIGHT UP
		Vector2 {-1, -1} // LEFT UP
	};

	priority_queue<Vertex_Djikstra, vector<Vertex_Djikstra>, greater<Vertex_Djikstra>> pq;
	vector<vector<float>> best = vector<vector<float>>(_poolCountY, vector<float>(_poolCountX, 100000.0f));

	Vertex_Djikstra startV;
	startV.pos = start;
	startV.g = 0;
	pq.push(startV);
	best[start.y][start.x] = 0;
	_discovered[start.y][start.x] = true;
	_parent[start.y][start.x] = start;

	while (true)
	{
		if (pq.empty() == true)
			break;

		Vector2 here = pq.top().pos;
		float cost = pq.top().g;
		pq.pop();

		if (here == end)
			break;

		if (best[here.y][here.x] < cost)
			continue;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];
			if (here == there)
				continue;
			if (CanGo(there) == false)
				continue;


			float distance = (there - here).Length();

			float nextCost = distance + best[here.y][here.x];

			if (best[there.y][there.x] < nextCost)
				continue;

			_maze->GetBlock(there)->SetType(Block::Type::SEARCHPRINT);
			Vertex_Djikstra thereV;
			thereV.pos = there;
			thereV.g = nextCost;
			best[there.y][there.x] = nextCost;
			pq.push(thereV);
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here;
		}
	}

	Vector2 pos2 = end;
	_path.push_back(pos2);
	while (true)
	{
		_path.push_back(_parent[pos2.y][pos2.x]);
		pos2 = _parent[pos2.y][pos2.x];

		if (pos2 == start)
			break;
	}
	std::reverse(_path.begin(), _path.end());
}

void Player::AStar(Vector2 start, Vector2 end)
{
	Vector2 frontPos[8] =
	{
		Vector2 {0, 1}, // DOWN
		Vector2 {1, 0}, // RIGHT
		Vector2 {0, -1}, // UP
		Vector2 {-1, 0}, // LEFT

		Vector2 {1, 1}, // RIGHT DOWN
		Vector2 {-1, 1}, // LEFT DOWN
		Vector2 {1, -1}, // RIGHT UP
		Vector2 {-1, -1} // LEFT UP
	};

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	vector<vector<float>> best = vector<vector<float>>(_poolCountY, vector<float>(_poolCountX, 100000.0f));

	Vertex startV;
	startV.pos = start;
	startV.g = 0;
	startV.h = start.Manhattan(end);
	startV.f = startV.g + startV.h;
	pq.push(startV);
	best[start.y][start.x] = startV.f;
	_discovered[start.y][start.x] = true;
	_parent[start.y][start.x] = start;

	while (true)
	{
		if (pq.empty() == true)
			break;

		Vertex here = pq.top();
		float f = here.f;
		pq.pop();

		if (here.pos == end)
			break;

		if (best[here.pos.y][here.pos.x] < f)
			continue;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here.pos + frontPos[i];
			if (here.pos == there)
				continue;
			if (CanGo(there) == false)
				continue;

			float distance = (there - here.pos).Length();
			float nextG = distance + here.g;
			float nextH = there.Manhattan(end);
			float nextF = nextG + nextH;

			if (best[there.y][there.x] < nextF)
				continue;

			_maze->GetBlock(there)->SetType(Block::Type::SEARCHPRINT);
			Vertex thereV;
			thereV.pos = there;
			thereV.g = nextG;
			thereV.h = nextH;
			thereV.f = nextF;
			best[there.y][there.x] = nextF;
			pq.push(thereV);
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here.pos;
		}
	}

	Vector2 pos2 = end;
	_path.push_back(pos2);
	while (true)
	{
		_path.push_back(_parent[pos2.y][pos2.x]);
		pos2 = _parent[pos2.y][pos2.x];

		if (pos2 == start)
			break;
	}
	std::reverse(_path.begin(), _path.end());
	//Vector2 frontPos[8] =
	//{
	//	Vector2 {0, 1}, // DOWN
	//	Vector2 {1, 0}, // RIGHT
	//	Vector2 {0, -1}, // UP
	//	Vector2 {-1, 0}, // LEFT

	//	Vector2 {1, 1}, // RIGHT DOWN
	//	Vector2 {-1, 1}, // LEFT DOWN
	//	Vector2 {1, -1}, // RIGHT UP
	//	Vector2 {-1, -1} // LEFT UP
	//};

	//priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	//vector<vector<float>> best = vector<vector<float>>(25, vector<float>(25, 100000.0f));

	//Vertex startV;
	//startV.pos = start;
	//startV.f = 0;
	//startV.h = (end - startV.pos).Length();
	//startV.g = startV.f + startV.h;
	//pq.push(startV);
	//best[start.y][start.x] = startV.g;
	//_discovered[start.y][start.x] = true;
	//_parent[start.y][start.x] = start;

	//while (true)
	//{
	//	if (pq.empty() == true)
	//		break;

	//	Vector2 here = pq.top().pos;
	//	float costg = pq.top().g;
	//	float cost = pq.top().f;
	//	pq.pop();

	//	if (here == end)
	//		break;

	//	if (best[here.y][here.x] < costg)
	//		continue;

	//	for (int i = 0; i < 8; i++)
	//	{
	//		Vector2 there = here + frontPos[i];
	//		if (here == there)
	//			continue;
	//		if (CanGo(there) == false)
	//			continue;

	//		float distance = (there-here).Length();
	//		float dH = (end - there).Length();
	//		float nextCost = distance + cost + dH;

	//		if (best[there.y][there.x] < nextCost)
	//			continue;

	//		_maze->GetBlock(there)->SetType(Block::Type::SEARCHPRINT);
	//		Vertex thereV;
	//		thereV.pos = there;
	//		thereV.f = distance + cost;
	//		thereV.h = (end - there).Length();
	//		thereV.g = nextCost;
	//		best[there.y][there.x] = nextCost;
	//		pq.push(thereV);
	//		_discovered[there.y][there.x] = true;
	//		_parent[there.y][there.x] = here;
	//	}
	//}

	//Vector2 pos2 = end;
	//_path.push_back(pos2);
	//while (true)
	//{
	//	_path.push_back(_parent[pos2.y][pos2.x]);
	//	pos2 = _parent[pos2.y][pos2.x];

	//	if (pos2 == start)
	//		break;
	//}
	//std::reverse(_path.begin(), _path.end());
}

void Player::TrackParents(const Vector2& child, vector<Vector2>& tempPath)
{
	tempPath.push_back(child);
	if (_parent[child.y][child.x] == child)
		return;
	TrackParents(_parent[child.y][child.x], tempPath);
}

bool Player::CanGo(Vector2 pos)
{
	if (_maze->GetBlock(pos)->GetType() == Block::Type::DISABLE)
		return false;
	return true;
}
