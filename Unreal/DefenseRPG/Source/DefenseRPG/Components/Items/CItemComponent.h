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
		EItemType ItemType;

	UPROPERTY(EditAnywhere)
		class UTexture2D* Texture;

	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		int32 Price;

	UPROPERTY(EditAnywhere)
		bool bStackable;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENSERPG_API UCItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCItemComponent();

protected:
	virtual void BeginPlay() override;
};