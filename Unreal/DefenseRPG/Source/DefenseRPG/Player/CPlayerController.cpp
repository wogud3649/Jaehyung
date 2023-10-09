#include "CPlayerController.h"
#include "Global.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Player/CPlayer.h"

ACPlayerController::ACPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ACPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ACPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ACPlayerController::OnSetDestinationReleased);

	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ACPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ACPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ACPlayerController::OnResetVR);
}

void ACPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ACPlayer* player = Cast<ACPlayer>(GetPawn()))
		{
			if (player->GetDecal())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, player->GetDecal()->GetComponentLocation());
			}
		}
	}
	else
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ACPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ACPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const pawn = GetPawn();
	if (pawn)
	{
		float const Distance = FVector::Dist(DestLocation, pawn->GetActorLocation());

		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ACPlayerController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;
}

void ACPlayerController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}