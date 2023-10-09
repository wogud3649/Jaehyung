#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/Weapons/CWeapon.h"
#include "CGun.generated.h"

UCLASS()
class PROJECT2_API ACGun : public ACWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCGunComponent* Gun;

	UPROPERTY(VisibleDefaultsOnly)
		class UCTraceComponent* Trace;

	UPROPERTY(VisibleDefaultsOnly)
		class UCZoomComponent* Zoom;

public:
	ACGun();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginRoot(AActor* InActor) override {};
	virtual void EndRoot(AActor* InActor) override {};
	virtual void BeginAction(bool bLeft) override {};
	virtual void EndAction(bool bLeft) override {};

	virtual bool Fire(FHitResult InHitResult) { return true; };
	virtual bool Reload() { return true; };
};