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
		BOSSSPAWN,
		BLOCKCOLLIDER,
		FLOORCOLLIDER,
		DOOR,
		CHEST
	};
	MapEditorTestScene();
	virtual ~MapEditorTestScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

	bool Save();
	bool Load();

	wstring GetFilePath() { return wstring(_curFilePath.begin(), _curFilePath.end()); }
private:
	void Functions();
	void Indicator();
	void ResetIndicator();
	void Draw(Vector2 pos);
	void Erase(Vector2 pos);
	void Drag(Vector2 pos);
	Vector2 GetTiledPos();

	shared_ptr<Brick> _brick;
	int _selectedIndex;

	shared_ptr<Sprite> _indicator;

	int _type = EditorType::DRAW;
	string _curType = "DRAW";

	Vector2 _startPos;
	Vector2 _endPos;

	vector<shared_ptr<Quad>> _monsterSpawn;
	shared_ptr<Quad> _playerSpawn;
	shared_ptr<Quad> _bossSpawn;

	string _history = "";
	string _curFilePath = "";
	bool _isHovered = false;
	bool _indicatorActive = true;

	shared_ptr<Quad> _doorSpawn;
	shared_ptr<Quad> _chestSpawn;
};

