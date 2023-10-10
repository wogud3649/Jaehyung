#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Button.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnClicked();

	UFUNCTION()
		void OnPressed();

	UFUNCTION()
		void OnReleased();

	UFUNCTION()
		void OnHovered();

	UFUNCTION()
		void OnUnhovered();

public:
	virtual void NativeConstruct() override;

	void SetTexture(class UTexture2D* Texture);

private:
	class UButton* Button;

	FButtonStyle ButtonStyle;
};