#include "framework.h"
#include "InventoryScene.h"

InventoryScene::InventoryScene()
{
	_inventory = make_shared<Inventory>();
	_inventory->SetPannelPos(CENTER);
}

InventoryScene::~InventoryScene()
{
}

void InventoryScene::Update()
{
	_inventory->Update();

}

void InventoryScene::Render()
{
}

void InventoryScene::PostRender()
{
	_inventory->Render();
	_inventory->PostRender();

	if (ImGui::Button("BUY", { 100, 100 }))
	{
		_inventory->BuyItem("Sword");
	}
	if (ImGui::Button("SELL", { 100, 100 }))
	{
		_inventory->SellItem("Sword");
	}
}
