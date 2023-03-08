#pragma once
class InventoryScene : public Scene
{
public:
	InventoryScene();
	~InventoryScene();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	shared_ptr<Inventory> _inventory;
};