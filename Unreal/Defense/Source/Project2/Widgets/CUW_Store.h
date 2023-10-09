#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "Components/Characters/CTurretComponent.h"
#include "CUW_Store.generated.h"

USTRUCT(BlueprintType)
struct FStoreData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		ETurretType Type;

	UPROPERTY(EditAnywhere)
		class UTexture2D* Texture;

	UPROPERTY(EditAnywhere)
		int32 Price;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoreItem_Pressed, FStoreData, InData);

UCLASS()
class PROJECT2_API UCUW_Store : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void PostNativeConstruct();

	FORCEINLINE TArray<class UCUW_Button*> GetButtons() { return Buttons; }
	FORCEINLINE bool IsDisplay() { return bDisplay; }

public:
	UPROPERTY(BlueprintAssignable)
		FStoreItem_Pressed OnStoreItem_Pressed;

	UPROPERTY(BlueprintReadWrite)
		TArray<UTexture2D*> StoreTextures;

	UPROPERTY(BlueprintReadWrite)
		TArray<int32> StorePrices;

	UPROPERTY(BlueprintReadWrite)
		UDataTable* DataTable;

public:
	virtual void NativeConstruct() override;

	void OnDisplay();
	void OffDisplay();

	void Pressed(FString InName);

private:
	TArray<FStoreData> StoreDatas;
	TArray<class UCUW_Button*> Buttons;
	bool bDisplay;
};