#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Components/Characters/CStatusComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "CMontageComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove;
};

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EWeaponType WeaponType;

	UPROPERTY(EditAnywhere)
		EStatusType StatusType;

	UPROPERTY(EditAnywhere)
		TArray<FMontage> AnimMontages;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void PlayAnimMontage(EWeaponType InWeapon, EStatusType InStatus);

public:
	FORCEINLINE bool IsEnableNext() { return bEnableNext; }

	FORCEINLINE void NextSelected() { Selected++; }
	FORCEINLINE void InitSelected() { Selected = 0; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

	UPROPERTY(EditAnywhere)
		bool bDebug = false;

public:
	UCMontageComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetDataTable(FString InPath);

	void EnableNext();
	void DisableNext();

private:
	void PlayCommonMontage(EStatusType InStatus);
	void Failed();

private:
	FMontageData* Datas[(int32)EWeaponType::Max][(int32)EStatusType::Max];
	int32 Selected = 0;
	bool bEnableNext;
};