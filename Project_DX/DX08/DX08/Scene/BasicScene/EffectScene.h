#pragma once
class EffectScene : public Scene
{
public:
	EffectScene();
	~EffectScene();

	virtual void Update() override;
	virtual void Render() override;

	virtual void PostRender() override;

private:
	shared_ptr<Effect> _effect;
	shared_ptr<Transform> _transform;
};

