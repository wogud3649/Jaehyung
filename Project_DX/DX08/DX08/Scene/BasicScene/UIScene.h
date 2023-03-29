#pragma once
class UIScene : public Scene
{
public:
	UIScene();
	~UIScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Inventory> _inventory;
};