#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/Weapons/Guns/CGun.h"
#include "CGun_Hitscan.generated.h"

UCLASS()
class PROJECT2_API ACGun_Hitscan : public ACGun
{
	GENERATED_BODY()

public:
	ACGun_Hitscan();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginRoot(AActor* InActor) override {};
	virtual void EndRoot(AActor* InActor) override {};
	virtual void BeginAction(bool bLeft) override {};
	virtual void EndAction(bool bLeft) override {};

	virtual bool Fire(FHitResult InHitResult) override;
	virtual bool Reload() override;
};