#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Items/CItemComponent.h"
#include "CUW_Store.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_Store : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnWindowPressed();

	UFUNCTION()
		void OnWindowReleased();

	UFUNCTION()
		void OnItemButtonClicked(const FItemData InItemData);

	FORCEINLINE void SetLinkedPlayer(class APlayerController* PlayerController) { LinkedPlayer = PlayerController; }
	FORCEINLINE const APlayerController* GetLinkedPlayer() { return LinkedPlayer; }

private:
	UFUNCTION()
		void UpdateLocation();

public:
	virtual void NativeConstruct() override;

private:
	void SetButtons();
	void BuyItem(const FItemData InItemData);
	void UpdateStop();

private:
	class UOverlay* StoreOverlay;
	class UButton* Window;
	TArray<class UCUW_Button*> Buttons;
	APlayerController* LinkedPlayer;
	FVector2D MousePos;
	bool bUpdateStop;
};