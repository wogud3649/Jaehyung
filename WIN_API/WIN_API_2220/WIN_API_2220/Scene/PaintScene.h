#pragma once
class PaintScene : public Scene
{
public:
	PaintScene();
	virtual ~PaintScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<CircleCollider> _circle;
	shared_ptr<RectCollider> _rect;
};

