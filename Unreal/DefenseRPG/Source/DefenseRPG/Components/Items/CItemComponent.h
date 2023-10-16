#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CItemComponent.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Default, Turret, Max,
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		int32 ItemCode = -1;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACItem> ItemClass;

	UPROPERTY(EditAnywhere)
		EItemType ItemType = EItemType::Default;

	UPROPERTY(EditAnywhere)
		class UTexture2D* Texture = NULL;

	UPROPERTY(EditAnywhere)
		FString Name = "";

	UPROPERTY(EditAnywhere)
		int32 Price = 0;

	UPROPERTY(EditAnywhere)
		bool bStackable = false;

	UPROPERTY(EditAnywhere)
		int32 MaxStackSize = 1;

	UPROPERTY(EditAnywhere)
		int32 StackSize = 1;

	UPROPERTY(EditAnywhere)
		FName SocketName = NAME_None;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENSERPG_API UCItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE const FItemData GetItemData() { return Data; }

public:
	UCItemComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetItemCode(const int32 ItemCode);

private:
	FItemData Data;
};