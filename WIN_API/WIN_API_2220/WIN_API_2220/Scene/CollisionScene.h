#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	virtual ~CollisionScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Collider> _circle1;
	shared_ptr<Collider> _circle2;

	shared_ptr<Collider> _rect1;
	shared_ptr<Collider> _rect2;
};

