#include "CCharacter.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Animation/AnimInstance.h"
#include "Characters/CAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/Characters/CMovementComponent.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Characters/CMontageComponent.h"
#include "Components/Objects/CWeaponComponent.h"

void ACCharacter::StatusChanged(EStatusType InType)
{
	AActor* Item = Inventory->GetSelectedItem();
	if (!Item)
	{
		Montage->PlayAnimMontage(EWeaponType::Unarmed, InType);
		return;
	}

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(Inventory->GetSelectedItem());
	if (!weapon)
	{
		Montage->PlayAnimMontage(EWeaponType::Unarmed, InType);
		return;
	}

	Montage->PlayAnimMontage(weapon->GetType(), InType);
}

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCMovementComponent>(this, &Movement, "Movement");
	CHelpers::CreateActorComponent<UCInventoryComponent>(this, &Inventory, "Inventory");
	CHelpers::CreateActorComponent<UCMontageComponent>(this, &Montage, "Montage");

	Movement->SetRun();
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetDynamicMaterial();

	Status->OnStatusChanged.AddDynamic(this, &ACCharacter::StatusChanged);

	AnimInstance = Cast<UCAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		Inventory->SelectedItem.AddDynamic(AnimInstance, &UCAnimInstance::UpdateItemType);
	}
	else
	{
		CLog::Print("NoAnimInstance");
		CLog::Print(GetName());
	}
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FGenericTeamId ACCharacter::GetGenericTeamId() const
{
	return FGenericTeamId(TeamId);
}

void ACCharacter::SetIgnoreActor(AActor* InActor, bool bIgnore)
{
	GetMesh()->IgnoreActorWhenMoving(InActor, bIgnore);
	GetCapsuleComponent()->IgnoreActorWhenMoving(InActor, bIgnore);
}

void ACCharacter::Healed(float InAmount)
{
	Status->AddHealth(InAmount);
}

void ACCharacter::Damaged(float InAmount, ACharacter* InCauser)
{
	Status->SubHealth(InAmount, InCauser);

	float yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), InCauser->GetActorLocation()).Yaw;
	FRotator rotator = FRotator(0);
	rotator.Yaw = yaw;

	SetActorRotation(rotator);
}

void ACCharacter::EndBackstep()
{
	InitStatus();
	SetOrientRotation(false);
}

void ACCharacter::EndRoll()
{
	InitStatus();
	SetOrientRotation(false);
}

void ACCharacter::EndHitted()
{
	InitStatus();
	SetOrientRotation(false);
}

void ACCharacter::EndDead()
{
	Inventory->DestroyAll();

	K2_DestroyActor();
}

void ACCharacter::EndInteract()
{
	InitStatus();
}

void ACCharacter::EndActionL()
{
	InitStatus();
	Montage->InitSelected();
}

void ACCharacter::NextMontage()
{
	CheckNull(Inventory->GetSelectedItem());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(Inventory->GetSelectedItem());
	CheckNull(weapon);

	Montage->DisableNext();
	Montage->NextSelected();
	Montage->PlayAnimMontage(weapon->GetType(), Status->GetType());
}

void ACCharacter::InitMontage()
{
	Montage->InitSelected();
}

void ACCharacter::InitBeginPlay()
{
}

void ACCharacter::SetDynamicMaterial()
{
	CheckNull(GetMesh());

	TArray<UMaterialInterface*> materials = GetMesh()->GetMaterials();

	for (int32 index = 0; index < materials.Num(); index++)
	{
		UMaterialInstanceConstant* constantMaterial = Cast<UMaterialInstanceConstant>(materials[index]);
		if (!constantMaterial) CLog::Log(index + "Is Not Instance"); continue;

		DynamicMaterials[index] = UMaterialInstanceDynamic::Create(constantMaterial, this);
		GetMesh()->SetMaterial(index, DynamicMaterials[index]);
	}
}

void ACCharacter::SetMesh(FString InPath)
{
	CheckTrue(InPath == "");

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, InPath);
	GetMesh()->SetSkeletalMesh(mesh);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ACCharacter::SetAnimInstance(FString InPath)
{
	CheckTrue(InPath == "");

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, InPath);
	GetMesh()->SetAnimInstanceClass(animInstance);
}

void ACCharacter::SetOrientRotation(bool bOrientRotation)
{
	GetCharacterMovement()->bOrientRotationToMovement = bOrientRotation;
	bUseControllerRotationYaw = !bOrientRotation;
}

void ACCharacter::Avoid()
{
	float dir = GetDirection();
	FRotator rotator = GetActorRotation();

	if (dir > 130 || dir < -130)
	{
		rotator.Yaw = rotator.Yaw + dir - 180;
		SetOrientRotation(true);
		SetActorRotation(rotator);
		Backstep();
	}
	else
	{
		rotator.Yaw = rotator.Yaw + dir;
		SetOrientRotation(true);
		SetActorRotation(rotator);
		Roll();
	}
}

void ACCharacter::InitStatus()
{
	Status->SetIdle();
	Movement->SetMove();
}

void ACCharacter::Backstep()
{
	Status->SetType(EStatusType::Backstep);
}

void ACCharacter::Roll()
{
	Status->SetType(EStatusType::Roll);
}

float ACCharacter::GetDirection()
{
	float rot = GetControlRotation().Yaw;
	float velocity = GetVelocity().Rotation().Yaw;
	float dir;

	if (rot > 180)
		rot = rot - 360;

	if ((rot > 0 && velocity > 0) || (rot < 0 && velocity < 0))
		dir = velocity - rot;
	else if (rot > 0 && velocity < 0)
		dir = 360 - rot + velocity;
	else if (rot < 0 && velocity > 0)
		dir = velocity - rot;
	else
		dir = 0;

	if (dir > 180)
		dir = dir - 360;

	return dir;
}