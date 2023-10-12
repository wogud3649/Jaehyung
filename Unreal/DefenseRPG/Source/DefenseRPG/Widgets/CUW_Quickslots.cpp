#include "CUW_Quickslots.h"
#include "Global.h"
#include "Engine/Texture2D.h"
#include "Components/HorizontalBox.h"
#include "Widgets/CUW_Button.h"

void UCUW_Quickslots::NativeConstruct()
{
	Super::NativeConstruct();

	SetButtons();
}

void UCUW_Quickslots::SetItemData(int32 Index, const FItemData InItemData)
{
	Buttons[Index]->SetItemData(InItemData);
}

void UCUW_Quickslots::SetButtons()
{
	UHorizontalBox* buttons = Cast<UHorizontalBox>(GetWidgetFromName("Buttons"));
	CheckNull(buttons);

	TArray<UWidget*> widgets = buttons->GetAllChildren();
	for (UWidget* widget : widgets)
	{
		UCUW_Button* button = Cast<UCUW_Button>(widget);
		if (button)
		{
			Buttons.Add(button);
		}
	}
}