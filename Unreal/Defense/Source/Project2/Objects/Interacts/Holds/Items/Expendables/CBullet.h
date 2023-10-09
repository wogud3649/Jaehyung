#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/Expendables/CExpendable.h"
#include "Components/Objects/CProjectileComponent.h"
#include "CBullet.generated.h"

UCLASS()
class PROJECT2_API ACBullet : public ACExpendable
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	FORCEINLINE bool IsFired() { return Projectile->IsFired(); }

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		UCProjectileComponent* Projectile;

public:
	ACBullet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginRoot(AActor* InActor) override;
	virtual void EndRoot(AActor* InActor) override;
	virtual void BeginAction(bool bLeft) override;
	virtual void EndAction(bool bLeft) override;

	void Fire(FRotator Direction);
	void Init();
	void Reload();
	void Hit();
};