#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

UCLASS()
class DEFENSERPG_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void MoveToMouseCursor();
	void SetNewMoveDestination();
	float GetDistanceFromPawn(FVector DestLocation);

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void SpawnDestinationEffect();
	void SetDestinationEffectVisibility(bool bVisibility);
	void SetDestinationEffectLocation(FVector EffectLocation);

protected:
	FHitResult HitResultUnderCursor;
	bool bMoveToMouseCursor = false;

	class UParticleSystem* DestinationEffectTemplate;
	class UParticleSystemComponent* DestinationEffect;
	bool bVisible = false;

	bool bPawnMoving = false;
};