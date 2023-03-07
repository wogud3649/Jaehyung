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
	void ActivatePlayer();
	void DeactivatePlayer();

	shared_ptr<Brick> _brick;
	int _selectedIndex;

	vector<shared_ptr<RectCollider>> _blocks;
	vector<shared_ptr<RectCollider>> _floors;
	Vector2 _colPaddingSize;

	int _type = EditorType::DRAW;

	vector<Vector2> _monsterSpawnPos;

	Vector2 _startPos;
	Vector2 _endPos;
};

