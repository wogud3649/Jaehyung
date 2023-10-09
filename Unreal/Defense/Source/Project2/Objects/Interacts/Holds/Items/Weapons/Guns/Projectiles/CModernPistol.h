#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/Weapons/Guns/Projectiles/CGun_Projectile.h"
#include "CModernPistol.generated.h"

UCLASS()
class PROJECT2_API ACModernPistol : public ACGun_Projectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		USkeletalMeshComponent* Mesh;

public:
	ACModernPistol();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginRoot(AActor* InActor) override;
	virtual void EndRoot(AActor* InActor) override;
	virtual void BeginAction(bool bLeft) override;
	virtual void EndAction(bool bLeft) override;
};