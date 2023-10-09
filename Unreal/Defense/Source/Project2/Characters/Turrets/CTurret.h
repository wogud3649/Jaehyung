#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/Characters/CTurretComponent.h"
#include "Interfaces/IInteract.h"
#include "Interfaces/IItem.h"
#include "CTurret.generated.h"

UCLASS()
class PROJECT2_API ACTurret : public ACCharacter, public IIInteract, public IIItem
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnInteract(AActor* InActor);

	UFUNCTION()
		void OffInteract(AActor* InActor);

	UFUNCTION()
		void OnRoot(AActor* InActor);

	UFUNCTION()
		void OffRoot(AActor* InActor);

	UFUNCTION()
		void OnAction(bool bLeft);

	UFUNCTION()
		void OffAction(bool bLeft);

	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Scaffolding;

	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* HealthWidget;

	UPROPERTY(VisibleDefaultsOnly)
		UCTurretComponent* Turret;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInteractComponent* Interact;

	UPROPERTY(VisibleDefaultsOnly)
		class UCItemComponent* Item;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

public:
	ACTurret();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor);
	virtual void EndInteract(AActor* InActor);

	virtual void BeginRoot(AActor* InActor) override;
	virtual void EndRoot(AActor* InActor) override;
	virtual void BeginAction(bool bLeft) override;
	virtual void EndAction(bool bLeft) override;

	void SetTurret(ETurretType InType);

	void BeginSelected();
	void EndSelected();

protected:
	virtual void InitBeginPlay() override;

	void EquipWeapon();

private:
	void Build();
};