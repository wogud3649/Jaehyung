#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/Weapons/OneHands/COneHand.h"
#include "CSword.generated.h"

UCLASS()
class PROJECT2_API ACSword : public ACOneHand
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleDefaultsOnly)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

public:
	ACSword();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginRoot(AActor* InActor) override;
	virtual void EndRoot(AActor* InActor) override;
	virtual void BeginAction(bool bLeft) override;
	virtual void EndAction(bool bLeft) override;
};