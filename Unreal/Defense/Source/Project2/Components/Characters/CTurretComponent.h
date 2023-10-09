#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTurretComponent.generated.h"

UENUM(BlueprintType)
enum class ETurretType : uint8
{
	Sword, GreatSword, Gun, Max,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCTurretComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetType(ETurretType InType) { Type = InType; }
	FORCEINLINE ETurretType GetType() { return Type; }

private:
	UPROPERTY(EditAnywhere)
		ETurretType Type;

public:
	UCTurretComponent();

protected:
	virtual void BeginPlay() override;
};