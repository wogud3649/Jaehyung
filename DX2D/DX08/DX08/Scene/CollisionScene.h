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
	shared_ptr<RectCollider> _rect;
	shared_ptr<CircleCollider> _circle;
	shared_ptr<CircleCollider> _circle2;

};

