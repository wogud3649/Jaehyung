#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/CItem.h"
#include "CWeapon.generated.h"

UCLASS()
class PROJECT2_API ACWeapon : public ACItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* Weapon;

public:
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginRoot(AActor* InActor) override {};
	virtual void EndRoot(AActor* InActor) override {};
	virtual void BeginAction(bool bLeft) override {};
	virtual void EndAction(bool bLeft) override {};
};