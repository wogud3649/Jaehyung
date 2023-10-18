#include "CInventoryComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Widgets/CUW_Inventory.h"
#include "Items/CItem.h"

UCInventoryComponent::UCInventoryComponent()
{
	CHelpers::GetClass<UCUW_Inventory>(&InventoryWidgetClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Inventory.BP_CUW_Inventory_C'");
}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryWidget = CreateWidget<UCUW_Inventory, APlayerController>(Cast<ACharacter>(GetOwner())->GetController<APlayerController>(), InventoryWidgetClass);
	InventoryWidget->AddToViewport();
}

bool UCInventoryComponent::RootItem(ACItem* InItem)
{
	bool result = InventoryWidget->RootItem(InItem);

	return result;
}

void UCInventoryComponent::DumpItem(int32 Index)
{
	InventoryWidget->DumpItem(Index);
}

void UCInventoryComponent::SelectItem(int32 Index)
{
	InventoryWidget->SelectItem(Index);
}

void UCInventoryComponent::PlayAction(bool bLeftClick)
{
	InventoryWidget->PlayAction(bLeftClick);
}