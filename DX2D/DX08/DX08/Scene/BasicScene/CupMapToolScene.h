#pragma once
class CupMapToolScene : public Scene
{
public:
	CupMapToolScene();
	~CupMapToolScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save();
	void Load();

private:
	Vector2 _trackPos;
	shared_ptr<Quad> _track;
};

