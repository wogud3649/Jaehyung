#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Items/CItemComponent.h"
#include "CUW_Button.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemButtonClicked, const FItemData, InItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonClicked, class UCUW_Button*, InButton);

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

	UPROPERTY(BlueprintAssignable)
		FButtonClicked OnButtonClicked;

public:
	virtual void NativeConstruct() override;

	virtual void SetItemData(FItemData InItemData);

protected:
	void SetButton();

protected:
	class UButton* Button;

	FItemData ItemData;
};