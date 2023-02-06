#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Collider> _circle1;
	shared_ptr<Collider> _rect1;
	shared_ptr<Collider> _rect2;
};

