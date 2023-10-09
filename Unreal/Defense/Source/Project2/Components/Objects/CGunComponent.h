#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGunComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void Fire(FHitResult InHitResult);

public:
	FORCEINLINE int32 GetBulletCapacity() { return BulletCapacity; }
	FORCEINLINE int32 GetActiveBullets() { return ActiveBullets; }

private:
	UPROPERTY(EditDefaultsOnly)
		int32 BulletCapacity = 30;

public:
	UCGunComponent();

protected:
	virtual void BeginPlay() override;

public:
	void Reload();

private:
	int32 ActiveBullets = BulletCapacity;
};