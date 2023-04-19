#pragma once
class FieldScene1 : public Scene
{
public:
	FieldScene1();
	virtual ~FieldScene1();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private:
	virtual void SceneClear();
	void CreateInteractObj();

	shared_ptr<Brick> _brick;
};

