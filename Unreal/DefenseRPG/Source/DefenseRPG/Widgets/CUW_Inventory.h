#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Items/CItemComponent.h"
#include "CUW_Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryItem);

UCLASS()
class DEFENSERPG_API UCUW_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnItemButtonClicked(const FItemData InItemData);

	UFUNCTION()
		void OnButtonClicked(class UCUW_Button* InButton);

	FORCEINLINE const TArray<UCUW_Button*> GetButtons() { return Buttons; }
	FORCEINLINE const int32 GetMoney() { return Money; }
	FORCEINLINE int32 GetIndex() { return Selected; }
	FORCEINLINE class ACItem* GetSelectedItem() { return Items[Selected]; }

public:
	virtual void NativeConstruct() override;

	bool RootItem(ACItem* InItem);
	void DumpItem(int32 Index);

	void SelectItem(int32 Index);

	void PlayAction(bool bLeftClick);

private:
	void OnRootItem(ACItem* InItem, int32 Index);

	void SetMoney();
	void SubMoney(int32 InAmount);
	void SetButtons();
	void UpdateMoney();
	void SetDefaultItemData();

	void OnSelected(int32 Index);
	void OffSelected(int32 Index);

private:
	TArray<ACItem*> Items;

	TArray<UCUW_Button*> Buttons;
	TArray<class UBorder*> Borders;
	class UTextBlock* MoneyText;

	int32 Money = 2000;

	int32 Selected = 0;
	int32 OldSelected = 0;

	FItemData DefaultItemData;
};