#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class PROJECT2_API ACEnemy : public ACCharacter
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetWeapon(EWeaponType InWeaponType) { WeaponType = InWeaponType; EquipWeapon(); }

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		UWidgetComponent* HealthWidget;

	UPROPERTY(EditAnywhere)
		EWeaponType WeaponType;

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void InitBeginPlay() override;

	void EquipWeapon();
};