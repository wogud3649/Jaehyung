#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted, Avoid,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
		bool IsWait();

	UFUNCTION(BlueprintPure)
		bool IsApproach();

	UFUNCTION(BlueprintPure)
		bool IsAction();

	UFUNCTION(BlueprintPure)
		bool IsPatrol();

	UFUNCTION(BlueprintPure)
		bool IsHitted();

	UFUNCTION(BlueprintPure)
		bool IsAvoid();

	FORCEINLINE void SetWait() { ChangeType(EBehaviorType::Wait); }
	FORCEINLINE void SetApproach() { ChangeType(EBehaviorType::Approach); }
	FORCEINLINE void SetAction() { ChangeType(EBehaviorType::Action); }
	FORCEINLINE void SetPatrol() { ChangeType(EBehaviorType::Patrol); }
	FORCEINLINE void SetHitted() { ChangeType(EBehaviorType::Hitted); }
	FORCEINLINE void SetAvoid() { ChangeType(EBehaviorType::Avoid); }

	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public:
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChanged OnBehaviorTypeChanged;

private:
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "Behavior";

	UPROPERTY(EditAnywhere)
		FName TargetKey = "Target";

public:
	UCBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	class AActor* GetTarget();

private:
	void ChangeType(EBehaviorType InType);
	EBehaviorType GetType();

private:
	class UBlackboardComponent* Blackboard;
};