#pragma once
class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

	void SetScene(wstring filePath) { _filePath = filePath; }

private:
	void SceneClear();
	void CreateInteractObj();

	shared_ptr<Brick> _brick;

	wstring _filePath = L"";
};

