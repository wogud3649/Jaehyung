#pragma once
class Maze
{
public:
	Maze();
	~Maze();

	struct Kruskal_Edge
	{
		int cost = 0;
		Vector2 u;
		Vector2 v;
	};

	struct Edge
	{
		int cost = 0;
		Vector2 v;

		bool operator<(const Edge& other) const
		{
			return cost < other.cost;
		}

		bool operator>(const Edge& other) const
		{
			return cost > other.cost;
		}
	};

	void Update();
	void Render(HDC hdc);

	void CreateMaze();
	void CreateMaze_Kruskal();
	void CreateMaze_Prim();

	Vector2 GetStartPos() { return { 1, 1 }; }
	Vector2 GetEndPos() { return Vector2{ (int)_poolCountX - 2, (int)_poolCountY - 2 }; }
	shared_ptr<Block> GetBlock(Vector2 pos) { return _blockMatrix[static_cast<UINT>(pos.y)][static_cast<UINT>(pos.x)]; }

private:

	vector<shared_ptr<Block>> _blocks;
	shared_ptr<Block> _blockMatrix[_poolCountY][_poolCountX] = { nullptr };
};

