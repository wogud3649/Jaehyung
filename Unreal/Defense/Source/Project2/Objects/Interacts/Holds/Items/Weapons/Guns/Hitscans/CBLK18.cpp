#include "CBLK18.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "Components/Objects/CGunComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "Components/Utilities/CTraceComponent.h"
#include "Components/Utilities/Timelines/Floats/CZoomComponent.h"

ACBLK18::ACBLK18()
{
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", Scene);

	SetMesh(Mesh, "SkeletalMesh'/Game/Resources/Mesh/Weapons/BLK18/SKM_BLK18.SKM_BLK18'");
	Mesh->SetCollisionProfileName("Custom");
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);

	Weapon->SetType(EWeaponType::Pistol);
	Weapon->SetPower(10);
	Weapon->SetRange(700);

	Zoom->SetCurve("CurveFloat'/Game/Resources/Curves/C_ModernPistol.C_ModernPistol'");
}

void ACBLK18::BeginPlay()
{
	Super::BeginPlay();

	Trace->OnTrace.AddDynamic(Gun, &UCGunComponent::Fire);
}

void ACBLK18::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckNull(GetOwner());

	FVector start;
	FVector end;
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(GetOwner());
	if (camera)
	{
		start = camera->GetComponentLocation() + camera->GetForwardVector() * 300;
		end = start + camera->GetForwardVector() * 1700;
	}
	else
	{
		start = Mesh->GetSocketLocation("Muzzle");
		end = start + GetOwner()->GetActorForwardVector() * 2000;
	}

	Trace->Trace(start, end);
}

void ACBLK18::BeginRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	AttachToComponent_Relative(Mesh, mesh, "Item_BLK18", true);

	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(InActor);
	CheckNull(springArm);

	Zoom->SetSpringArm(springArm);
}

void ACBLK18::EndRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	DetachFromComponent(Mesh, mesh, FDetachmentTransformRules::KeepWorldTransform, true);
}

void ACBLK18::BeginAction(bool bLeft)
{
	CheckNull(GetOwner());

	if (bLeft)
	{
		Trace->BeginTrace();
	}
	else
	{
		Zoom->Play();
	}
}

void ACBLK18::EndAction(bool bLeft)
{
	CheckNull(GetOwner());

	if (bLeft)
	{

	}
	else
	{
		Zoom->Reverse();
	}
}