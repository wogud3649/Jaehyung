#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Items/CItemComponent.h"
#include "CUW_Inventory.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnItemButtonClicked(const FItemData InItemData);

	FORCEINLINE const TArray<class UCUW_Button*> GetButtons() { return Buttons; }
	FORCEINLINE const int32 GetMoney() { return Money; }

public:
	virtual void NativeConstruct() override;

	bool RootItem(const FItemData InItemData);

private:
	void SetMoney();
	void SubMoney(int32 InAmount);
	void SetButtons();
	void UpdateMoney();

private:
	TArray<class UCUW_Button*> Buttons;
	class UTextBlock* MoneyText;
	int32 Money = 10000;
};