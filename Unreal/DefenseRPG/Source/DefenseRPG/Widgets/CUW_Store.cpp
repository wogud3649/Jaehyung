#include "CUW_Store.h"
#include "Global.h"
#include "Engine/DataTable.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/Overlay.h"
#include "Components/Items/CItemComponent.h"
#include "Components/Items/CInventoryComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/CUW_Button.h"

void UCUW_Store::OnWindowPressed()
{
	FVector2D mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D storePos = UWidgetLayoutLibrary::SlotAsCanvasSlot(StoreOverlay)->GetPosition();
	MousePos = mousePos - storePos;

	bUpdateStop = false;

	UpdateLocation();
}

void UCUW_Store::OnWindowReleased()
{
	bUpdateStop = true;
}

void UCUW_Store::OnItemButtonClicked(const FItemData InItemData)
{
	CheckTrue(InItemData.ItemCode == -1);

	BuyItem(InItemData);
}

void UCUW_Store::UpdateLocation()
{
	CheckTrue(bUpdateStop);

	UKismetSystemLibrary::K2_SetTimer(this, "UpdateLocation", 0.01f, false);

	FVector2D mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D resultPos = mousePos - MousePos;

	// TODO : ¾î»öÇÔ
	if (resultPos.X > -1000 && resultPos.X < -280 && resultPos.Y < -180 && resultPos.Y > -540)
	{
		UWidgetLayoutLibrary::SlotAsCanvasSlot(StoreOverlay)->SetPosition(resultPos);
	}
}

void UCUW_Store::NativeConstruct()
{
	Super::NativeConstruct();

	SetButtons();
}

void UCUW_Store::SetButtons()
{
	StoreOverlay = Cast<UOverlay>(GetWidgetFromName("StoreOverlay"));

	Window = Cast<UButton>(GetWidgetFromName("Window"));
	if (Window)
	{
		Window->OnPressed.AddDynamic(this, &UCUW_Store::OnWindowPressed);
		Window->OnReleased.AddDynamic(this, &UCUW_Store::OnWindowReleased);
	}

	UGridPanel* gridpanel = Cast<UGridPanel>(GetWidgetFromName("Buttons"));
	if (gridpanel)
	{
		TArray<UWidget*> widgets = gridpanel->GetAllChildren();

		for (UWidget* widget : widgets)
		{
			Buttons.Add(Cast<UCUW_Button>(widget));
		}
	}

	UDataTable* dataTable;
	CHelpers::GetAssetDynamic<UDataTable>(&dataTable, "DataTable'/Game/Resources/DataTables/ItemDatas.ItemDatas'");

	if (dataTable)
	{
		TArray<FItemData*> itemDatas;
		dataTable->GetAllRows<FItemData>("", itemDatas);

		for (int i = 0, j = 0; i < itemDatas.Num(); i++)
		{
			if (itemDatas[i]->Name == "Default")
				continue;

			Buttons[j]->SetItemData(*itemDatas[i]);
			j++;
		}
	}

	for (UCUW_Button* button : Buttons)
	{
		button->OnItemButtonClicked.AddDynamic(this, &UCUW_Store::OnItemButtonClicked);
	}
}

void UCUW_Store::BuyItem(const FItemData InItemData)
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(LinkedPlayer->GetPawn());
	CheckNull(inventory);

	inventory->RootItem(InItemData);
}