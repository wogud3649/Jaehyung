#pragma once
class ProjectionScene : public Scene
{
public:
	ProjectionScene();
	virtual ~ProjectionScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<Line> _line1;
	shared_ptr<Line> _line2;
	shared_ptr<Line> _projection;

	Vector2 _line1Dir;
	Vector2 _line2Dir;
};

