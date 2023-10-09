#include "CUW_Store.h"
#include "Global.h"
#include "Components/HorizontalBox.h"
#include "Widgets/CUW_Button.h"

void UCUW_Store::NativeConstruct()
{
	Super::NativeConstruct();

	UHorizontalBox* buttons = Cast<UHorizontalBox>(GetWidgetFromName("Buttons"));
	TArray<UWidget*> widgets = buttons->GetAllChildren();

	for (UWidget* widget : widgets)
	{
		UCUW_Button* button = Cast<UCUW_Button>(widget);

		if (button)
			Buttons.Add(button);
	}

	StoreDatas.SetNum((int32)ETurretType::Max);
	StoreTextures.SetNum((int32)ETurretType::Max);
	StorePrices.SetNum((int32)ETurretType::Max);

	CHelpers::GetAssetDynamic(&DataTable, "DataTable'/Game/Widgets/DataTables/DT_Store.DT_Store'");

	if (!DataTable)
	{
		CLog::Print("NoDataTable");
		return;
	}

	TArray<FStoreData*> datas;
	DataTable->GetAllRows<FStoreData>("", datas);

	if (datas.Num() == 0)
	{
		CLog::Print("NoTextureDatas : Inventory");
	}

	for (int32 i = 0; i < datas.Num(); i++)
	{
		StoreDatas[(int32)datas[i]->Type].Type = datas[i]->Type;
		StoreDatas[(int32)datas[i]->Type].Texture = datas[i]->Texture;
		StoreDatas[(int32)datas[i]->Type].Price = datas[i]->Price;

		StoreTextures[(int32)datas[i]->Type] = datas[i]->Texture;
		StorePrices[(int32)datas[i]->Type] = datas[i]->Price;
	}

	PostNativeConstruct();
}

void UCUW_Store::OnDisplay()
{
	bDisplay = true;

	SetVisibility(ESlateVisibility::Visible);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI());
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
}

void UCUW_Store::OffDisplay()
{
	bDisplay = false;

	SetVisibility(ESlateVisibility::Hidden);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void UCUW_Store::Pressed(FString InName)
{
	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i]->GetName() == InName)
		{
			if (OnStoreItem_Pressed.IsBound())
				OnStoreItem_Pressed.Broadcast(StoreDatas[i]);
		}
	}

	OffDisplay();
}