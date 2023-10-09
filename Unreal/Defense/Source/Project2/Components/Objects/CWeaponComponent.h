#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed, Sword, GreatSword, Pistol, Max,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetType(EWeaponType InType) { ChangeType(InType); }
	FORCEINLINE EWeaponType GetType() { return Type; }

	FORCEINLINE void SetPower(float InPower) { Power = InPower; }
	FORCEINLINE float GetPower() { return Power; }

	FORCEINLINE void SetRange(float InRange) { Range = InRange; }
	FORCEINLINE float GetRange() { return Range; }

private:
	UPROPERTY(EditAnywhere)
		EWeaponType Type;

	UPROPERTY(EditAnywhere)
		float Power;

	UPROPERTY(EditAnywhere)
		float Range;

public:
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:
	void ActivateCollision();
	void DeactivateCollision();

private:
	void ChangeType(EWeaponType InType);
};