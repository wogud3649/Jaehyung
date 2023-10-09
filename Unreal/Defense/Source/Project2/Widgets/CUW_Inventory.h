#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "Components/Objects/CItemComponent.h"
#include "CUW_Inventory.generated.h"

USTRUCT(BlueprintType)
struct FInventoryData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EItemType Type;

	UPROPERTY(EditAnywhere)
		class UTexture2D* Texture;
};

UCLASS()
class PROJECT2_API UCUW_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateMoney(int32 InAmount);

	UFUNCTION(BlueprintImplementableEvent)
		void SetItem(int32 itemCode, int32 index);

	UFUNCTION(BlueprintImplementableEvent)
		void OnSelect(int32 index);

	UFUNCTION(BlueprintImplementableEvent)
		void OffSelect(int32 index);

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<UTexture2D*> InventoryTextures;

	UPROPERTY(BlueprintReadWrite)
		UDataTable* DataTable;

	UPROPERTY(BlueprintReadWrite)
		int32 Money;

protected:
	virtual void NativeConstruct() override;
};