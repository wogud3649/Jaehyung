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

bool UCInventoryComponent::RootItem(const FItemData InItemData)
{
	bool result = InventoryWidget->RootItem(InItemData);

	return result;
}

void UCInventoryComponent::SelectItem(int32 Index)
{
	InventoryWidget->SelectItem(Index);
}