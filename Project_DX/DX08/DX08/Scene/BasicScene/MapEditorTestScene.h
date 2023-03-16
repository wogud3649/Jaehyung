#pragma once
class MapEditorTestScene : public Scene
{
public:
	enum EditorType
	{
		DRAW,
		ERASE,
		DRAG,
		PLAYERSPAWN,
		MONSTERSPAWN,
		BLOCKCOLLIDER,
		FLOORCOLLIDER
	};
	MapEditorTestScene();
	virtual ~MapEditorTestScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

	void Save();
	void Load();

private:
	void Functions();
	void Draw(Vector2 pos);
	void Erase(Vector2 pos);
	void Drag(Vector2 pos);
	Vector2 GetTiledPos();

	shared_ptr<Brick> _brick;
	int _selectedIndex;

	int _type = EditorType::DRAW;

	Vector2 _startPos;
	Vector2 _endPos;

	shared_ptr<Quad> _playerSpawn;
	vector<shared_ptr<Quad>> _monsterSpawn;

	string _history = "";
};

