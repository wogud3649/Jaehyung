#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Run, Sprint, Max,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetRun() { ChangeType(EMovementType::Run); }
	FORCEINLINE void SetSprint() { ChangeType(EMovementType::Sprint); }

	FORCEINLINE void SetMove() { bCanMove = true; }
	FORCEINLINE void SetStop() { bCanMove = false; }

	FORCEINLINE bool GetCanMove() { return bCanMove; }

private:
	UPROPERTY(EditAnywhere)
		EMovementType Type;

	UPROPERTY(EditAnywhere)
		float RunSpeed = 400.0f;

	UPROPERTY(EditAnywhere)
		float SprintSpeed = 600.0f;

	UPROPERTY(EditAnywhere)
		int32 JumpMaxCount = 3;

public:
	UCMovementComponent();

protected:
	virtual void BeginPlay() override;

private:
	void ChangeType(EMovementType InType);
	void UpdateSpeed();

private:
	float* Speed[(int32)EMovementType::Max] = { &RunSpeed, &SprintSpeed};

	bool bCanMove = true;
	float JumpZVelocity = 600.0f;
};