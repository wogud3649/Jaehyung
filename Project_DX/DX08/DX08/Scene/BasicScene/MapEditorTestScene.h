#pragma once
class MapEditorTestScene : public Scene
{
public:
	MapEditorTestScene();
	virtual ~MapEditorTestScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private:
	shared_ptr<Brick> _brick;
};

