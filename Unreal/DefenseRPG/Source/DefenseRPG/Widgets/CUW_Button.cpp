#include "CUW_Button.h"
#include "Global.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Components/Button.h"
#include "Components/Items/CItemComponent.h"
#include "Styling/SlateColor.h"

void UCUW_Button::OnClicked()
{
	if (OnItemButtonClicked.IsBound())
		OnItemButtonClicked.Broadcast(ItemData);

	if (OnButtonClicked.IsBound())
		OnButtonClicked.Broadcast(this);
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

	SetButton();
}

void UCUW_Button::SetItemData(FItemData InItemData)
{
	ItemData = InItemData;

	FButtonStyle ButtonStyle;

	ButtonStyle.Normal.SetResourceObject(ItemData.Texture);
	ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.5));
	ButtonStyle.Hovered.SetResourceObject(ItemData.Texture);
	ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.75));
	ButtonStyle.Pressed.SetResourceObject(ItemData.Texture);
	ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(1, 1, 1, 1));

	Button->SetStyle(ButtonStyle);
}

void UCUW_Button::InitItemData()
{
	ItemData = FItemData();

	FButtonStyle ButtonStyle;

	ButtonStyle.Normal.SetResourceObject(ItemData.Texture);
	ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.5));
	ButtonStyle.Hovered.SetResourceObject(ItemData.Texture);
	ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.75));
	ButtonStyle.Pressed.SetResourceObject(ItemData.Texture);
	ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(1, 1, 1, 1));

	Button->SetStyle(ButtonStyle);
}

void UCUW_Button::SetButton()
{
	Button = Cast<UButton>(GetWidgetFromName("Button"));
	CheckNull(Button);

	Button->OnClicked.AddDynamic(this, &UCUW_Button::OnClicked);
	Button->OnPressed.AddDynamic(this, &UCUW_Button::OnPressed);
	Button->OnReleased.AddDynamic(this, &UCUW_Button::OnReleased);
	Button->OnHovered.AddDynamic(this, &UCUW_Button::OnHovered);
	Button->OnUnhovered.AddDynamic(this, &UCUW_Button::OnUnhovered);
}