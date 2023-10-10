#include "CUW_Quickslots.h"
#include "Global.h"
#include "Engine/Texture2D.h"
#include "Components/HorizontalBox.h"
#include "Widgets/CUW_Button.h"

void UCUW_Quickslots::NativeConstruct()
{
	Super::NativeConstruct();

	UHorizontalBox* buttons = Cast<UHorizontalBox>(GetWidgetFromName("Buttons"));
	if (buttons)
	{
		TArray<UWidget*> Widgets = buttons->GetAllChildren();
		for (int32 i = 0; i < Widgets.Num(); i++)
		{
			UCUW_Button* button = Cast<UCUW_Button>(Widgets[i]);
			if (button)
			{
				Buttons.Add(button);
			}
		}
	}
}

void UCUW_Quickslots::SetTexture(int32 Index, UTexture2D* Texture)
{
	Buttons[Index]->SetTexture(Texture);
}