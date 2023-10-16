#include "CUW_Name.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "Components/TextBlock.h"

void UCUW_Name::NativeConstruct()
{
	Super::NativeConstruct();

	Text = Cast<UTextBlock>(GetWidgetFromName("NameText"));
	if (Text)
		Text->SetText(FText::FromString(Name));
}

void UCUW_Name::SetNameText(const FString& InName)
{
	Name = InName;
}