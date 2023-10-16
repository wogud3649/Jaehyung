#include "CUW_Inventory.h"
#include "Global.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Items/CItem.h"
#include "Widgets/CUW_Quickslots.h"
#include "Widgets/CUW_Button.h"

void UCUW_Inventory::OnItemButtonClicked(FItemData InItemData)
{
	CheckTrue(InItemData.ItemCode == -1);
}

void UCUW_Inventory::OnButtonClicked(UCUW_Button* InButton)
{
	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i] == InButton)
		{
			SelectItem(i);
			break;
		}
	}
}

void UCUW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	SetMoney();
	SetButtons();
	Items.SetNum(Buttons.Num());
	OnSelected(Selected);
}

bool UCUW_Inventory::RootItem(const FItemData InItemData)
{
	if (Money < InItemData.Price)
		return false;

	int32 quickIndex = -1;

	if (InItemData.bStackable)
	{
		for (int i = 0; i < Buttons.Num(); i++)
		{
			FItemData buttonItemData = Buttons[i]->GetItemData();

			if (buttonItemData.ItemCode == InItemData.ItemCode)
			{
				if (buttonItemData.StackSize < buttonItemData.MaxStackSize)
				{
					buttonItemData.StackSize++;
					Buttons[i]->SetItemData(buttonItemData);
					SubMoney(InItemData.Price);

					OnRootItem(InItemData, i);

					return true;
				}
			}
			else if (buttonItemData.ItemCode == -1)
			{
				if (quickIndex == -1)
					quickIndex = i;
			}
		}

		if (quickIndex != -1)
		{
			Buttons[quickIndex]->SetItemData(InItemData);
			SubMoney(InItemData.Price);

			OnRootItem(InItemData, quickIndex);

			return true;
		}
	}
	else
	{
		for (int32 i = 0; i < Buttons.Num(); i++)
		{
			FItemData buttonItemData = Buttons[i]->GetItemData();

			if (buttonItemData.ItemCode != -1)
				continue;

			Buttons[i]->SetItemData(InItemData);
			SubMoney(InItemData.Price);

			OnRootItem(InItemData, i);

			return true;
		}
	}

	return false;
}

void UCUW_Inventory::SelectItem(int32 Index)
{
	CheckTrue(Index == OldSelected);

	Selected = Index;

	OnSelected(Selected);
	OffSelected(OldSelected);

	OldSelected = Selected;
}

void UCUW_Inventory::OnRootItem(const FItemData InItemData, int32 Index)
{
	ACItem* item = Cast<ACItem>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), InItemData.ItemClass, FTransform(), ESpawnActorCollisionHandlingMethod::AlwaysSpawn, GetOwningPlayerPawn()));
	if (item)
	{
		UGameplayStatics::FinishSpawningActor(item, FTransform());

		Items[Index] = item;
		item->Rooted();
		if (Selected != Index)
			item->OffSelected();

		USkeletalMeshComponent* skeletal = CHelpers::GetComponent<USkeletalMeshComponent>(GetOwningPlayerPawn());
		if (skeletal)
		{
			if (InItemData.SocketName != NAME_None)
			{
				item->AttachToComponent(skeletal, FAttachmentTransformRules::KeepRelativeTransform, InItemData.SocketName);
			}
		}
	}
}

void UCUW_Inventory::SetMoney()
{
	MoneyText = Cast<UTextBlock>(GetWidgetFromName("MoneyText"));

	UpdateMoney();
}

void UCUW_Inventory::SubMoney(int32 InAmount)
{
	CheckTrue(Money < InAmount);

	Money -= InAmount;

	UpdateMoney();
}

void UCUW_Inventory::SetButtons()
{
	UCUW_Quickslots* quickslots = Cast<UCUW_Quickslots>(GetWidgetFromName("Quickslots"));
	if (quickslots)
	{
		TArray<UCUW_Button*> buttons = quickslots->GetButtons();

		for (UCUW_Button* button : buttons)
		{
			Buttons.Add(button);
		}
	}

	for (UCUW_Button* button : Buttons)
	{
		button->OnItemButtonClicked.AddDynamic(this, &UCUW_Inventory::OnItemButtonClicked);
		button->OnButtonClicked.AddDynamic(this, &UCUW_Inventory::OnButtonClicked);
		Borders.Add(Cast<UBorder>(button->GetWidgetFromName("Border")));
	}
}

void UCUW_Inventory::UpdateMoney()
{
	CheckNull(MoneyText);

	FString moneyText = FString::FromInt(Money) + " $";
	MoneyText->SetText(FText::FromString(moneyText));
}

void UCUW_Inventory::OnSelected(int32 Index)
{
	Borders[Index]->SetBrushColor(FLinearColor::Red);

	if (Items[Index])
		Items[Index]->OnSelected();
}

void UCUW_Inventory::OffSelected(int32 Index)
{
	Borders[Index]->SetBrushColor(FLinearColor::White);

	if (Items[Index])
		Items[Index]->OffSelected();
}