#include "CUW_Button.h"
#include "Global.h"
#include "Engine/Texture2D.h"
#include "Components/Button.h"
#include "Styling/SlateColor.h"

void UCUW_Button::OnClicked()
{
}

void UCUW_Button::OnPressed()
{
}

void UCUW_Button::OnReleased()
{
}

void UCUW_Button::OnHovered()
{
}

void UCUW_Button::OnUnhovered()
{
}

void UCUW_Button::NativeConstruct()
{
	Super::NativeConstruct();

	Button = Cast<UButton>(GetWidgetFromName("Button"));
	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UCUW_Button::OnClicked);
		Button->OnPressed.AddDynamic(this, &UCUW_Button::OnPressed);
		Button->OnReleased.AddDynamic(this, &UCUW_Button::OnReleased);
		Button->OnHovered.AddDynamic(this, &UCUW_Button::OnHovered);
		Button->OnUnhovered.AddDynamic(this, &UCUW_Button::OnUnhovered);
	}
}

void UCUW_Button::SetTexture(UTexture2D* Texture)
{
	ButtonStyle.Normal.SetResourceObject(Texture);
	ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.5));
	ButtonStyle.Hovered.SetResourceObject(Texture);
	ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.75));
	ButtonStyle.Pressed.SetResourceObject(Texture);
	ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(1, 1, 1, 1));

	Button->SetStyle(ButtonStyle);
}