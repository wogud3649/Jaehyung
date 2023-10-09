#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/CUW_Name.h"
#include "Widgets/CUW_Health.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Idle, Backstep, Roll, Hitted, Dead, Interact, Dump, ActionL, ActionR, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatus, EStatusType, InType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FStatus OnStatusChanged;

private:
	UPROPERTY(EditDefaultsOnly)
		EStatusType Type;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

public:
	FORCEINLINE void SetType(EStatusType InType) { ChangeType(InType); }
	FORCEINLINE void SetIdle() { ChangeType(EStatusType::Idle); }
	FORCEINLINE EStatusType GetType() { return Type; }
	FORCEINLINE bool IsIdle() { return Type == EStatusType::Idle; }
	FORCEINLINE bool IsHitted() { return Type == EStatusType::Hitted; }
	FORCEINLINE bool IsDead() { return Type == EStatusType::Dead; }
	FORCEINLINE bool IsActionL() { return Type == EStatusType::ActionL; }

	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }

	FORCEINLINE void OnDisplay() { HealthBar->OnDisplay(); }
	FORCEINLINE void OffDisplay() { HealthBar->OffDisplay(); }
	FORCEINLINE bool IsDisplay() { return HealthBar->IsDisplay(); }

public:
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	void InitName(FString InName);
	void InitHealth();

	void AddHealth(float InAmount);
	void SubHealth(float InAmount, ACharacter* InCauser = NULL);

	void UpdateHealth();

private:
	void ChangeType(EStatusType InType);

private:
	UCUW_Name* Name;
	UCUW_Health* HealthBar;

	float Health;

	bool bDead;
};