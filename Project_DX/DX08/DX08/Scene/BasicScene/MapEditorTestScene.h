#pragma once
class MapEditorTestScene : public Scene
{
public:
	enum EditorType
	{
		DRAW,
		ERASE,
		DRAG
	};
	MapEditorTestScene();
	virtual ~MapEditorTestScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private:
	void ActivatePlayer();
	void DeactivatePlayer();

	shared_ptr<Brick> _brick;
	int _selectedIndex;
	
	shared_ptr<Advanced_Player> _player;
	bool _playerActive = false;

	int _type = EditorType::DRAW;

	bool _isClicked = false;

};

