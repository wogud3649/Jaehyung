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
#include "Components/SizeBox.h"
#include "Widgets/CUW_StoreButton.h"

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

	Confirmation->SetVisibility(ESlateVisibility::Visible);
	TempItemData = InItemData;
}

void UCUW_Store::OnOKButtonClicked()
{
	Confirmation->SetVisibility(ESlateVisibility::Hidden);

	CheckTrue(TempItemData.ItemCode == -1);

	BuyItem(TempItemData);
}

void UCUW_Store::OnCancelButtonClicked()
{
	Confirmation->SetVisibility(ESlateVisibility::Hidden);

	CheckTrue(TempItemData.ItemCode == -1);

	TempItemData = FItemData();
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
	SetConfirmation();
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
			Buttons.Add(Cast<UCUW_StoreButton>(widget));
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

	for (UCUW_StoreButton* button : Buttons)
	{
		button->OnItemButtonClicked.AddDynamic(this, &UCUW_Store::OnItemButtonClicked);
	}
}

void UCUW_Store::SetConfirmation()
{
	Confirmation = Cast<USizeBox>(GetWidgetFromName("Confirmation"));
	if (Confirmation)
	{
		Confirmation->SetVisibility(ESlateVisibility::Hidden);
	}

	OKButton = Cast<UButton>(GetWidgetFromName("OKButton"));
	if (OKButton)
	{
		OKButton->OnClicked.AddDynamic(this, &UCUW_Store::OnOKButtonClicked);
	}

	CancelButton = Cast<UButton>(GetWidgetFromName("CancelButton"));
	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UCUW_Store::OnCancelButtonClicked);
	}
}

void UCUW_Store::BuyItem(const FItemData InItemData)
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(LinkedPlayer->GetPawn());
	CheckNull(inventory);

	inventory->RootItem(InItemData);
}