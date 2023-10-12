#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Items/CItemComponent.h"
#include "CUW_Button.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemButtonClicked, const FItemData, InItemData);

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

	FORCEINLINE const FItemData GetItemData() { return ItemData; }

public:
	UPROPERTY(BlueprintAssignable)
		FItemButtonClicked OnItemButtonClicked;

public:
	virtual void NativeConstruct() override;

	void SetItemData(FItemData InItemData);

private:
	void SetButton();

private:
	class UButton* Button;

	FItemData ItemData;
};