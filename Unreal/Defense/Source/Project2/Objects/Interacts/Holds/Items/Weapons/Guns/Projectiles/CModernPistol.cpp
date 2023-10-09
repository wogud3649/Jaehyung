#include "CModernPistol.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/Objects/CGunComponent.h"
#include "Components/Objects/CWeaponComponent.h"
#include "Components/Utilities/CTraceComponent.h"
#include "Components/Utilities/Timelines/Floats/CZoomComponent.h"
#include "Objects/Interacts/Holds/Items/Expendables/CBullet.h"

ACModernPistol::ACModernPistol()
{
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", Scene);

	SetMesh(Mesh, "SkeletalMesh'/Game/Resources/Mesh/Weapons/Modern_Pistol/pistol.pistol'");
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

void ACModernPistol::BeginPlay()
{
	Super::BeginPlay();

	Trace->OnTrace.AddDynamic(Gun, &UCGunComponent::Fire);
}

void ACModernPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckNull (GetOwner());

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

void ACModernPistol::BeginRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	AttachToComponent_Relative(Mesh, mesh, "Item_ModernPistol", true);

	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(InActor);
	CheckNull(springArm);

	Zoom->SetSpringArm(springArm);

	Trace->SetActorToIgnore(InActor);

	for (int32 i = 0; i < Gun->GetBulletCapacity(); i++)
	{
		USphereComponent* sphere = CHelpers::GetComponent<USphereComponent>(Bullets[i]);
		if (!sphere) continue;

		sphere->IgnoreActorWhenMoving(InActor, true);
	}
}

void ACModernPistol::EndRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	DetachFromComponent(Mesh, mesh, FDetachmentTransformRules::KeepWorldTransform, true);

	Trace->RemoveActorToIgnore(InActor);

	for (int32 i = 0; i < Gun->GetBulletCapacity(); i++)
	{
		USphereComponent* sphere = CHelpers::GetComponent<USphereComponent>(Bullets[i]);
		if (!sphere) continue;

		sphere->IgnoreActorWhenMoving(InActor, false);
	}
}

void ACModernPistol::BeginAction(bool bLeft)
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

void ACModernPistol::EndAction(bool bLeft)
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