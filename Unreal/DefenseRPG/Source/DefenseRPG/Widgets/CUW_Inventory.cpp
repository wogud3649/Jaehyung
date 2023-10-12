#include "CUW_Inventory.h"
#include "Global.h"
#include "Components/TextBlock.h"
#include "Widgets/CUW_Quickslots.h"
#include "Widgets/CUW_Button.h"

void UCUW_Inventory::OnItemButtonClicked(FItemData InItemData)
{
	CheckTrue(InItemData.ItemCode == -1);
}

void UCUW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	SetMoney();
	SetButtons();
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
			return true;
		}
	}
	else
	{
		for (UCUW_Button* button : Buttons)
		{
			FItemData buttonItemData = button->GetItemData();

			if (buttonItemData.ItemCode != -1)
				continue;

			button->SetItemData(InItemData);
			SubMoney(InItemData.Price);
			return true;
		}
	}

	return false;
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
	}
}

void UCUW_Inventory::UpdateMoney()
{
	CheckNull(MoneyText);

	FString moneyText = FString::FromInt(Money) + " $";
	MoneyText->SetText(FText::FromString(moneyText));
}