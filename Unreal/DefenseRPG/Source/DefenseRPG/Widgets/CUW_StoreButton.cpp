#include "CUW_StoreButton.h"
#include "Global.h"
#include "Components/TextBlock.h"

void UCUW_StoreButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCUW_StoreButton::SetItemData(FItemData InItemData)
{
	Super::SetItemData(InItemData);

	UTextBlock* priceText = Cast<UTextBlock>(GetWidgetFromName("PriceText"));
	if (priceText)
	{
		FString text = FString::FromInt(InItemData.Price) + " $";
		priceText->SetText(FText::FromString(text));
	}
}