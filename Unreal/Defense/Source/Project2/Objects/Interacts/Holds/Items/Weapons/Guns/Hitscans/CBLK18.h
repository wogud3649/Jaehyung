#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/Weapons/Guns/Hitscans/CGun_Hitscan.h"
#include "CBLK18.generated.h"

UCLASS()
class PROJECT2_API ACBLK18 : public ACGun_Hitscan
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		USkeletalMeshComponent* Mesh;

public:
	ACBLK18();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginRoot(AActor* InActor) override;
	virtual void EndRoot(AActor* InActor) override;
	virtual void BeginAction(bool bLeft) override;
	virtual void EndAction(bool bLeft) override;
};