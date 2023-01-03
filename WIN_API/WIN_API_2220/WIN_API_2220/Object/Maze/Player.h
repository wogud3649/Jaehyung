#pragma once
class Player
{
public:
	struct Vertex_Djikstra
	{
		Vector2 pos;
		float g;

		bool operator<(const Vertex_Djikstra& other) const
		{
			return (g < other.g);
		}

		bool operator>(const Vertex_Djikstra& other) const
		{
			return (g > other.g);
		}
	};

	struct Vertex
	{
		Vector2 pos;
		float g;
		float h;
		float f;

		bool operator<(const Vertex& other) const
		{
			return f < other.f;
		}

		bool operator>(const Vertex& other) const
		{
			return f > other.f;
		}

	};

	Player(shared_ptr<Maze> maze);
	~Player();

	void Init();

	void Update();

	void RightHand();
	void DFS(Vector2 pos, Vector2 end, vector<Vector2>& tempPath);
	void BFS(Vector2 pos, Vector2 end, vector<Vector2>& tempPath);
	void Djikstra(Vector2 start, Vector2 end);
	void AStar(Vector2 start, Vector2 end);

	void TrackParents(const Vector2& child, vector<Vector2>& tempPath);

	bool CanGo(Vector2 pos);

private:
	Vector2 _pos = { 0, 0 };

	vector<Vector2> _path;
	int _pathIndex = 0;
	float _time = 0.0f;

	shared_ptr<Maze> _maze;
	Dir _dir = Dir::DIR_UP;

	// DFS
	vector<vector<bool>> _visited;

	// BFS
	vector<vector<bool>> _discovered;
	vector<vector<Vector2>> _parent;
};