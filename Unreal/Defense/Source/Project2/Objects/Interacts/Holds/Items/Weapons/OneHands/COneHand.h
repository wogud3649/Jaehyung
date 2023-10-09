#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/Weapons/CWeapon.h"
#include "COneHand.generated.h"

UCLASS()
class PROJECT2_API ACOneHand : public ACWeapon
{
	GENERATED_BODY()

public:
	ACOneHand();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginRoot(AActor* InActor) override {};
	virtual void EndRoot(AActor* InActor) override {};
	virtual void BeginAction(bool bLeft) override {};
	virtual void EndAction(bool bLeft) override {};
};