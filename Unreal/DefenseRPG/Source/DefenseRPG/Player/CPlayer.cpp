#include "CPlayer.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"

ACPlayer::ACPlayer()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateComponent<UDecalComponent>(this, &Decal, "Decal", GetMesh());

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	USkeletalMeshComponent* Skeletal = GetMesh();
	USkeletalMesh* MannequinMesh = NULL;
	CHelpers::GetAsset<USkeletalMesh>(&MannequinMesh, "SkeletalMesh'/Game/Resources/Character/SK_Mannequin/Mesh/SK_Mannequin_Female.SK_Mannequin_Female'");
	Skeletal->SetSkeletalMesh(MannequinMesh);
	Skeletal->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	Skeletal->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;

	Camera->bUsePawnControlRotation = false;

	UMaterial* DecalMaterial = NULL;
	CHelpers::GetAsset<UMaterial>(&DecalMaterial, "Material'/Game/Resources/Decal/M_Cursor_Decal.M_Cursor_Decal'");
	if (DecalMaterial)
	{
		Decal->SetDecalMaterial(DecalMaterial);
	}
	Decal->DecalSize = FVector(16.f, 32.f, 32.f);
	Decal->SetRelativeRotation(FRotator(90.f, 0.f, 0.f).Quaternion());

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Decal)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = Camera->GetComponentLocation();
				FVector EndLocation = Camera->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				Decal->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			Decal->SetWorldLocation(TraceHitResult.Location);
			Decal->SetWorldRotation(CursorR);
		}
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}