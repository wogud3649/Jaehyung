#include "CPlayerController.h"
#include "Global.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Player/CPlayer.h"

ACPlayerController::ACPlayerController()
{
	// Particle
	CHelpers::GetAsset<UParticleSystem>(&DestinationEffectTemplate, "ParticleSystem'/Game/Resources/Particles/P_Sparks.P_Sparks'");

	// Cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// SpawnParticle
	SpawnDestinationEffect();
}

void ACPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	//if (bPawnMoving)
	//{
	//	if (GetDistanceFromPawn(HitResultUnderCursor.ImpactPoint) < 120.0f)
	//	{
	//		bPawnMoving = false;
	//		SetDestinationEffectVisibility(false);
	//	}
	//}
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	 
	// BindAction
	InputComponent->BindAction("RightClick", IE_Pressed, this, &ACPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &ACPlayerController::OnSetDestinationReleased);
}

void ACPlayerController::MoveToMouseCursor()
{
	// Set HitResult
	GetHitResultUnderCursor(ECC_Visibility, false, HitResultUnderCursor);

	// Check Hit
	CheckFalse(HitResultUnderCursor.bBlockingHit);

	// Set Destination
	SetNewMoveDestination();
}

void ACPlayerController::SetNewMoveDestination()
{
	FVector DestLocation = HitResultUnderCursor.ImpactPoint;

	float const Distance = GetDistanceFromPawn(DestLocation);

	CheckFalse((Distance > 120.0f));
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
	SetDestinationEffectLocation(DestLocation);

	bPawnMoving = true;
	//SetDestinationEffectVisibility(true);
}

float ACPlayerController::GetDistanceFromPawn(FVector DestLocation)
{
	APawn* const pawn = GetPawn();
	if (!pawn)
		return 0;

	return FVector::Dist(DestLocation, pawn->GetActorLocation());
}

void ACPlayerController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;
}

void ACPlayerController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}

void ACPlayerController::SpawnDestinationEffect()
{
	CheckNull(DestinationEffectTemplate);

	DestinationEffect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestinationEffectTemplate, HitResultUnderCursor.ImpactPoint);
	//SetDestinationEffectVisibility(false);
}

void ACPlayerController::SetDestinationEffectVisibility(bool bVisibility)
{
	CheckNull(DestinationEffect);

	CheckTrue(bVisible == bVisibility);

	bVisible = bVisibility;

	// TODO : 다른 방식 찾아보기
	if (bVisible)
	{
		DestinationEffect->ActivateSystem();
	}
	else
	{
		DestinationEffect->DeactivateSystem();
	}
}

void ACPlayerController::SetDestinationEffectLocation(FVector EffectLocation)
{
	CheckNull(DestinationEffect);

	DestinationEffect->SetWorldLocation(EffectLocation);
}