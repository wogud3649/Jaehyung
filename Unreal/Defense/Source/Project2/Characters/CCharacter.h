#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/Characters/CStatusComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CCharacter.generated.h"

UCLASS()
class PROJECT2_API ACCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void StatusChanged(EStatusType InType);

public:
	FORCEINLINE uint8 GetTeamID() { return TeamId; }

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMovementComponent* Movement;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInventoryComponent* Inventory;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontageComponent* Montage;

	UPROPERTY(EditAnywhere)
		uint8 TeamId = 0;

public:
	ACCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

	void SetIgnoreActor(AActor* InActor, bool bIgnore = true);

	void Healed(float InAmount);
	void Damaged(float InAmount, ACharacter* InCauser = NULL);

	void EndBackstep();
	void EndRoll();
	void EndHitted();
	virtual void EndDead();
	void EndInteract();
	void EndActionL();

	void NextMontage();
	void InitMontage();

protected:
	virtual void InitBeginPlay();

	void SetDynamicMaterial();
	void SetMesh(FString InPath);
	void SetAnimInstance(FString InPath);
	void SetOrientRotation(bool bOrientRotation);

	void Avoid();

private:
	void InitStatus();
	void Backstep();
	void Roll();

	float GetDirection();

private:
	TArray<class UMaterialInstanceDynamic*> DynamicMaterials;

	class UCAnimInstance* AnimInstance;
};