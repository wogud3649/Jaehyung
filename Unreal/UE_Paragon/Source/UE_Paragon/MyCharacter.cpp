// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "MyAnimInstance.h"
#include "MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MyUserWidget.h"
#include "MyAIController.h"

// ·Î±×
// UE_LOG(LogTemp, Log, TEXT("UpDown Scale : %f"), value);
// UE_LOG(LogTemp, Log, TEXT("LeftRight Scale : %f"), value);

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm
	(TEXT("SkeletalMesh'/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith'"));

	if (sm.Succeeded())
		GetMesh()->SetSkeletalMesh(sm.Object);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	_stat = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));
	_hpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpBarWidget->SetupAttachment(GetMesh());
	_hpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	_hpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/HPBAR.HPBar_C'"));

	if (UW.Succeeded())
	{
		_hpBarWidget->SetWidgetClass(UW.Class);
		_hpBarWidget->SetDrawSize(FVector2D(200.0f, 50.0f));
	}

	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (IsValid(_animInstance))
	{
		_animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
		_animInstance->_onAttackHit.AddUObject(this, &AMyCharacter::AttackCheck);
	}

	_hpBarWidget->InitWidget();
	auto hpWidget = Cast<UMyUserWidget>(_hpBarWidget->GetUserWidgetObject());

	if (hpWidget)
	{
		hpWidget->Bind(_stat);
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
}

void AMyCharacter::Attack()
{
	if (_isAttack == true)
		return;

	_animInstance->PlayAttackMontage();

	_animInstance->JumpToSection(_curAttack);
	_curAttack = _curAttack % 3 + 1;

	_isAttack = true;
}

void AMyCharacter::AttackCheck()
{
	//UE_LOG(LogTemp, Log, TEXT("ATTACKCHECK"));
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 50.0f;

	bool boolResult = GetWorld()->SweepSingleByChannel
	(
		OUT hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	// GetWorld()->LineTraceSingleByChannel();
	// DrawDebugLine();

	FColor drawColor;
	if (boolResult)
	{
		drawColor = FColor::Red;
		//Cast<AMyCharacter>(hitResult.Actor)->TakeDamage(_stat->GetAttack());
	}
	else
	{
		drawColor = FColor::Green;
	}

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;
	float halfHeight = attackRange * 0.5f + attackRadius;
	FQuat rotation = FRotationMatrix::MakeFromZ(vec).ToQuat();

	DrawDebugCapsule
	(
		GetWorld(),
		center,
		halfHeight,
		attackRadius,
		rotation,
		drawColor,
		false,
		1.0f
	);

	if (boolResult && hitResult.Actor.IsValid())
	{
		FDamageEvent damageEvent;
		hitResult.Actor->TakeDamage(_stat->GetAttack(), damageEvent, GetController(), this);
	}
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
{
	_isAttack = false;
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	_stat->Damaged(Damage);

	UE_LOG(LogTemp, Log, TEXT("CurHp : %d"), _stat->GetHp());

	return Damage;
}

void AMyCharacter::UpDown(float value)
{
	_upDown = value;
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::LeftRight(float value)
{
	_leftRight = value;
	AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::Yaw(float value)
{
	AddControllerYawInput(value);
}