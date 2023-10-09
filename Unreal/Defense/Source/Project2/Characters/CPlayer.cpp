#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Characters/CMovementComponent.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Characters/CMontageComponent.h"
#include "Components/Characters/Player/COptionComponent.h"
#include "Components/Characters/Player/CStoreComponent.h"
#include "Components/Utilities/CTraceComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Widgets/CCrossHairComponent.h"
#include "Components/Widgets/CResultComponent.h"
#include "Widgets/CUW_Health.h"

ACPlayer::ACPlayer()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpirngArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateComponent<UWidgetComponent>(this, &HealthWidget, "HealthWidget", GetMesh());

	CHelpers::CreateActorComponent<UCOptionComponent>(this, &Option, "Option");
	CHelpers::CreateActorComponent<UCTraceComponent>(this, &Trace, "Trace");
	CHelpers::CreateActorComponent<UCCrossHairComponent>(this, &CrossHair, "CrossHair");
	CHelpers::CreateActorComponent<UCStoreComponent>(this, &Store, "Store");
	CHelpers::CreateActorComponent<UCResultComponent>(this, &Result, "Result");

	SpringArm->SetRelativeLocation(FVector(0, 25, 180));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->SocketOffset = FVector(0, 25, 25);
	SpringArm->TargetArmLength = 175.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = false;

	SetOrientRotation(false);
	SetMesh("SkeletalMesh'/Game/Resources/Mesh/Characters/SK_Mannequin/SK_Mannequin.SK_Mannequin'");
	SetAnimInstance("AnimBlueprint'/Game/Characters/ABP_CPlayer.ABP_CPlayer_C'");

	Inventory->SetPlayer();
	Inventory->ClearMoney();
	Inventory->AddMoney(300);

	Montage->SetDataTable("DataTable'/Game/Characters/DataTables/DT_SK_Mannequin.DT_SK_Mannequin'");

	TSubclassOf<UCUW_Health> healthClass;
	CHelpers::GetClass<UCUW_Health>(&healthClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Health_Player.BP_CUW_Health_Player_C'");
	HealthWidget->SetWidgetClass(healthClass);
	HealthWidget->SetDrawSize(FVector2D(0, 0));
	HealthWidget->SetWidgetSpace(EWidgetSpace::World);
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	Trace->TickTrace.AddDynamic(CrossHair, &UCCrossHairComponent::Focus);
	Trace->OnTrace.AddDynamic(CrossHair, &UCCrossHairComponent::OnTrace);
	Trace->OffTrace.AddDynamic(CrossHair, &UCCrossHairComponent::OffTrace);

	HealthWidget->InitWidget();
	HealthWidget->GetWidget()->AddToViewport();

	Status->InitHealth();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CrossHair->IsDisplay())
	{
		FVector start = Camera->GetComponentLocation() + Camera->GetForwardVector() * 300;
		FVector end = start + Camera->GetForwardVector() * 600;
		Trace->Trace(start, end);
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Scroll", this, &ACPlayer::OnScroll);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::EndSprint);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACPlayer::BeginJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACPlayer::EndJump);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ACPlayer::BeginInteract);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &ACPlayer::EndInteract);
	PlayerInputComponent->BindAction("ActionL", EInputEvent::IE_Pressed, this, &ACPlayer::BeginActionL);
	PlayerInputComponent->BindAction("ActionL", EInputEvent::IE_Released, this, &ACPlayer::EndActionL);
	PlayerInputComponent->BindAction("ActionR", EInputEvent::IE_Pressed, this, &ACPlayer::BeginActionR);
	PlayerInputComponent->BindAction("ActionR", EInputEvent::IE_Released, this, &ACPlayer::EndActionR);
	PlayerInputComponent->BindAction("Dump", EInputEvent::IE_Pressed, this, &ACPlayer::Dump);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ACPlayer::Reload);
	PlayerInputComponent->BindAction("Build", EInputEvent::IE_Pressed, this, &ACPlayer::Build);
	PlayerInputComponent->BindAction("1", EInputEvent::IE_Pressed, this, &ACPlayer::Num1);
	PlayerInputComponent->BindAction("2", EInputEvent::IE_Pressed, this, &ACPlayer::Num2);
	PlayerInputComponent->BindAction("3", EInputEvent::IE_Pressed, this, &ACPlayer::Num3);
	PlayerInputComponent->BindAction("4", EInputEvent::IE_Pressed, this, &ACPlayer::Num4);
	PlayerInputComponent->BindAction("5", EInputEvent::IE_Pressed, this, &ACPlayer::Num5);
	PlayerInputComponent->BindAction("6", EInputEvent::IE_Pressed, this, &ACPlayer::Num6);
	PlayerInputComponent->BindAction("7", EInputEvent::IE_Pressed, this, &ACPlayer::Num7);
	PlayerInputComponent->BindAction("8", EInputEvent::IE_Pressed, this, &ACPlayer::Num8);
	PlayerInputComponent->BindAction("9", EInputEvent::IE_Pressed, this, &ACPlayer::Num9);
	PlayerInputComponent->BindAction("0", EInputEvent::IE_Pressed, this, &ACPlayer::Num0);
}

void ACPlayer::EndDead()
{
	Result->Lose();

	Super::EndDead();
}

void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Movement->GetCanMove());
	CheckTrue(InAxis == 0);

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Movement->GetCanMove());
	CheckTrue(InAxis == 0);

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	CheckTrue(abs(InAxis) < FLT_EPSILON);

	float rotationSpeed = InAxis * Option->HorizontalRotationRate * GetWorld()->GetDeltaSeconds();

	AddControllerYawInput(rotationSpeed);
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	CheckTrue(abs(InAxis) < FLT_EPSILON);

	float rotationSpeed = InAxis * Option->VerticalRotationRate * GetWorld()->GetDeltaSeconds();

	AddControllerPitchInput(rotationSpeed);
}

void ACPlayer::OnScroll(float InAxis)
{
	CheckTrue(InAxis == 0);

	if (InAxis > 0)
		Inventory->Right();
	else
		Inventory->Left();
}

void ACPlayer::BeginSprint()
{
	Movement->SetSprint();
}

void ACPlayer::EndSprint()
{
	Movement->SetRun();
}

void ACPlayer::BeginJump()
{
	CheckFalse(Status->IsIdle());

	AActor* item = Inventory->GetSelectedItem();

	if (!item)
	{
		Jump();
		return;
	}

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(item);
	if (!weapon)
	{
		Jump();
		return;
	}

	Avoid();
}

void ACPlayer::EndJump()
{
	AActor* item = Inventory->GetSelectedItem();
	if (item)
	{
		UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(Inventory->GetSelectedItem());
		if (weapon)
		{
			return;
		}
		return;
	}

	StopJumping();
}

void ACPlayer::BeginInteract()
{
	CheckFalse(Status->IsIdle());

	Trace->BeginTrace();
}

void ACPlayer::EndInteract()
{
	CheckFalse(Status->IsIdle());

	Trace->EndTrace();
}

void ACPlayer::BeginActionL()
{
	CheckNull(Inventory->GetSelectedItem());

	if (Status->IsActionL())
	{
		Montage->EnableNext();
	}

	CheckFalse(Status->IsIdle());

	Status->SetType(EStatusType::ActionL);

	Inventory->BeginAction(true);
}

void ACPlayer::EndActionL()
{
	CheckNull(Inventory->GetSelectedItem());

	Inventory->EndAction(true);
}

void ACPlayer::BeginActionR()
{
	CheckNull(Inventory->GetSelectedItem());

	CheckFalse(Status->IsIdle());

	Inventory->BeginAction(false);
}

void ACPlayer::EndActionR()
{
	CheckNull(Inventory->GetSelectedItem());

	Inventory->EndAction(false);
}

void ACPlayer::Dump()
{
	CheckFalse(Status->IsIdle());

	Inventory->Dump();
}

void ACPlayer::Reload()
{
	CheckFalse(Status->IsIdle());

	Inventory->Reload();
}

void ACPlayer::Build()
{
	if (Store->IsDisplay())
		Store->OffDisplay();
	else
		Store->OnDisplay();
}

void ACPlayer::Num1()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(0);
}

void ACPlayer::Num2()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(1);
}

void ACPlayer::Num3()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(2);
}

void ACPlayer::Num4()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(3);
}

void ACPlayer::Num5()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(4);
}

void ACPlayer::Num6()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(5);
}

void ACPlayer::Num7()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(6);
}

void ACPlayer::Num8()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(7);
}

void ACPlayer::Num9()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(8);
}

void ACPlayer::Num0()
{
	CheckFalse(Status->IsIdle());

	Inventory->Select(9);
}