#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CProjectileComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsFired() { return bFired; }

private:
	UPROPERTY(EditDefaultsOnly)
		float Speed = 2000.0f;

	UPROPERTY(EditDefaultsOnly)
		float ProjectileGravityScale = 0.0f;

	UPROPERTY(EditDefaultsOnly)
		bool bFired = false;

	UPROPERTY(EditDefaultsOnly)
		float MaxLifespan = 2.0f;

public:
	UCProjectileComponent();

protected:
	virtual void BeginPlay() override;

public:
	void TickProjectile(float DeltaTime);

	void Fire(FRotator InDirection);
	void Init();
	void Reload();

private:
	FRotator Direction;
	float Lifespan = MaxLifespan;
};