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

	UFUNCTION()
		void OnButtonClicked(class UCUW_Button* InButton);

	FORCEINLINE const TArray<class UCUW_Button*> GetButtons() { return Buttons; }
	FORCEINLINE const int32 GetMoney() { return Money; }
	FORCEINLINE int32 GetIndex() { return Selected; }

public:
	virtual void NativeConstruct() override;

	bool RootItem(const FItemData InItemData);

	void SelectItem(int32 Index);

private:
	void OnRootItem(const FItemData InItemData, int32 Index);

	void SetMoney();
	void SubMoney(int32 InAmount);
	void SetButtons();
	void UpdateMoney();

	void OnSelected(int32 Index);
	void OffSelected(int32 Index);

private:
	TArray<class ACItem*> Items;

	TArray<class UCUW_Button*> Buttons;
	TArray<class UBorder*> Borders;
	class UTextBlock* MoneyText;
	int32 Money = 800;

	int32 Selected = 0;
	int32 OldSelected = 0;
};