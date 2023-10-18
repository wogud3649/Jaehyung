#include "CPlayer.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Animation/AnimInstance.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Items/CInventoryComponent.h"

ACPlayer::ACPlayer()
{
	// CreateComponent
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateComponent<UDecalComponent>(this, &Decal, "Decal", GetMesh());

	// CreateActorComponent
	CHelpers::CreateActorComponent<UCInventoryComponent>(this, &Inventory, "Inventory");

	// UseControllerRotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Mesh
	USkeletalMeshComponent* Skeletal = GetMesh();
	USkeletalMesh* MannequinMesh = NULL;
	CHelpers::GetAsset<USkeletalMesh>(&MannequinMesh, "SkeletalMesh'/Game/Resources/Characters/SK_Mannequin/Mesh/SK_Mannequin_Female.SK_Mannequin_Female'");
	if (MannequinMesh)
		Skeletal->SetSkeletalMesh(MannequinMesh);
	Skeletal->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	Skeletal->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	TSubclassOf<UAnimInstance> AnimInstance;
	CHelpers::GetClass<UAnimInstance>(&AnimInstance, "AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'");
	Skeletal->SetAnimInstanceClass(AnimInstance);

	// CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// SpringArm
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;

	// Camera
	Camera->bUsePawnControlRotation = false;

	// Decal
	UMaterial* DecalMaterial = NULL;
	CHelpers::GetAsset<UMaterial>(&DecalMaterial, "Material'/Game/Resources/Decal/M_Cursor_Decal.M_Cursor_Decal'");
	if (DecalMaterial)
		Decal->SetDecalMaterial(DecalMaterial);
	Decal->DecalSize = FVector(16.f, 32.f, 32.f);
	Decal->SetRelativeRotation(FRotator(90.f, 0.f, 0.f).Quaternion());

	// Tick
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

	TickDecal();
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// BindAction
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ACPlayer::OnLeftPressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &ACPlayer::OnLeftReleased);
	InputComponent->BindAction("1", IE_Pressed, this, &ACPlayer::On1Pressed);
	InputComponent->BindAction("2", IE_Pressed, this, &ACPlayer::On2Pressed);
	InputComponent->BindAction("3", IE_Pressed, this, &ACPlayer::On3Pressed);
	InputComponent->BindAction("4", IE_Pressed, this, &ACPlayer::On4Pressed);
	InputComponent->BindAction("5", IE_Pressed, this, &ACPlayer::On5Pressed);
	InputComponent->BindAction("6", IE_Pressed, this, &ACPlayer::On6Pressed);
	InputComponent->BindAction("7", IE_Pressed, this, &ACPlayer::On7Pressed);
	InputComponent->BindAction("8", IE_Pressed, this, &ACPlayer::On8Pressed);
	InputComponent->BindAction("9", IE_Pressed, this, &ACPlayer::On9Pressed);
	InputComponent->BindAction("0", IE_Pressed, this, &ACPlayer::On0Pressed);
}

void ACPlayer::TickDecal()
{
	CheckNull(Decal);

	APlayerController* PC = Cast<APlayerController>(GetController());
	CheckNull(PC);

	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);

	CheckFalse(HitResult.bBlockingHit);

	FVector CursorFV = HitResult.ImpactNormal;
	FRotator CursorR = CursorFV.Rotation();
	Decal->SetWorldLocation(HitResult.Location);
	Decal->SetWorldRotation(CursorR);
}

void ACPlayer::OnLeftPressed()
{
	Inventory->PlayAction(true);
}

void ACPlayer::OnLeftReleased()
{
}

void ACPlayer::On1Pressed()
{
	Inventory->SelectItem(0);
}

void ACPlayer::On2Pressed()
{
	Inventory->SelectItem(1);
}

void ACPlayer::On3Pressed()
{
	Inventory->SelectItem(2);
}

void ACPlayer::On4Pressed()
{
	Inventory->SelectItem(3);
}

void ACPlayer::On5Pressed()
{
	Inventory->SelectItem(4);
}

void ACPlayer::On6Pressed()
{
	Inventory->SelectItem(5);
}

void ACPlayer::On7Pressed()
{
	Inventory->SelectItem(6);
}

void ACPlayer::On8Pressed()
{
	Inventory->SelectItem(7);
}

void ACPlayer::On9Pressed()
{
	Inventory->SelectItem(8);
}

void ACPlayer::On0Pressed()
{
	Inventory->SelectItem(9);
}
